#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ifnet_t ;
struct TYPE_6__ {int lqm_state; } ;
struct TYPE_7__ {TYPE_1__ if_interface_state; } ;

/* Variables and functions */
 int IFNET_LQM_THRESH_OFF ; 
 int /*<<< orphan*/  ifnet_lock_done (TYPE_2__*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (TYPE_2__*) ; 

int
ifnet_link_quality(ifnet_t ifp)
{
	int lqm;

	if (ifp == NULL)
		return (IFNET_LQM_THRESH_OFF);

	ifnet_lock_shared(ifp);
	lqm = ifp->if_interface_state.lqm_state;
	ifnet_lock_done(ifp);

	return (lqm);
}