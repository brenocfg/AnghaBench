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

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  NukuEn (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

void GetDirFromPath(char *dst, char *src)
{
	char str[MAX_PATH];
	int i,len;
	char c;
	char tmp[MAX_PATH];
	int wp;
	if (src)
	{
		strcpy(str, src);
	}
	else
	{
		strcpy(str, dst);
	}
	NukuEn(str, NULL);
	wp = 0;
	len = strlen(str);
	dst[0] = 0;
	for (i = 0;i < len;i++)
	{
		c = str[i];
		switch (c)
		{
		case '\\':
			tmp[wp] = 0;
			wp = 0;
			strcat(dst, tmp);
			strcat(dst, "\\");
			break;
		default:
			tmp[wp] = c;
			wp++;
			break;
		}
	}
	NukuEn(dst, NULL);
}