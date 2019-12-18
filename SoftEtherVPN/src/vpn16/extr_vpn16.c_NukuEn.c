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
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

void NukuEn(char *dst, char *src)
{
	char str[MAX_PATH];
	int i;
	if (src)
	{
		strcpy(str, src);
	}
	else
	{
		strcpy(str, dst);
	}
	i = strlen(str);
	if (str[i - 1] == '\\')
	{
		str[i - 1] = 0;
	}
	strcpy(dst, str);
}