#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlan_parent_ref ;
struct ifnet {int dummy; } ;
typedef  TYPE_2__* ifvlan_ref ;
struct TYPE_13__ {int /*<<< orphan*/  ifv_multicast; } ;
struct TYPE_12__ {struct ifnet* vlp_ifp; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_2__* ifnet_get_ifvlan_retained (struct ifnet*) ; 
 scalar_t__ ifnet_ifvlan_vlan_parent_ok (struct ifnet*,TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* ifvlan_get_vlan_parent_retained (TYPE_2__*) ; 
 int /*<<< orphan*/  ifvlan_release (TYPE_2__*) ; 
 int multicast_list_program (int /*<<< orphan*/ *,struct ifnet*,struct ifnet*) ; 
 int /*<<< orphan*/  vlan_lock () ; 
 int /*<<< orphan*/  vlan_parent_release (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_signal (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlan_parent_wait (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlan_unlock () ; 

__attribute__((used)) static int
vlan_setmulti(struct ifnet * ifp)
{
    int			error = 0;
    ifvlan_ref 		ifv;
    struct ifnet *	p;
    vlan_parent_ref	vlp = NULL;

    vlan_lock();
    ifv = ifnet_get_ifvlan_retained(ifp);
    if (ifv == NULL) {
	goto unlock_done;
    }
    vlp = ifvlan_get_vlan_parent_retained(ifv);
    if (vlp == NULL) {
	/* no parent, no need to program the multicast filter */
	goto unlock_done;
    }
    vlan_parent_wait(vlp, "vlan_setmulti");

    /* check again, things could have changed */
    if (ifnet_ifvlan_vlan_parent_ok(ifp, ifv, vlp) == FALSE) {
	goto signal_done;
    }
    p = vlp->vlp_ifp;
    vlan_unlock();

    /* update parent interface with our multicast addresses */
    error = multicast_list_program(&ifv->ifv_multicast, ifp, p);

    vlan_lock();

 signal_done:
    vlan_parent_signal(vlp, "vlan_setmulti");

 unlock_done:
    vlan_unlock();
    if (ifv != NULL) {
	ifvlan_release(ifv);
    }
    if (vlp != NULL) {
	vlan_parent_release(vlp);
    }
    return (error);
}