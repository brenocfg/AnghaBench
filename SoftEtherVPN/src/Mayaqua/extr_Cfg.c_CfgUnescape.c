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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (int) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 
 int ToInt (char*) ; 
 char* ZeroMalloc (int) ; 

char *CfgUnescape(char *str)
{
	char *tmp;
	char *ret;
	char tmp2[16];
	UINT len, wp, i;
	UINT code;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	len = StrLen(str);
	tmp = ZeroMalloc(len + 1);
	wp = 0;
	if (len == 1 && str[0] == '$')
	{
		// Empty character
		tmp[0] = 0;
	}
	else
	{
		for (i = 0;i < len;i++)
		{
			if (str[i] != '$')
			{
				tmp[wp++] = str[i];
			}
			else
			{
				tmp2[0] = '0';
				tmp2[1] = 'x';
				tmp2[2] = str[i + 1];
				tmp2[3] = str[i + 2];
				i += 2;
				tmp2[4] = 0;
				code = ToInt(tmp2);
				tmp[wp++] = (char)code;
			}
		}
	}
	ret = Malloc(StrLen(tmp) + 1);
	StrCpy(ret, StrLen(tmp) + 1, tmp);
	Free(tmp);
	return ret;
}