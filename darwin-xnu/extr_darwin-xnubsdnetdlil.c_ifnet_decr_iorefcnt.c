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
struct ifnet {scalar_t__ if_refio; int if_refflags; int /*<<< orphan*/  if_ref_lock; } ;

/* Variables and functions */
 int IFRF_ATTACHED ; 
 int IFRF_DETACHING ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

void
ifnet_decr_iorefcnt(struct ifnet *ifp)
{
	lck_mtx_lock_spin(&ifp->if_ref_lock);
	VERIFY(ifp->if_refio > 0);
	VERIFY(ifp->if_refflags & (IFRF_ATTACHED | IFRF_DETACHING));
	ifp->if_refio--;

	/*
	 * if there are no more outstanding io references, wakeup the
	 * ifnet_detach thread if detaching flag is set.
	 */
	if (ifp->if_refio == 0 && (ifp->if_refflags & IFRF_DETACHING))
		wakeup(&(ifp->if_refio));

	lck_mtx_unlock(&ifp->if_ref_lock);
}