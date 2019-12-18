#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_1__* vlan_parent_ref ;
struct ifnet {int dummy; } ;
typedef  TYPE_2__* ifvlan_ref ;
struct TYPE_18__ {scalar_t__ ifv_flags; scalar_t__ ifv_mtufudge; int /*<<< orphan*/  ifv_multicast; TYPE_1__* ifv_vlp; struct ifnet* ifv_ifp; } ;
struct TYPE_17__ {int /*<<< orphan*/  vlp_vlan_list; struct ifnet* vlp_ifp; } ;
struct TYPE_16__ {scalar_t__ verbose; } ;

/* Variables and functions */
 scalar_t__ ETHERMTU ; 
 int FALSE ; 
 int /*<<< orphan*/  IFEF_VLAN ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_RUNNING ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFT_L2VLAN ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 TYPE_14__* g_vlan ; 
 TYPE_2__* ifnet_get_ifvlan (struct ifnet*) ; 
 char* ifnet_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_set_eflags (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_flags (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifnet_set_lladdr_and_type (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_mtu (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_offload (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  ifv_vlan_list ; 
 int /*<<< orphan*/  ifvlan_new_mtu (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ifvlan_release (TYPE_2__*) ; 
 int /*<<< orphan*/  multicast_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_assert_lock_held () ; 
 int /*<<< orphan*/  vlan_detach_protocol (struct ifnet*) ; 
 int /*<<< orphan*/  vlan_lock () ; 
 int /*<<< orphan*/  vlan_parent_flags_detaching (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_release (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_remove_vlan (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vlan_parent_retain (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_signal (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlan_parent_wait (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlan_unlock () ; 
 int /*<<< orphan*/  vlp_parent_list ; 

__attribute__((used)) static int
vlan_unconfig(ifvlan_ref ifv, int need_to_wait)
{
    struct ifnet *	ifp = ifv->ifv_ifp;
    int			last_vlan = FALSE;
    int			need_ifv_release = 0;
    int			need_vlp_release = 0;
    struct ifnet *	p;
    vlan_parent_ref	vlp;

    vlan_assert_lock_held();
    vlp = ifv->ifv_vlp;
    if (vlp == NULL) {
	return (0);
    }
    if (need_to_wait) {
	need_vlp_release++;
	vlan_parent_retain(vlp);
	vlan_parent_wait(vlp, "vlan_unconfig");

        /* check again because another thread could be in vlan_unconfig */
	if (ifv != ifnet_get_ifvlan(ifp)) {
	    goto signal_done;
	}
	if (ifv->ifv_vlp != vlp) {
	    /* vlan parent changed */
	    goto signal_done;
	}
    }

    /* ifv has a reference on vlp, need to remove it */
    need_vlp_release++;
    p = vlp->vlp_ifp;

    /* remember whether we're the last VLAN on the parent */
    if (LIST_NEXT(LIST_FIRST(&vlp->vlp_vlan_list), ifv_vlan_list) == NULL) {
	if (g_vlan->verbose) {
	    printf("vlan_unconfig: last vlan on %s%d\n",
		   ifnet_name(p), ifnet_unit(p));
	}
	last_vlan = TRUE;
    }

    /* back-out any effect our mtu might have had on the parent */
    (void)ifvlan_new_mtu(ifv, ETHERMTU - ifv->ifv_mtufudge);

    vlan_unlock();

    /* un-join multicast on parent interface */
    (void)multicast_list_remove(&ifv->ifv_multicast);

    /* Clear our MAC address. */
    ifnet_set_lladdr_and_type(ifp, NULL, 0, IFT_L2VLAN);

    /* detach VLAN "protocol" */
    if (last_vlan) {
	(void)vlan_detach_protocol(p);
    }

    vlan_lock();

    /* return to the state we were in before SIFVLAN */
    ifnet_set_mtu(ifp, 0);
    ifnet_set_flags(ifp, 0, 
		    IFF_BROADCAST | IFF_MULTICAST | IFF_SIMPLEX | IFF_RUNNING);
    ifnet_set_offload(ifp, 0);
    ifv->ifv_mtufudge = 0;

    /* Disconnect from parent. */
    vlan_parent_remove_vlan(vlp, ifv);
    ifv->ifv_flags = 0;

    /* vlan_parent has reference to ifv, remove it */
    need_ifv_release++;

    /* from this point on, no more referencing ifv */
    if (last_vlan && !vlan_parent_flags_detaching(vlp)) {
	/* the vlan parent has no more VLAN's */
	ifnet_set_eflags(p, 0, IFEF_VLAN);
	LIST_REMOVE(vlp, vlp_parent_list);

	/* one for being in the list */
	need_vlp_release++;

	/* release outside of the lock below */
	need_vlp_release++;
    }

 signal_done:
    if (need_to_wait) {
	vlan_parent_signal(vlp, "vlan_unconfig");
    }
    vlan_unlock();
    while (need_ifv_release--) {
	ifvlan_release(ifv);
    }
    while (need_vlp_release--) {	/* references to vlp */
	vlan_parent_release(vlp);
    }
    vlan_lock();
    return (0);
}