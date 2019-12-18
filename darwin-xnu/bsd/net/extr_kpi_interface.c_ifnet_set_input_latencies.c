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
struct if_latencies {scalar_t__ eff_lt; scalar_t__ max_lt; } ;
struct ifnet {struct if_latencies if_input_lt; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSQ_EV_LINK_LATENCY ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ifnet_update_rcv (struct ifnet*,int /*<<< orphan*/ ) ; 

errno_t
ifnet_set_input_latencies(struct ifnet *ifp, struct if_latencies *lt)
{
	struct if_latencies old_lt;

	VERIFY(ifp != NULL && lt != NULL);

	old_lt = ifp->if_input_lt;
	if (lt->eff_lt != 0)
		ifp->if_input_lt.eff_lt = lt->eff_lt;
	if (lt->max_lt != 0)
		ifp->if_input_lt.max_lt = lt->max_lt;
	if (ifp->if_input_lt.eff_lt > ifp->if_input_lt.max_lt)
		ifp->if_input_lt.max_lt = ifp->if_input_lt.eff_lt;
	else if (ifp->if_input_lt.eff_lt == 0)
		ifp->if_input_lt.eff_lt = ifp->if_input_lt.max_lt;

	if (old_lt.eff_lt != ifp->if_input_lt.eff_lt ||
	    old_lt.max_lt != ifp->if_input_lt.max_lt)
		ifnet_update_rcv(ifp, CLASSQ_EV_LINK_LATENCY);

	return (0);
}