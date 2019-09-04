#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct socket {int so_flags; TYPE_3__* so_cfil; TYPE_2__* so_proto; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_8__ {int /*<<< orphan*/  cfs_close_wait_timeout; int /*<<< orphan*/  cfs_close_wait; } ;
struct TYPE_7__ {int /*<<< orphan*/  cfi_flags; } ;
struct TYPE_6__ {TYPE_1__* pr_domain; int /*<<< orphan*/ * (* pr_getlock ) (struct socket*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFIF_CLOSE_WAIT ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ IS_UDP (struct socket*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int PCATCH ; 
 int /*<<< orphan*/  PR_F_WILLUNLOCK ; 
 int PSOCK ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int SOF_CONTENT_FILTER ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int cfil_close_wait_timeout ; 
 scalar_t__ cfil_filters_attached (struct socket*) ; 
 int /*<<< orphan*/  cfil_sock_notify_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfil_sock_udp_close_wait (struct socket*) ; 
 TYPE_4__ cfil_stats ; 
 int msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,struct timespec*) ; 
 int /*<<< orphan*/ * stub1 (struct socket*,int /*<<< orphan*/ ) ; 

void
cfil_sock_close_wait(struct socket *so)
{
	lck_mtx_t *mutex_held;
	struct timespec ts;
	int error;

	if (IS_UDP(so)) {
		cfil_sock_udp_close_wait(so);
		return;
	}

	if ((so->so_flags & SOF_CONTENT_FILTER) == 0 || so->so_cfil == NULL)
		return;

	CFIL_LOG(LOG_INFO, "so %llx", (uint64_t)VM_KERNEL_ADDRPERM(so));

	if (so->so_proto->pr_getlock != NULL)
		mutex_held = (*so->so_proto->pr_getlock)(so, PR_F_WILLUNLOCK);
	else
		mutex_held = so->so_proto->pr_domain->dom_mtx;
	LCK_MTX_ASSERT(mutex_held, LCK_MTX_ASSERT_OWNED);

	while (cfil_filters_attached(so)) {
		/*
		 * Notify the filters we are going away so they can detach
		 */
		cfil_sock_notify_shutdown(so, SHUT_RDWR);

		/*
		 * Make sure we need to wait after the filter are notified
		 * of the disconnection
		 */
		if (cfil_filters_attached(so) == 0)
			break;

		CFIL_LOG(LOG_INFO, "so %llx waiting",
			(uint64_t)VM_KERNEL_ADDRPERM(so));

		ts.tv_sec = cfil_close_wait_timeout / 1000;
		ts.tv_nsec = (cfil_close_wait_timeout % 1000) *
			NSEC_PER_USEC * 1000;

		OSIncrementAtomic(&cfil_stats.cfs_close_wait);
		so->so_cfil->cfi_flags |= CFIF_CLOSE_WAIT;
		error = msleep((caddr_t)so->so_cfil, mutex_held,
			PSOCK | PCATCH, "cfil_sock_close_wait", &ts);
		so->so_cfil->cfi_flags &= ~CFIF_CLOSE_WAIT;

		CFIL_LOG(LOG_NOTICE, "so %llx timed out %d",
			(uint64_t)VM_KERNEL_ADDRPERM(so), (error != 0));

		/*
		 * Force close in case of timeout
		 */
		if (error != 0) {
			OSIncrementAtomic(&cfil_stats.cfs_close_wait_timeout);
			break;
		}
	}

}