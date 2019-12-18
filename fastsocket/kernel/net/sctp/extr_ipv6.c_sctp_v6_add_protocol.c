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
 int EAGAIN ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 scalar_t__ inet6_add_protocol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_inet6addr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_inet6addr_notifier ; 
 int /*<<< orphan*/  sctpv6_protocol ; 

int sctp_v6_add_protocol(void)
{
	/* Register notifier for inet6 address additions/deletions. */
	register_inet6addr_notifier(&sctp_inet6addr_notifier);

	if (inet6_add_protocol(&sctpv6_protocol, IPPROTO_SCTP) < 0)
		return -EAGAIN;

	return 0;
}