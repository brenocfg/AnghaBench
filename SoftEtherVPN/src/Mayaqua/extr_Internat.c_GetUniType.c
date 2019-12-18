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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int UINT ;
typedef  int BYTE ;

/* Variables and functions */
 scalar_t__ IsBigEndian () ; 

UINT GetUniType(wchar_t c)
{
	BYTE c1, c2;

	if (IsBigEndian())
	{
		if (sizeof(wchar_t) == 2)
		{
			c1 = ((BYTE *)&c)[0];
			c2 = ((BYTE *)&c)[1];
		}
		else
		{
			c1 = ((BYTE *)&c)[2];
			c2 = ((BYTE *)&c)[3];
		}
	}
	else
	{
		c1 = ((BYTE *)&c)[1];
		c2 = ((BYTE *)&c)[0];
	}

	if (c1 == 0)
	{
		if (c2 <= 0x7f)
		{
			// 1 byte
			return 1;
		}
		else
		{
			// 2 bytes
			return 2;
		}
	}
	if ((c1 & 0xf8) == 0)
	{
		// 2 bytes
		return 2;
	}
	// 3 bytes
	return 3;
}