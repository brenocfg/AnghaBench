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
typedef  int wchar_t ;
typedef  int UINT ;

/* Variables and functions */
 int UniStrLen (int*) ; 

void UniTrimCrlf(wchar_t *str)
{
	UINT len;
	// Validate arguments
	if (str == NULL)
	{
		return;
	}
	len = UniStrLen(str);
	if (len == 0)
	{
		return;
	}

	if (str[len - 1] == L'\n')
	{
		if (len >= 2 && str[len - 2] == L'\r')
		{
			str[len - 2] = 0;
		}
		str[len - 1] = 0;
	}
	else if(str[len - 1] == L'\r')
	{
		str[len - 1] = 0;
	}
}