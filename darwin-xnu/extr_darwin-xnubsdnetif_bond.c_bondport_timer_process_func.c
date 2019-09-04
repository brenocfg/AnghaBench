#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  devtimer_ref ;
typedef  int devtimer_process_func_event ;
typedef  TYPE_1__* bondport_ref ;
struct TYPE_6__ {int /*<<< orphan*/  verbose; } ;
struct TYPE_5__ {int ifb_last_link_event; struct ifnet* ifb_ifp; int /*<<< orphan*/  ifb_name; int /*<<< orphan*/ * ifb_active_lag; } ;
struct TYPE_4__ {TYPE_2__* po_bond; } ;

/* Variables and functions */
 int KEV_DL_LINK_OFF ; 
 int KEV_DL_LINK_ON ; 
 int /*<<< orphan*/  bond_lock () ; 
 int /*<<< orphan*/  bond_unlock () ; 
 int /*<<< orphan*/  devtimer_arg0 (int /*<<< orphan*/ ) ; 
#define  devtimer_process_func_event_lock 129 
#define  devtimer_process_func_event_unlock 128 
 int /*<<< orphan*/  devtimer_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devtimer_retain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devtimer_valid (int /*<<< orphan*/ ) ; 
 TYPE_3__* g_bond ; 
 int /*<<< orphan*/  ifbond_selection (TYPE_2__*) ; 
 int /*<<< orphan*/  interface_link_event (struct ifnet*,int) ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bondport_timer_process_func(devtimer_ref timer, 
			    devtimer_process_func_event event)
{
    bondport_ref	p;

    switch (event) {
    case devtimer_process_func_event_lock:
	bond_lock();
	devtimer_retain(timer);
	break;
    case devtimer_process_func_event_unlock:
	if (devtimer_valid(timer)) {
	    /* as long as the devtimer is valid, we can look at arg0 */
	    int			event_code = 0;
	    struct ifnet *	bond_ifp = NULL;

	    p = (bondport_ref)devtimer_arg0(timer);
	    if (ifbond_selection(p->po_bond)) {
		event_code = (p->po_bond->ifb_active_lag == NULL) 
		    ? KEV_DL_LINK_OFF 
		    : KEV_DL_LINK_ON;
		/* XXX need to take a reference on bond_ifp */
		bond_ifp = p->po_bond->ifb_ifp;
		p->po_bond->ifb_last_link_event = event_code;
	    }
	    else {
		event_code = (p->po_bond->ifb_active_lag == NULL) 
		    ? KEV_DL_LINK_OFF 
		    : KEV_DL_LINK_ON;
		if (event_code != p->po_bond->ifb_last_link_event) {
		    if (g_bond->verbose) {
			timestamp_printf("%s: (timer) generating LINK event\n",
					 p->po_bond->ifb_name);
		    }
		    bond_ifp = p->po_bond->ifb_ifp;
		    p->po_bond->ifb_last_link_event = event_code;
		}
	    }
	    devtimer_release(timer);
	    bond_unlock();
	    if (bond_ifp != NULL) {
		interface_link_event(bond_ifp, event_code);
	    }
	}
	else {
	    /* timer is going away */
	    devtimer_release(timer);
	    bond_unlock();
	}
	break;
    default:
	break;
    }
}