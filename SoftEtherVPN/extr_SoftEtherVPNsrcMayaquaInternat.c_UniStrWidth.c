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
typedef  size_t UINT ;

/* Variables and functions */
 size_t UniStrLen (int*) ; 

UINT UniStrWidth(wchar_t *str)
{
	UINT i, len, ret;
	// Validate arguments
	if (str == NULL)
	{
		return 0;
	}

	ret = 0;
	len = UniStrLen(str);
	for (i = 0;i < len;i++)
	{
		if (str[i] <= 255)
		{
			ret++;
		}
		else
		{
			ret += 2;
		}
	}
	return ret;
}