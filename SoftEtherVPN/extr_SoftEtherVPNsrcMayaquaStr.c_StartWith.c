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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 char* CopyStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 scalar_t__ StrLen (char*) ; 

bool StartWith(char *str, char *key)
{
	UINT str_len;
	UINT key_len;
	char *tmp;
	bool ret;
	// Validate arguments
	if (str == NULL || key == NULL)
	{
		return false;
	}

	// Comparison
	str_len = StrLen(str);
	key_len = StrLen(key);
	if (str_len < key_len)
	{
		return false;
	}
	if (str_len == 0 || key_len == 0)
	{
		return false;
	}
	tmp = CopyStr(str);
	tmp[key_len] = 0;

	if (StrCmpi(tmp, key) == 0)
	{
		ret = true;
	}
	else
	{
		ret = false;
	}

	Free(tmp);

	return ret;
}