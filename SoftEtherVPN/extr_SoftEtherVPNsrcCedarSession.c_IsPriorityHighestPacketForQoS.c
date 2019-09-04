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
typedef  int UCHAR ;

/* Variables and functions */

bool IsPriorityHighestPacketForQoS(void *data, UINT size)
{
	UCHAR *buf;
	// Validate arguments
	if (data == NULL)
	{
		return false;
	}

	buf = (UCHAR *)data;
	if (size >= 16)
	{
		if (buf[12] == 0x08 && buf[13] == 0x00 && buf[15] != 0x00 && buf[15] != 0x08)
		{
			// IPv4 packet and ToS != 0
			return true;
		}

		if (size >= 34 && size <= 128)
		{
			if (buf[12] == 0x08 && buf[13] == 0x00 && buf[23] == 0x01)
			{
				// IMCPv4 packet
				return true;
			}
		}
	}

	return false;
}