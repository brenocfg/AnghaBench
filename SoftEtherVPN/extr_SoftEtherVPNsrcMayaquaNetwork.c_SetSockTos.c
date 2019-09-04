#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int CurrentTos; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */

void SetSockTos(SOCK *s, int tos)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	if (s->CurrentTos == tos)
	{
		return;
	}

#ifdef	IP_TOS
	(void)setsockopt(s->socket, IPPROTO_IP, IP_TOS, (char *)&tos, sizeof(int));
#endif	// IP_TOS

	s->CurrentTos = tos;
}