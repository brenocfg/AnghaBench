#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vlan_parent_ref ;
typedef  int u_int16_t ;
struct ifnet {int /*<<< orphan*/  if_eflags; } ;
typedef  TYPE_1__* ifvlan_ref ;
typedef  int ifnet_offload_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_12__ {scalar_t__ ifv_mtufudge; scalar_t__ ifv_encaplen; scalar_t__ ifv_flags; int /*<<< orphan*/  ifv_multicast; int /*<<< orphan*/ * ifv_vlp; } ;
struct TYPE_11__ {int /*<<< orphan*/  parent_list; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ ETHERMTU ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int FALSE ; 
 int IFEF_BOND ; 
 int /*<<< orphan*/  IFEF_VLAN ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_RUNNING ; 
 int IFF_SIMPLEX ; 
 int IFF_UP ; 
 int IFNET_VLAN_MTU ; 
 int IFNET_VLAN_TAGGING ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int TRUE ; 
 TYPE_10__* g_vlan ; 
 int ifnet_eflags (struct ifnet*) ; 
 int ifnet_flags (struct ifnet*) ; 
 TYPE_1__* ifnet_get_ifvlan (struct ifnet*) ; 
 TYPE_1__* ifnet_get_ifvlan_retained (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int ifnet_offload (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_set_eflags (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_flags (struct ifnet*,int,int) ; 
 int /*<<< orphan*/  ifnet_set_lladdr_and_type (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_mtu (struct ifnet*,scalar_t__) ; 
 int /*<<< orphan*/  ifnet_set_offload (struct ifnet*,int) ; 
 scalar_t__ ifvlan_flags_detaching (TYPE_1__*) ; 
 int /*<<< orphan*/  ifvlan_flags_set_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  ifvlan_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ifvlan_retain (TYPE_1__*) ; 
 int multicast_list_program (int /*<<< orphan*/ *,struct ifnet*,struct ifnet*) ; 
 int /*<<< orphan*/ * parent_list_lookup (struct ifnet*) ; 
 int /*<<< orphan*/  vlan_assert_lock_held () ; 
 int vlan_attach_protocol (struct ifnet*) ; 
 int /*<<< orphan*/  vlan_detach_protocol (struct ifnet*) ; 
 int /*<<< orphan*/  vlan_lock () ; 
 int /*<<< orphan*/  vlan_parent_add_vlan (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int vlan_parent_create (struct ifnet*,int /*<<< orphan*/ **) ; 
 scalar_t__ vlan_parent_flags_detaching (int /*<<< orphan*/ *) ; 
 scalar_t__ vlan_parent_flags_supports_vlan_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlan_parent_lookup_tag (int /*<<< orphan*/ *,int) ; 
 scalar_t__ vlan_parent_no_vlans (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_parent_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_parent_remove_vlan (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_parent_signal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlan_parent_wait (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlan_unlock () ; 
 int /*<<< orphan*/  vlp_parent_list ; 

__attribute__((used)) static int
vlan_config(struct ifnet * ifp, struct ifnet * p, int tag)
{
    int			error;
    int			first_vlan = FALSE;
    ifvlan_ref 		ifv = NULL;
    int			ifv_added = FALSE;
    int			need_vlp_release = 0;
    vlan_parent_ref	new_vlp = NULL;
    ifnet_offload_t	offload;
    u_int16_t		parent_flags;
    vlan_parent_ref	vlp = NULL;

    /* pre-allocate space for vlan_parent, in case we're first */
    error = vlan_parent_create(p, &new_vlp);
    if (error != 0) {
	return (error);
    }

    vlan_lock();
    ifv = ifnet_get_ifvlan_retained(ifp);
    if (ifv == NULL || ifv->ifv_vlp != NULL) {
	vlan_unlock();
	if (ifv != NULL) {
	    ifvlan_release(ifv);
	}
	vlan_parent_release(new_vlp);
	return (EBUSY);
    }
    vlp = parent_list_lookup(p);
    if (vlp != NULL) {
	vlan_parent_retain(vlp);
	need_vlp_release++;
	if (vlan_parent_lookup_tag(vlp, tag) != NULL) {
	    /* already a VLAN with that tag on this interface */
	    error = EADDRINUSE;
	    goto unlock_done;
	}
    }
    else {
	/* one for being in the list */
	vlan_parent_retain(new_vlp);

	/* we're the first VLAN on this interface */
	LIST_INSERT_HEAD(&g_vlan->parent_list, new_vlp, vlp_parent_list);
	vlp = new_vlp;

	vlan_parent_retain(vlp);
	need_vlp_release++;
    }

    /* need to wait to ensure no one else is trying to add/remove */
    vlan_parent_wait(vlp, "vlan_config");

    if (ifnet_get_ifvlan(ifp) != ifv) {
	error = EINVAL;
	goto signal_done;
    }

    /* check again because someone might have gotten in */
    if (parent_list_lookup(p) != vlp) {
	error = EBUSY;
	goto signal_done;
    }

    if (vlan_parent_flags_detaching(vlp)
	|| ifvlan_flags_detaching(ifv) || ifv->ifv_vlp != NULL) {
	error = EBUSY;
	goto signal_done;
    }

    /* check again because someone might have gotten the tag */
    if (vlan_parent_lookup_tag(vlp, tag) != NULL) {
	/* already a VLAN with that tag on this interface */
	error = EADDRINUSE;
	goto signal_done;
    }

    if (vlan_parent_no_vlans(vlp)) {
	first_vlan = TRUE;
    }
    vlan_parent_add_vlan(vlp, ifv, tag);
    ifvlan_retain(ifv);	/* parent references ifv */
    ifv_added = TRUE;

    /* check whether bond interface is using parent interface */
    ifnet_lock_exclusive(p);
    if ((ifnet_eflags(p) & IFEF_BOND) != 0) {
	ifnet_lock_done(p);
	/* don't allow VLAN over interface that's already part of a bond */
	error = EBUSY;
	goto signal_done;
    }
    /* prevent BOND interface from using it */
    /* Can't use ifnet_set_eflags because that would take the lock */
    p->if_eflags |= IFEF_VLAN;
    ifnet_lock_done(p);
    vlan_unlock();

    if (first_vlan) {
	/* attach our VLAN "protocol" to the interface */
	error = vlan_attach_protocol(p);
	if (error) {
	    vlan_lock();
	    goto signal_done;
	}
    }

    /* configure parent to receive our multicast addresses */
    error = multicast_list_program(&ifv->ifv_multicast, ifp, p);
    if (error != 0) {
	if (first_vlan) {
	    (void)vlan_detach_protocol(p);
	}
	vlan_lock();
	goto signal_done;
    }

    /* set our ethernet address to that of the parent */
    ifnet_set_lladdr_and_type(ifp, IF_LLADDR(p), ETHER_ADDR_LEN, IFT_ETHER);

    /* no failures past this point */
    vlan_lock();

    ifv->ifv_encaplen = ETHER_VLAN_ENCAP_LEN;
    ifv->ifv_flags = 0;
    if (vlan_parent_flags_supports_vlan_mtu(vlp)) {
	ifv->ifv_mtufudge = 0;
    } else {
	/*
	 * Fudge the MTU by the encapsulation size.  This
	 * makes us incompatible with strictly compliant
	 * 802.1Q implementations, but allows us to use
	 * the feature with other NetBSD implementations,
	 * which might still be useful.
	 */
	ifv->ifv_mtufudge = ifv->ifv_encaplen;
    }
    ifnet_set_mtu(ifp, ETHERMTU - ifv->ifv_mtufudge);

    /*
     * Copy only a selected subset of flags from the parent.
     * Other flags are none of our business.
     */
    parent_flags = ifnet_flags(p) 
	& (IFF_BROADCAST | IFF_MULTICAST | IFF_SIMPLEX);
    ifnet_set_flags(ifp, parent_flags,
		    IFF_BROADCAST | IFF_MULTICAST | IFF_SIMPLEX);

    /* use hwassist bits from parent interface, but exclude VLAN bits */
    offload = ifnet_offload(p) & ~(IFNET_VLAN_TAGGING | IFNET_VLAN_MTU);
    ifnet_set_offload(ifp, offload);

    ifnet_set_flags(ifp, IFF_RUNNING, IFF_RUNNING);
    ifvlan_flags_set_ready(ifv);
    vlan_parent_signal(vlp, "vlan_config");
    vlan_unlock();
    if (new_vlp != vlp) {
	/* throw it away, it wasn't needed */
	vlan_parent_release(new_vlp);
    }
    if (ifv != NULL) {
	ifvlan_release(ifv);
    }
    if (first_vlan) {
	/* mark the parent interface up */
	ifnet_set_flags(p, IFF_UP, IFF_UP);
	(void)ifnet_ioctl(p, 0, SIOCSIFFLAGS, (caddr_t)NULL);
    }
    return 0;

 signal_done:
    vlan_assert_lock_held();

    if (ifv_added) {
	vlan_parent_remove_vlan(vlp, ifv);
	if (!vlan_parent_flags_detaching(vlp) && vlan_parent_no_vlans(vlp)) {
	    /* the vlan parent has no more VLAN's */
	    ifnet_set_eflags(p, 0, IFEF_VLAN);
	    LIST_REMOVE(vlp, vlp_parent_list);
	    /* release outside of the lock below */
	    need_vlp_release++;

	    /* one for being in the list */
	    need_vlp_release++;
	}
    }
    vlan_parent_signal(vlp, "vlan_config");

 unlock_done:
    vlan_unlock();

    while (need_vlp_release--) {
	vlan_parent_release(vlp);
    }
    if (new_vlp != vlp) {
	vlan_parent_release(new_vlp);
    }
    if (ifv != NULL) {
	if (ifv_added) {
	    ifvlan_release(ifv);
	}
	ifvlan_release(ifv);
    }
    return (error);
}