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
struct ifnet {int if_eflags; int if_start_flags; scalar_t__ if_start_thread; scalar_t__ if_start_delay_qlen; scalar_t__ if_start_delayed; int /*<<< orphan*/  if_start_lock; int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_start_active; int /*<<< orphan*/  if_start_req; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ IFCQ_LEN (int /*<<< orphan*/ *) ; 
 int IFEF_ENQUEUE_MULTI ; 
 int IFEF_TXSTART ; 
 int IFSF_FLOW_CONTROLLED ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_wakeup_thread (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ifnet_start_common(struct ifnet *ifp, boolean_t resetfc)
{
	if (!(ifp->if_eflags & IFEF_TXSTART))
		return;
	/*
	 * If the starter thread is inactive, signal it to do work,
	 * unless the interface is being flow controlled from below,
	 * e.g. a virtual interface being flow controlled by a real
	 * network interface beneath it, or it's been disabled via
	 * a call to ifnet_disable_output().
	 */
	lck_mtx_lock_spin(&ifp->if_start_lock);
	if (resetfc) {
		ifp->if_start_flags &= ~IFSF_FLOW_CONTROLLED;
	} else if (ifp->if_start_flags & IFSF_FLOW_CONTROLLED) {
		lck_mtx_unlock(&ifp->if_start_lock);
		return;
	}
	ifp->if_start_req++;
	if (!ifp->if_start_active && ifp->if_start_thread != THREAD_NULL &&
	    (resetfc || !(ifp->if_eflags & IFEF_ENQUEUE_MULTI) ||
	    IFCQ_LEN(&ifp->if_snd) >= ifp->if_start_delay_qlen ||
	    ifp->if_start_delayed == 0)) {
		(void) thread_wakeup_thread((caddr_t)&ifp->if_start_thread,
		    ifp->if_start_thread);
	}
	lck_mtx_unlock(&ifp->if_start_lock);
}