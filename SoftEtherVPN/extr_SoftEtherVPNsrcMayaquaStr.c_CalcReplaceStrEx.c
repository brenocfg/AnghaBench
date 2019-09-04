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
 scalar_t__ INFINITE ; 
 scalar_t__ SearchStrEx (char*,char*,scalar_t__,int) ; 
 scalar_t__ StrLen (char*) ; 

UINT CalcReplaceStrEx(char *string, char *old_keyword, char *new_keyword, bool case_sensitive)
{
	UINT i, num;
	UINT len_string, len_old, len_new;
	// Validate arguments
	if (string == NULL || old_keyword == NULL || new_keyword == NULL)
	{
		return 0;
	}

	// Get the length of the string
	len_string = StrLen(string);
	len_old = StrLen(old_keyword);
	len_new = StrLen(new_keyword);

	if (len_old == len_new)
	{
		return len_string;
	}

	// Search
	num = 0;
	i = 0;
	while (true)
	{
		i = SearchStrEx(string, old_keyword, i, case_sensitive);
		if (i == INFINITE)
		{
			break;
		}
		i += len_old;
		num++;
	}

	// Calculation
	return len_string + len_new * num - len_old * num;
}