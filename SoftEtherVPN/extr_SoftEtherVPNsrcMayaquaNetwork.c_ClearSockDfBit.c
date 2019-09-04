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
typedef  int /*<<< orphan*/  SOCK ;

/* Variables and functions */

void ClearSockDfBit(SOCK *s)
{
#ifdef	IP_PMTUDISC_DONT
#ifdef	IP_MTU_DISCOVER
	UINT value = IP_PMTUDISC_DONT;
	if (s == NULL)
	{
		return;
	}

	(void)setsockopt(s->socket, IPPROTO_IP, IP_MTU_DISCOVER, (char *)&value, sizeof(value));
#endif	// IP_MTU_DISCOVER
#endif	// IP_PMTUDISC_DONT
}