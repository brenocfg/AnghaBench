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
typedef  int UINT64 ;
typedef  size_t UINT ;

/* Variables and functions */

UINT64 Json_ToInt64Ex(char *str, char **endptr, bool *error)
{
	UINT i;
	UINT64 ret = 0;
	if (error != NULL) *error = true;
	// Validate arguments
	if (str == NULL)
	{
		if (endptr != NULL)
		{
			*endptr = NULL;
		}
		return 0;
	}

	for (i = 0;;i++)
	{
		char c = str[i];
		if (endptr != NULL)
		{
			*endptr = &str[i];
		}
		if (c == 0)
		{
			break;
		}
		if ('0' <= c && c <= '9')
		{
			ret = ret * (UINT64)10 + (UINT64)(c - '0');
			if (error != NULL) *error = false;
		}
		else
		{
			break;
		}
	}

	return ret;
}