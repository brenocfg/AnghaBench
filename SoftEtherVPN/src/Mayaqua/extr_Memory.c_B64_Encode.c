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
typedef  int BYTE ;

/* Variables and functions */
 char B64_CodeToChar (int) ; 
 scalar_t__ TRUE ; 

int B64_Encode(char *set, char *source, int len)
{
	BYTE *src;
	int i,j;
	src = (BYTE *)source;
	j = 0;
	i = 0;
	if (!len)
	{
		return 0;
	}
	while (TRUE)
	{
		if (i >= len)
		{
			return j;
		}
		if (set)
		{
			set[j] = B64_CodeToChar((src[i]) >> 2);
		}
		if (i + 1 >= len)
		{
			if (set)
			{
				set[j + 1] = B64_CodeToChar((src[i] & 0x03) << 4);
				set[j + 2] = '=';
				set[j + 3] = '=';
			}
			return j + 4;
		}
		if (set)
		{
			set[j + 1] = B64_CodeToChar(((src[i] & 0x03) << 4) + ((src[i + 1] >> 4)));
		}
		if (i + 2 >= len)
		{
			if (set)
			{
				set[j + 2] = B64_CodeToChar((src[i + 1] & 0x0f) << 2);
				set[j + 3] = '=';
			}
			return j + 4;
		}
		if (set)
		{
			set[j + 2] = B64_CodeToChar(((src[i + 1] & 0x0f) << 2) + ((src[i + 2] >> 6)));
			set[j + 3] = B64_CodeToChar(src[i + 2] & 0x3f);
		}
		i += 3;
		j += 4;
	}
}