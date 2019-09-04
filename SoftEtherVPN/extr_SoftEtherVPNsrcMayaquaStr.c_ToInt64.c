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
 size_t StrLen (char*) ; 

UINT64 ToInt64(char *str)
{
	UINT len, i;
	UINT64 ret = 0;
	// Validate arguments
	if (str == NULL)
	{
		return 0;
	}

	len = StrLen(str);
	for (i = 0;i < len;i++)
	{
		char c = str[i];
		if (c != ',')
		{
			if ('0' <= c && c <= '9')
			{
				ret = ret * (UINT64)10 + (UINT64)(c - '0');
			}
			else
			{
				break;
			}
		}
	}

	return ret;
}