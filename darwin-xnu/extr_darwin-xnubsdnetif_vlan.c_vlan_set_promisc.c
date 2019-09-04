#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlan_parent_ref ;
struct ifnet {int dummy; } ;
typedef  TYPE_2__* ifvlan_ref ;
struct TYPE_9__ {TYPE_1__* ifv_vlp; } ;
struct TYPE_8__ {int /*<<< orphan*/  vlp_ifp; } ;

/* Variables and functions */
 int EBUSY ; 
 int IFF_PROMISC ; 
 int ifnet_flags (struct ifnet*) ; 
 TYPE_2__* ifnet_get_ifvlan_retained (struct ifnet*) ; 
 int ifnet_set_promiscuous (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifvlan_flags_clear_promisc (TYPE_2__*) ; 
 scalar_t__ ifvlan_flags_promisc (TYPE_2__*) ; 
 int /*<<< orphan*/  ifvlan_flags_set_promisc (TYPE_2__*) ; 
 int /*<<< orphan*/  ifvlan_release (TYPE_2__*) ; 
 int /*<<< orphan*/  vlan_lock () ; 
 int /*<<< orphan*/  vlan_unlock () ; 

__attribute__((used)) static int
vlan_set_promisc(struct ifnet * ifp)
{
    int 			error = 0;
    ifvlan_ref			ifv;
    vlan_parent_ref		vlp;

    vlan_lock();
    ifv = ifnet_get_ifvlan_retained(ifp);
    if (ifv == NULL) {
	error = EBUSY;
	goto done;
    }

    vlp = ifv->ifv_vlp;
    if (vlp == NULL) {
	goto done;
    }
    if ((ifnet_flags(ifp) & IFF_PROMISC) != 0) {
	if (!ifvlan_flags_promisc(ifv)) {
	    error = ifnet_set_promiscuous(vlp->vlp_ifp, 1);
	    if (error == 0) {
		ifvlan_flags_set_promisc(ifv);
	    }
	}
    } else {
	if (ifvlan_flags_promisc(ifv)) {
	    error = ifnet_set_promiscuous(vlp->vlp_ifp, 0);
	    if (error == 0) {
		ifvlan_flags_clear_promisc(ifv);
	    }
	}
    }
 done:
    vlan_unlock();
    if (ifv != NULL) {
	ifvlan_release(ifv);
    }
    return (error);
}