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
typedef  int /*<<< orphan*/  uint64_t ;
struct socket {int so_flags; int /*<<< orphan*/ * so_cfil; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_UDP (struct socket*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAX_CONTENT_FILTER ; 
 int SHUT_RD ; 
 int SHUT_WR ; 
 int SOF_CONTENT_FILTER ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  cfil_dispatch_disconnect_event (struct socket*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cfil_sock_udp_notify_shutdown (struct socket*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

void
cfil_sock_notify_shutdown(struct socket *so, int how)
{
	errno_t error = 0;
	int kcunit;

	if (IS_UDP(so)) {
		cfil_sock_udp_notify_shutdown(so, how, 0, 0);
		return;
	}

	if ((so->so_flags & SOF_CONTENT_FILTER) == 0 || so->so_cfil == NULL)
		return;

	CFIL_LOG(LOG_INFO, "so %llx how %d",
		(uint64_t)VM_KERNEL_ADDRPERM(so), how);

	socket_lock_assert_owned(so);

	for (kcunit = 1; kcunit <= MAX_CONTENT_FILTER; kcunit++) {
		/* Disconnect incoming side */
		if (how != SHUT_WR)
			error = cfil_dispatch_disconnect_event(so, so->so_cfil, kcunit, 0);
		/* Disconnect outgoing side */
		if (how != SHUT_RD)
			error = cfil_dispatch_disconnect_event(so, so->so_cfil, kcunit, 1);
	}
}