#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#define M 997 

struct hash_table
{
	int key;
	int flag;				// Bayrak 1 ise o index dolu demektir.Bayrak bos ise o index 0 demektir.
	char string[100];
	char duzelt[80];
};

int hash(int h1,int h2,int i)	// Hashing
{
	return (h1+(i*h2))%M;
}
int hash1(int key)				// Hash1
{
	return key % M;
}
int hash2(int key)				// Hash2
{
	return 1+(key%(M-1));
}


void insert(char kelime[20], struct hash_table *array,int k)
{
	int key=findKey(kelime); // insert yaparken sadece kelimeyi buraya yollayıp Key degerini findKey fonksiyonunda stringi int'e dönüştürerek çağırdık.
	int i=0,j;
	int h1=hash1(key);
	int h2=hash2(key);					// hash islemeri icin degerleri h1 h2'ye atadik.
	int index=hash(h1,h2,i);			// Cunku ana hash fonksiyonumuz hash1 ve hash2'yi h1-h2 olarak kullanıyor.
	int size=0;
	for(j=0;97<=((int)kelime[j]) && ((int)kelime[j])<=122;j++)
	{
		size++;
	}
	int temp;
	while (array[index].flag==1)
	{
		if(array[index].key==key)					// string(x) Key degeri ile string(y) Key degeri aynı olsa bile
		{														// Stringlerin aynı olup olmadığını ekstra kontrol ederek farklı stringlerden gelebilecek					// Olası aynı Key değerleri için fonksiyonumuzu doğru çalışır hale getirdik.		
		return;
		}
		i++;
		index=hash(h1,h2,i);									// Boş yer bulana kadar i'yi arttıra arttıra hash'i devam ettirdik
	}

	array[index].flag=1;										// Bulunulan index'in flag==0 olması durumu orasının boş olduğunu gösterir.
	array[index].key=key;										// Böylece key ve string'i struct'ın o indexindeki değerlere atadık.					
	for(j=0;j<size;j++)									// Ayrıca o index'in flagini=1 yaparak orasının artık dolu olduğunu da belirttik.
	{
		array[index].string[j]=kelime[j];
	}
	
}

int insert2(char kelime[20],struct hash_table *array2)
{
	int key=findKey(kelime); // insert yaparken sadece kelimeyi buraya yollayıp Key degerini findKey fonksiyonunda stringi int'e dönüştürerek çağırdık.
	int i=0,j;
	int h1=hash1(key);
	int h2=hash2(key);					// hash islemeri icin degerleri h1 h2'ye atadik.
	int index=hash(h1,h2,i);			// Cunku ana hash fonksiyonumuz hash1 ve hash2'yi h1-h2 olarak kullanıyor.
	int size=0;
	for(j=0;97<=((int)kelime[j]) && ((int)kelime[j])<=122;j++)
	{
		size++;
	}
	int temp;
	while(array2[index].flag==1)
	{
		if(array2[index].key==key)					// string(x) Key degeri ile string(y) Key degeri aynı olsa bile
		{
		return index;												// Stringlerin aynı olup olmadığını ekstra kontrol ederek farklı stringlerden gelebilecek					// Olası aynı Key değerleri için fonksiyonumuzu doğru çalışır hale getirdik.		
		}
		i++;
		index=hash(h1,h2,i);									// Boş yer bulana kadar i'yi arttıra arttıra hash'i devam ettirdik
	}

	array2[index].flag=1;										// Bulunulan index'in flag==0 olması durumu orasının boş olduğunu gösterir.
	array2[index].key=key;										// Böylece key ve string'i struct'ın o indexindeki değerlere atadık.					
	for(j=0;j<size;j++)									// Ayrıca o index'in flagini=1 yaparak orasının artık dolu olduğunu da belirttik.
	{
		array2[index].string[j]=kelime[j];
	}
	return index;
}
void hatali(char aranankelime[20],struct hash_table *array,struct hash_table *array2)
{
	int d,i;
	int len1=strlen(aranankelime);		// aranan kelimenin uzunluğu
	
	for(i=0;i<M;i++)
	{
		if(array[i].flag==1)
		{
		int len2=strlen(array[i].string);		// karsilastirilacak kelimenin uzunluğu ( distance hesabı için gerekli)
		d= distance(aranankelime,len1,array[i].string,len2);
		if(d==1)								// distance 1 ise
		{
			int index=insert2(aranankelime,array2);
			strcat(array2[index].duzelt,array[i].string);
			strcat(array2[index].duzelt," ");
		}
		if(d==2)								// distance 2 ise 
		{
			int index=insert2(aranankelime,array2);
			strcat(array2[index].duzelt,array[i].string);	
			strcat(array2[index].duzelt," ");
		}
		}
		
	}
}

