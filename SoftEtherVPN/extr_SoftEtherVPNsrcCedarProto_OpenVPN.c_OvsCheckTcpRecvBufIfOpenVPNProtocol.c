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

bool OvsCheckTcpRecvBufIfOpenVPNProtocol(UCHAR *buf, UINT size)
{
	if (buf == NULL || size != 2)
	{
		return false;
	}

	if (buf[0] == 0x00 && buf[1] == 0x0E)
	{
		return true;
	}

	return false;
}