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
typedef  int USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int Endian16 (int) ; 

bool IsNetbiosRegistrationPacket(UCHAR *buf, UINT size)
{
	// Validate arguments
	if (buf == NULL || size == 0)
	{
		return false;
	}

	if (size >= 4)
	{
		USHORT us = *((USHORT *)(buf + 2));

		us = Endian16(us);

		if (((us & 0x7800) >> 11) == 5)
		{
			return true;
		}
	}

	return false;
}