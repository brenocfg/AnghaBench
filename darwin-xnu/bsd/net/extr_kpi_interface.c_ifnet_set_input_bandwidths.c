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
struct if_bandwidths {scalar_t__ eff_bw; scalar_t__ max_bw; } ;
struct ifnet {struct if_bandwidths if_input_bw; int /*<<< orphan*/  if_link_status_lock; int /*<<< orphan*/ * if_link_status; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSQ_EV_LINK_BANDWIDTH ; 
 scalar_t__ IFNET_IS_WIFI (struct ifnet*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ifnet_set_link_status_inbw (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_update_rcv (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 

errno_t
ifnet_set_input_bandwidths(struct ifnet *ifp, struct if_bandwidths *bw)
{
	struct if_bandwidths old_bw;

	VERIFY(ifp != NULL && bw != NULL);

	old_bw = ifp->if_input_bw;
	if (bw->eff_bw != 0)
		ifp->if_input_bw.eff_bw = bw->eff_bw;
	if (bw->max_bw != 0)
		ifp->if_input_bw.max_bw = bw->max_bw;
	if (ifp->if_input_bw.eff_bw > ifp->if_input_bw.max_bw)
		ifp->if_input_bw.max_bw = ifp->if_input_bw.eff_bw;
	else if (ifp->if_input_bw.eff_bw == 0)
		ifp->if_input_bw.eff_bw = ifp->if_input_bw.max_bw;

	if (IFNET_IS_WIFI(ifp) && ifp->if_link_status != NULL) {
		lck_rw_lock_exclusive(&ifp->if_link_status_lock);
		ifnet_set_link_status_inbw(ifp);
		lck_rw_done(&ifp->if_link_status_lock);
	}

	if (old_bw.eff_bw != ifp->if_input_bw.eff_bw ||
	    old_bw.max_bw != ifp->if_input_bw.max_bw)
		ifnet_update_rcv(ifp, CLASSQ_EV_LINK_BANDWIDTH);

	return (0);
}