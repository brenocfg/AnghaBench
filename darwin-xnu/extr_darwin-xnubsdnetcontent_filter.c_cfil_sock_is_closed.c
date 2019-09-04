#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct socket {int so_flags; TYPE_1__* so_cfil; } ;
typedef  scalar_t__ errno_t ;
struct TYPE_6__ {int /*<<< orphan*/  cfi_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFIF_SOCK_CLOSED ; 
 int /*<<< orphan*/  CFIL_INFO_VERIFY (TYPE_1__*) ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_UDP (struct socket*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAX_CONTENT_FILTER ; 
 int SOF_CONTENT_FILTER ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 scalar_t__ cfil_acquire_sockbuf (struct socket*,TYPE_1__*,int) ; 
 scalar_t__ cfil_dispatch_closed_event (struct socket*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  cfil_flush_queues (struct socket*,TYPE_1__*) ; 
 int /*<<< orphan*/  cfil_release_sockbuf (struct socket*,int) ; 
 int /*<<< orphan*/  cfil_service_inject_queue (struct socket*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  cfil_sock_udp_is_closed (struct socket*) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

void
cfil_sock_is_closed(struct socket *so)
{
	errno_t error = 0;
	int kcunit;

	if (IS_UDP(so)) {
		cfil_sock_udp_is_closed(so);
		return;
	}

	if ((so->so_flags & SOF_CONTENT_FILTER) == 0 || so->so_cfil == NULL)
		return;

	CFIL_LOG(LOG_INFO, "so %llx", (uint64_t)VM_KERNEL_ADDRPERM(so));

	socket_lock_assert_owned(so);

	for (kcunit = 1; kcunit <= MAX_CONTENT_FILTER; kcunit++) {
		/* Let the filters know of the closing */
		error = cfil_dispatch_closed_event(so, so->so_cfil, kcunit);
	}

	/* Last chance to push passed data out */
	error = cfil_acquire_sockbuf(so, so->so_cfil, 1);
	if (error == 0)
		cfil_service_inject_queue(so, so->so_cfil, 1);
	cfil_release_sockbuf(so, 1);

	so->so_cfil->cfi_flags |= CFIF_SOCK_CLOSED;

	/* Pending data needs to go */
	cfil_flush_queues(so, so->so_cfil);

	CFIL_INFO_VERIFY(so->so_cfil);
}