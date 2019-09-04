#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUFF_MAX_LENG ; 
 int GetRealString (char*) ; 
 int TERM_MAX_LENG ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int insert_string (char*) ; 
 int /*<<< orphan*/  itoa (int,char*,int) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

void bigIndex_hash(const char *docpath, const char *hashpath)  
{  
	FILE *fr, *fw;  
	int len;  
	char *pbuf, *p;  
	char dockey[TERM_MAX_LENG];  

	if(docpath == NULL || *docpath == '\0')  
		return;  

	if(hashpath == NULL || *hashpath == '\0')  
		return;  

	fr = fopen(docpath, "rb");  //读取文件docpath  
	fw = fopen(hashpath, "wb");  
	if(fr == NULL || fw == NULL)  
	{  
		printf("open read or write file error!\n");  
		return;  
	}  

	pbuf = (char*)malloc(BUFF_MAX_LENG);  
	if(pbuf == NULL)  
	{  
		fclose(fr);  
		return ;  
	}  

	memset(pbuf, 0, BUFF_MAX_LENG);  

	while(fgets(pbuf, BUFF_MAX_LENG, fr))  
	{  
		len = GetRealString(pbuf);  
		if(len <= 1)  
			continue;  
		p = strstr(pbuf, "#####");    
		if(p != NULL)  
			continue;  

		p = strstr(pbuf, "  ");  
		if (p == NULL)  
		{  
			printf("file contents error!");  
		}  

		len = p - pbuf;  
		dockey[0] = 0;  
		strncpy(dockey, pbuf, len);  

		dockey[len] = 0;        

		int num = insert_string(dockey);   

		dockey[len] = ' ';  
		dockey[len+1] = '\0';  
		char str[20];  
		itoa(num, str, 10);  

		strcat(dockey, str);  
		dockey[len+strlen(str)+1] = '\0';  
		fprintf (fw, "%s\n", dockey);  

	}  
	free(pbuf);  
	fclose(fr);  
	fclose(fw);  
}