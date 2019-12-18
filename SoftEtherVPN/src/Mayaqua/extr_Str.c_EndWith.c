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
 scalar_t__ StrCmpi (char*,char*) ; 
 scalar_t__ StrLen (char*) ; 

bool EndWith(char *str, char *key)
{
	UINT str_len;
	UINT key_len;
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

	if (StrCmpi(str + (str_len - key_len), key) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}