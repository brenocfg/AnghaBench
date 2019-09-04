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
typedef  int UINT ;
typedef  int BYTE ;

/* Variables and functions */

UINT GetUtf8Type(BYTE *s, UINT size, UINT offset)
{
	// Validate arguments
	if (s == NULL)
	{
		return 0;
	}
	if ((offset + 1) > size)
	{
		return 0;
	}
	if ((s[offset] & 0x80) == 0)
	{
		// 1 byte
		return 1;
	}
	if ((s[offset] & 0x20) == 0)
	{
		// 2 bytes
		if ((offset + 2) > size)
		{
			return 0;
		}
		return 2;
	}
	// 3 bytes
	if ((offset + 3) > size)
	{
		return 0;
	}
	return 3;
}