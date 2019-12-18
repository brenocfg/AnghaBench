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
 int strlen (char*) ; 
 scalar_t__ toupper (char) ; 

int StringContains(char *str1, char *str2, int casesensitive)
{
	int len, i, j, index;

	if (str1 == NULL || str2 == NULL) return -1;

	len = strlen(str1) - strlen(str2);
	index = 0;
	for (i = 0; i <= len; i++, str1++, index++)
	{
		for (j = 0; str2[j]; j++)
		{
			if (casesensitive)
			{
				if (str1[j] != str2[j]) break;
			} //end if
			else
			{
				if (toupper(str1[j]) != toupper(str2[j])) break;
			} //end else
		} //end for
		if (!str2[j]) return index;
	} //end for
	return -1;
}