void search(char aranankelime[20],struct hash_table *array,struct hash_table *array2)
{
	int key=findKey(aranankelime); 				// Aranan kelimenin keyini elde ettik.
	int i=0,j;
	int h1=hash1(key);
	int h2=hash2(key);
	int index=hash(h1,h2,i);
	int adimsayisi=1;
	int lenght=strlen(aranankelime);							// Kac adımda bulduğumuzu saydırmak için tuttuk.
										
	while (array[index].flag==1)			
	{
		int counter=0;
		for(j=0;j<lenght;j++)
		{
			if(array[index].string[j]==aranankelime[j])
			{
				counter++;
			}
		}
		
		if(array[index].key==key)
		{
			printf("\n  The word %s is in the dictionary..",aranankelime);
			return;
		}
		i++;
		index=hash(h1,h2,i);							// Kodu ilk yazarken farklı kelimelerin aynı Key degerine denk gelmesi sebebiyle kelime kaybı
		adimsayisi++;									// Ve yanlış bilgi gösterimini farketmiştim.strcmp kontrolünü if içerisinde ekstra tanımlayarak bunu çözmüş oldum.
						
	}													// yani artık KEY DEGERLERİ aynı olsa bile STRING eslesmez ise farklı kelimeler olduğunu farkediyoruz.
	if(array[index].key!=key)
	{
		hatali(aranankelime,array,array2);
	}
}
int distance (char *word1,int len1,char *word2,int len2)
{
    int matrix[len1 + 1][len2 + 1];
    int i;
    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++) {
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int delete1;
                int insert;
                int substitute;
                int minimum;

                delete1 = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete1;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}

int findKey(char *str)									// Hashing hesaplamasında kullanılacak Key degerinin olusturuldugu fonksiyon
{
				
	int sum=0,j;		
	for(j=0;97<=((int)str[j]) && ((int)str[j])<=122;j++)		// 						HORNER METODU
	{
		sum+=str[j]*pow(3,j);;
	}
	return sum;										 
}

int main()
{
	struct hash_table sozluk[M];
	struct hash_table hatali[M];
	sozluk[M].flag=0;
	hatali[M].flag=0;											// Tüm flagleri 0'a setledim. Kullanımıma göre flag=0 ise o index bos demektir.									// Yani tüm indexlerin bos oldugunu belirttim.
	char small_dictionary[10000];
	char aranankelime[20];								
	char girdi[1000]; 							
	char *tempstr;
	char *tempstr2;										 
	FILE *dosya;
	int i;

			dosya = fopen("smallDictionary.txt","r"); 	// Dokumandaki satırları çeker ( ENTER ) basılana kadar
			if(dosya!=NULL)					// Baştan böyle başladım hocam. Text dosyası sıralı bir şekilde girildiği sürece tüm değerleri eksiksiz okuyorum.
			{								// Fakat sürekli enter basılarak girilen text'leri okuyamıyor.Sonradan değiştirecekti ama her şeyi değiştirmem gerekcekti
				fgets(small_dictionary,10000,dosya);			// Atacağım örnek görüntülerden programın eksiksiz ve düzgün çalıştığını göreceksiniz.
				strlwr(small_dictionary);
				printf("\n\n Information imported from small Dictionary.txt");	
			}
			else
			{
				printf("\n Wrong Filename! ");
			}
			fclose(dosya);
			int textsize=strlen(small_dictionary);		// Dokumandaki tüm string üzerinden kelime kelime ayırma yaptık.
			int j=0;
			while(j<textsize)
			{
			
				tempstr=(char*)malloc(20*sizeof(char));
				
				int k=0;
				for(j;97<=((int)small_dictionary[j]) && ((int)small_dictionary[j])<=122;j++)	// Sozluk oldugu için kelimelerin harflerinin küçük olmasıyla birlikte
				{
					tempstr[k]=small_dictionary[j];										// Küçük harf harici değer görürsen dedim çünkü bosluk harici / gibi işaretler
					k++;																// Görmesi durumunda onları da ekleyebilirdik.
				}																		// Belki ödevde noktalama işaretleri yok denmiş ama ben daha kapsamlı olacağı için bunu tercih ettim.
				j++;
				
				insert(tempstr,sozluk,k);		// Kelimeyi ayırdık insert fonksiyonuna yolladık ve gerekli kontrolleri yaptırdık.
				free(tempstr);
			}
			
			int counter=0;	
				printf("\n\n Enter the sentence you want to check :  ");
 			 	gets(girdi);
 			 	strlwr(girdi);
 			 	int textsize2=strlen(girdi);		// Dokumandaki tüm string üzerinden kelime kelime ayırma yaptık.
				j=0;
				while(j<textsize2)
				{
			
					tempstr2=(char*)malloc(20*sizeof(char));
				
					int k=0;
					for(j;97<=((int)girdi[j]) && ((int)girdi[j])<=122;j++)	// Sozluk oldugu için kelimelerin harflerinin küçük olmasıyla birlikte
					{
						tempstr2[k]=girdi[j];										// Küçük harf harici değer görürsen dedim çünkü bosluk harici / gibi işaretler
						k++;																// Görmesi durumunda onları da ekleyebilirdik.
					}																		// Belki ödevde noktalama işaretleri yok denmiş ama ben daha kapsamlı olacağı için bunu tercih ettim.
					j++;
															// Sozluk olduğu için kelimeleri kuculterek arama yaptım.
		        	search(tempstr2,sozluk,hatali);
					// Kelimeyi ayırdık insert fonksiyonuna yolladık ve gerekli kontrolleri yaptırdık.
					free(tempstr2);
				}
		        
			  
			  for(i=0;i<M;i++)
		    {
		    	if(hatali[i].flag==1)
				{
					printf("\n The word %s is a misspelling -- Suggestion(s) :   %s ",hatali[i].string,hatali[i].duzelt);
				}
			}
			
	return 0;
}
