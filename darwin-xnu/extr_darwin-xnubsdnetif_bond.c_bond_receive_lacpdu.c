#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mbuf {scalar_t__ m_data; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  lacpdu_ref ;
typedef  TYPE_1__* ifbond_ref ;
typedef  TYPE_2__* bondport_ref ;
struct TYPE_9__ {scalar_t__ verbose; } ;
struct TYPE_8__ {scalar_t__ po_enabled; TYPE_1__* po_bond; } ;
struct TYPE_7__ {scalar_t__ ifb_mode; int ifb_last_link_event; struct ifnet* ifb_ifp; int /*<<< orphan*/  ifb_name; int /*<<< orphan*/ * ifb_active_lag; } ;

/* Variables and functions */
 int IFEF_BOND ; 
 scalar_t__ IF_BOND_MODE_LACP ; 
 int KEV_DL_LINK_OFF ; 
 int KEV_DL_LINK_ON ; 
 int /*<<< orphan*/  bond_lock () ; 
 TYPE_2__* bond_lookup_port (struct ifnet*) ; 
 int /*<<< orphan*/  bond_unlock () ; 
 int /*<<< orphan*/  bondport_receive_lacpdu (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* g_bond ; 
 scalar_t__ ifbond_selection (TYPE_1__*) ; 
 int ifnet_eflags (struct ifnet*) ; 
 int /*<<< orphan*/  interface_link_event (struct ifnet*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bond_receive_lacpdu(struct mbuf * m, struct ifnet * port_ifp)
{
    struct ifnet *		bond_ifp = NULL;
    ifbond_ref			ifb;
    int				event_code = 0;
    bondport_ref		p;

    bond_lock();
    if ((ifnet_eflags(port_ifp) & IFEF_BOND) == 0) {
	goto done;
    }
    p = bond_lookup_port(port_ifp);
    if (p == NULL) {
	goto done;
    }
    if (p->po_enabled == 0) {
	goto done;
    }
    ifb = p->po_bond;
    if (ifb->ifb_mode != IF_BOND_MODE_LACP) {
	goto done;
    }
    bondport_receive_lacpdu(p, (lacpdu_ref)m->m_data);
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
		timestamp_printf("%s: (receive) generating LINK event\n",
				 ifb->ifb_name);
	    }
	    bond_ifp = ifb->ifb_ifp;
	    ifb->ifb_last_link_event = event_code;
	}
    }

 done:
    bond_unlock();
    if (bond_ifp != NULL) {
	interface_link_event(bond_ifp, event_code);
    }
    m_freem(m);
    return;
}