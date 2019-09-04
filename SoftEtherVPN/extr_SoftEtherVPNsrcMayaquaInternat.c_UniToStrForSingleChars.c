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

void UniToStrForSingleChars(char *dst, UINT dst_size, wchar_t *src)
{
	UINT i;
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return;
	}

	for (i = 0;i < UniStrLen(src) + 1;i++)
	{
		wchar_t s = src[i];
		char d;

		if (s == 0)
		{
			d = 0;
		}
		else if (s <= 0xff)
		{
			d = (char)s;
		}
		else
		{
			d = ' ';
		}

		dst[i] = d;
	}
}