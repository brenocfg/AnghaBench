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
 int WORD_MAX_LENG ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int insert_string (char*) ; 
 int /*<<< orphan*/  itoa (int,char*,int) ; 
 int keysize ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

void bigIndex_hashcode(const char *in_file_path, const char *out_file_path)  
{  
	FILE *fr, *fw;  
	int len, value;  
	char *pbuf, *pleft, *p;  
	char keyvalue[TERM_MAX_LENG], str[WORD_MAX_LENG];  

	if(in_file_path == NULL || *in_file_path == '\0') {  
		printf("input file path error!\n");  
		return;  
	}  

	if(out_file_path == NULL || *out_file_path == '\0') {  
		printf("output file path error!\n");  
		return;  
	}  

	fr = fopen(in_file_path, "r");  //读取in_file_path路径文件  
	fw = fopen(out_file_path, "w");  

	if(fr == NULL || fw == NULL)  
	{  
		printf("open read or write file error!\n");  
		return;  
	}  

	pbuf = (char*)malloc(BUFF_MAX_LENG);  
	pleft = (char*)malloc(BUFF_MAX_LENG);  
	if(pbuf == NULL || pleft == NULL)  
	{  
		printf("allocate memory error!");  
		fclose(fr);  
		return ;  
	}  

	memset(pbuf, 0, BUFF_MAX_LENG);  

	int offset = 1;  
	while(fgets(pbuf, BUFF_MAX_LENG, fr))  
	{  
		if (--offset > 0)  
			continue;  

		if(GetRealString(pbuf) <= 1)  
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

		// 确定跳过行数  
		strcpy(pleft, p+1);   
		offset = atoi(pleft) + 1;  

		strncpy(keyvalue, pbuf, len);    
		keyvalue[len] = '\0';  
		value = insert_string(keyvalue);  

		if (value != -1) {  

			// key value中插入空格  
			keyvalue[len] = ' ';  
			keyvalue[len+1] = '\0';  

			itoa(value, str, 10);  
			strcat(keyvalue, str);  

			keyvalue[len+strlen(str)+1] = ' ';  
			keyvalue[len+strlen(str)+2] = '\0';  

			keysize++;  
			itoa(keysize, str, 10);  
			strcat(keyvalue, str);  

			// 将key value写入文件  
			fprintf (fw, "%s\n", keyvalue);  

		}  
	}  
	free(pbuf);  
	fclose(fr);  
	fclose(fw);  
}