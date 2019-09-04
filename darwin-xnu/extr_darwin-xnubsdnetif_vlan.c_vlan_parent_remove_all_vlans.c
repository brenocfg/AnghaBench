#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlan_parent_ref ;
struct ifnet {int dummy; } ;
typedef  TYPE_2__* ifvlan_ref ;
struct TYPE_16__ {struct ifnet* ifv_ifp; } ;
struct TYPE_15__ {int /*<<< orphan*/  vlp_vlan_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFEF_VLAN ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_detach (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_set_eflags (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifv_vlan_list ; 
 TYPE_1__* parent_list_lookup (struct ifnet*) ; 
 int /*<<< orphan*/  vlan_lock () ; 
 scalar_t__ vlan_parent_flags_detaching (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_flags_set_detaching (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_release (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_retain (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_signal (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlan_parent_wait (TYPE_1__*,char*) ; 
 int vlan_remove (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_unlock () ; 
 int /*<<< orphan*/  vlp_parent_list ; 

__attribute__((used)) static void
vlan_parent_remove_all_vlans(struct ifnet * p)
{
    ifvlan_ref 		ifv;
    int			need_vlp_release = 0;
    ifvlan_ref		next;
    vlan_parent_ref	vlp;

    vlan_lock();
    vlp = parent_list_lookup(p);
    if (vlp == NULL || vlan_parent_flags_detaching(vlp)) {
	/* no VLAN's */
	vlan_unlock();
	return;
    }
    vlan_parent_flags_set_detaching(vlp);
    vlan_parent_retain(vlp);
    vlan_parent_wait(vlp, "vlan_parent_remove_all_vlans");
    need_vlp_release++;

    /* check again */
    if (parent_list_lookup(p) != vlp) {
	goto signal_done;
    }

    for (ifv = LIST_FIRST(&vlp->vlp_vlan_list); ifv != NULL; ifv = next) {
	struct ifnet *	ifp = ifv->ifv_ifp;
	int		removed;

	next = LIST_NEXT(ifv, ifv_vlan_list);
	removed = vlan_remove(ifv, FALSE);
	if (removed) {
	    vlan_unlock();
	    ifnet_detach(ifp);
	    vlan_lock();
	}
    }

    /* the vlan parent has no more VLAN's */
    ifnet_set_eflags(p, 0, IFEF_VLAN); /* clear IFEF_VLAN */

    LIST_REMOVE(vlp, vlp_parent_list);
    need_vlp_release++;	/* one for being in the list */
    need_vlp_release++; /* final reference */

 signal_done:
    vlan_parent_signal(vlp, "vlan_parent_remove_all_vlans");
    vlan_unlock();

    while (need_vlp_release--) {
	vlan_parent_release(vlp);
    }
    return;
}