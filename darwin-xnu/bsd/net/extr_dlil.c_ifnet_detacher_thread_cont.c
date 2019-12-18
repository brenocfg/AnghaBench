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
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ PZERO ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlil_if_lock () ; 
 int /*<<< orphan*/  dlil_if_lock_assert () ; 
 int /*<<< orphan*/  dlil_if_unlock () ; 
 int /*<<< orphan*/  dlil_ifnet_lock ; 
 int /*<<< orphan*/  ifnet_delayed_run ; 
 int /*<<< orphan*/  ifnet_detach_final (struct ifnet*) ; 
 scalar_t__ ifnet_detaching_cnt ; 
 struct ifnet* ifnet_detaching_dequeue () ; 
 int /*<<< orphan*/  ifnet_detaching_head ; 
 int /*<<< orphan*/  msleep0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ,int (*) (int)) ; 

__attribute__((used)) static int
ifnet_detacher_thread_cont(int err)
{
#pragma unused(err)
	struct ifnet *ifp;

	for (;;) {
		dlil_if_lock_assert();
		while (ifnet_detaching_cnt == 0) {
			(void) msleep0(&ifnet_delayed_run, &dlil_ifnet_lock,
			    (PZERO - 1), "ifnet_detacher_cont", 0,
			    ifnet_detacher_thread_cont);
			/* NOTREACHED */
		}

		VERIFY(TAILQ_FIRST(&ifnet_detaching_head) != NULL);

		/* Take care of detaching ifnet */
		ifp = ifnet_detaching_dequeue();
		if (ifp != NULL) {
			dlil_if_unlock();
			ifnet_detach_final(ifp);
			dlil_if_lock();
		}
	}
}