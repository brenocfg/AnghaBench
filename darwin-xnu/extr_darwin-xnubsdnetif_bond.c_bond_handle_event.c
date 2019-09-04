#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct media_info {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ifnet {int dummy; } ;
typedef  TYPE_1__* ifbond_ref ;
typedef  TYPE_2__* bondport_ref ;
struct TYPE_10__ {scalar_t__ verbose; } ;
struct TYPE_9__ {int /*<<< orphan*/  po_enabled; struct media_info po_media_info; int /*<<< orphan*/  po_ifp; TYPE_1__* po_bond; } ;
struct TYPE_8__ {int ifb_distributing_count; scalar_t__ ifb_mode; int ifb_last_link_event; struct ifnet* ifb_ifp; int /*<<< orphan*/  ifb_name; int /*<<< orphan*/ * ifb_active_lag; } ;

/* Variables and functions */
 scalar_t__ IF_BOND_MODE_LACP ; 
#define  KEV_DL_IF_DETACHED 130 
#define  KEV_DL_LINK_OFF 129 
#define  KEV_DL_LINK_ON 128 
 int /*<<< orphan*/  bond_lock () ; 
 TYPE_2__* bond_lookup_port (struct ifnet*) ; 
 int /*<<< orphan*/  bond_remove_interface (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_unlock () ; 
 int /*<<< orphan*/  bondport_link_status_changed (TYPE_2__*) ; 
 TYPE_4__* g_bond ; 
 scalar_t__ ifbond_selection (TYPE_1__*) ; 
 int /*<<< orphan*/  interface_link_event (struct ifnet*,int) ; 
 struct media_info interface_media_info (struct ifnet*) ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bond_handle_event(struct ifnet * port_ifp, int event_code)
{
    struct ifnet *	bond_ifp = NULL;
    ifbond_ref		ifb;
    int			old_distributing_count;
    bondport_ref	p;
    struct media_info	media_info = { 0, 0};

    switch (event_code) {
    case KEV_DL_IF_DETACHED:
	break;
    case KEV_DL_LINK_OFF:
    case KEV_DL_LINK_ON:
	media_info = interface_media_info(port_ifp);
	break;
    default:
	return;
    }
    bond_lock();
    p = bond_lookup_port(port_ifp);
    if (p == NULL) {
	bond_unlock();
	return;
    }
    ifb = p->po_bond;
    old_distributing_count = ifb->ifb_distributing_count;
    switch (event_code) {
    case KEV_DL_IF_DETACHED:
	bond_remove_interface(ifb, p->po_ifp);
	break;
    case KEV_DL_LINK_OFF:
    case KEV_DL_LINK_ON:
	p->po_media_info = media_info;
	if (p->po_enabled) {
	    bondport_link_status_changed(p);
	}
	break;
    }
    /* generate a link-event */
    if (ifb->ifb_mode == IF_BOND_MODE_LACP) {
	if (ifbond_selection(ifb)) {
	    event_code = (ifb->ifb_active_lag == NULL) 
		? KEV_DL_LINK_OFF 
		: KEV_DL_LINK_ON;
	    /* XXX need to take a reference on bond_ifp */
	    bond_ifp = ifb->ifb_ifp;
	    ifb->ifb_last_link_event = event_code;
	}
	else {
	    event_code = (ifb->ifb_active_lag == NULL) 
		? KEV_DL_LINK_OFF 
		: KEV_DL_LINK_ON;
	    if (event_code != ifb->ifb_last_link_event) {
		if (g_bond->verbose) {
		    timestamp_printf("%s: (event) generating LINK event\n",
				     ifb->ifb_name);
		}
		bond_ifp = ifb->ifb_ifp;
		ifb->ifb_last_link_event = event_code;
	    }
	}
    }
    else {
	/*
	 * if the distributing array membership changed from 0 <-> !0
	 * generate a link event
	 */
	if (old_distributing_count == 0 
	    && ifb->ifb_distributing_count != 0) {
	    event_code = KEV_DL_LINK_ON;
	}
	else if (old_distributing_count != 0 
		 && ifb->ifb_distributing_count == 0) {
	    event_code = KEV_DL_LINK_OFF;
	}
	if (event_code != 0 && event_code != ifb->ifb_last_link_event) {
	    bond_ifp = ifb->ifb_ifp;
	    ifb->ifb_last_link_event = event_code;
	}
    }

    bond_unlock();
    if (bond_ifp != NULL) {
	interface_link_event(bond_ifp, event_code);
    }
    return;
}