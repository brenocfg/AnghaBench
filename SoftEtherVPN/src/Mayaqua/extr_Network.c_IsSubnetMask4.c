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
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int IPToUINT (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsLittleEndian () ; 
 int Swap32 (int) ; 

bool IsSubnetMask4(IP *ip)
{
	UINT i;
	// Validate arguments
	if (ip == NULL)
	{
		return false;
	}

	if (IsIP6(ip))
	{
		return false;
	}

	i = IPToUINT(ip);

	if (IsLittleEndian())
	{
		i = Swap32(i);
	}

	switch (i)
	{
	case 0x00000000:
	case 0x80000000:
	case 0xC0000000:
	case 0xE0000000:
	case 0xF0000000:
	case 0xF8000000:
	case 0xFC000000:
	case 0xFE000000:
	case 0xFF000000:
	case 0xFF800000:
	case 0xFFC00000:
	case 0xFFE00000:
	case 0xFFF00000:
	case 0xFFF80000:
	case 0xFFFC0000:
	case 0xFFFE0000:
	case 0xFFFF0000:
	case 0xFFFF8000:
	case 0xFFFFC000:
	case 0xFFFFE000:
	case 0xFFFFF000:
	case 0xFFFFF800:
	case 0xFFFFFC00:
	case 0xFFFFFE00:
	case 0xFFFFFF00:
	case 0xFFFFFF80:
	case 0xFFFFFFC0:
	case 0xFFFFFFE0:
	case 0xFFFFFFF0:
	case 0xFFFFFFF8:
	case 0xFFFFFFFC:
	case 0xFFFFFFFE:
	case 0xFFFFFFFF:
		return true;
	}

	return false;
}