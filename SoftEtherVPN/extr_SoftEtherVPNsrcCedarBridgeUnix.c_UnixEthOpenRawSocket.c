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

/* Variables and functions */

int UnixEthOpenRawSocket()
{
#ifdef	UNIX_LINUX
	int s;

	s = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (s < 0)
	{
		return INVALID_SOCKET;
	}
	else
	{
		return s;
	}
#else	// UNIX_LINUX
	return -1;
#endif	// UNIX_LINUX
}