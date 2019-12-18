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
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int UINT ;

/* Variables and functions */
 scalar_t__ CfgCheckCharForName (char) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (int) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 
 char* ZeroMalloc (int) ; 

char *CfgEscape(char *str)
{
	char *tmp;
	char *ret;
	char tmp2[16];
	UINT len;
	UINT wp, i;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	len = StrLen(str);
	tmp = ZeroMalloc(len * 3 + 2);
	if (len == 0)
	{
		// Empty character
		StrCpy(tmp, (len * 3 + 2), "$");
	}
	else
	{
		// Non null character
		wp = 0;
		for (i = 0;i < len;i++)
		{
			if (CfgCheckCharForName(str[i]))
			{
				tmp[wp++] = str[i];
			}
			else
			{
				tmp[wp++] = '$';
				Format(tmp2, sizeof(tmp2), "%02X", (UINT)str[i]);
				tmp[wp++] = tmp2[0];
				tmp[wp++] = tmp2[1];
			}
		}
	}
	ret = Malloc(StrLen(tmp) + 1);
	StrCpy(ret, 0, tmp);
	Free(tmp);
	return ret;
}