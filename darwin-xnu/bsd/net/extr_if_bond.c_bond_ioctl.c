#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int u_long ;
struct TYPE_16__ {int /*<<< orphan*/  ifdm_max; int /*<<< orphan*/  ifdm_min; int /*<<< orphan*/  ifdm_current; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; int /*<<< orphan*/  ifr_data64; int /*<<< orphan*/  ifr_mtu; TYPE_4__ ifr_devmtu; } ;
struct ifnet {int dummy; } ;
struct ifmediareq64 {int /*<<< orphan*/  ifmu_ulist; } ;
struct ifmediareq32 {int /*<<< orphan*/  ifmu_ulist; } ;
struct ifmediareq {int ifm_count; void* ifm_current; int /*<<< orphan*/  ifm_status; void* ifm_active; int /*<<< orphan*/  ifm_mask; } ;
struct ifaddr {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  ibru_int_val; int /*<<< orphan*/  ibru_if_name; } ;
struct if_bond_req {int /*<<< orphan*/  ibr_op; TYPE_5__ ibr_ibru; } ;
typedef  TYPE_6__* ifbond_ref ;
typedef  int /*<<< orphan*/  ibr ;
struct TYPE_19__ {int /*<<< orphan*/  verbose; } ;
struct TYPE_18__ {int ifb_mode; int /*<<< orphan*/  ifb_altmtu; TYPE_3__** ifb_distributing_array; int /*<<< orphan*/  ifb_distributing_count; TYPE_1__* ifb_active_lag; } ;
struct TYPE_14__ {void* mi_active; } ;
struct TYPE_15__ {TYPE_2__ po_media_info; } ;
struct TYPE_13__ {void* lag_active_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 void* IFM_ETHER ; 
 scalar_t__ IFT_ETHER ; 
 scalar_t__ IFT_IEEE8023ADLAG ; 
#define  IF_BOND_MODE_LACP 148 
#define  IF_BOND_MODE_STATIC 147 
#define  IF_BOND_OP_ADD_INTERFACE 146 
#define  IF_BOND_OP_GET_STATUS 145 
#define  IF_BOND_OP_REMOVE_INTERFACE 144 
#define  IF_BOND_OP_SET_MODE 143 
#define  IF_BOND_OP_SET_VERBOSE 142 
#define  SIOCADDMULTI 141 
#define  SIOCDELMULTI 140 
#define  SIOCGIFALTMTU 139 
#define  SIOCGIFBOND 138 
#define  SIOCGIFDEVMTU 137 
#define  SIOCGIFMEDIA32 136 
#define  SIOCGIFMEDIA64 135 
#define  SIOCSIFADDR 134 
#define  SIOCSIFALTMTU 133 
#define  SIOCSIFBOND 132 
#define  SIOCSIFFLAGS 131 
#define  SIOCSIFLLADDR 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int bond_add_interface (struct ifnet*,struct ifnet*) ; 
 int /*<<< orphan*/  bond_device_mtu (struct ifnet*,TYPE_6__*) ; 
 int /*<<< orphan*/  bond_get_mtu_values (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bond_get_status (TYPE_6__*,struct if_bond_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_lock () ; 
 int bond_remove_interface (TYPE_6__*,struct ifnet*) ; 
 int bond_set_mode (struct ifnet*,int /*<<< orphan*/ ) ; 
 int bond_set_mtu (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int bond_set_promisc (struct ifnet*) ; 
 int bond_setmulti (struct ifnet*) ; 
 int /*<<< orphan*/  bond_unlock () ; 
 int copyin (int /*<<< orphan*/ ,struct if_bond_req*,int) ; 
 int copyout (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_proc () ; 
 TYPE_8__* g_bond ; 
 int /*<<< orphan*/  ifbond_flags_if_detaching (TYPE_6__*) ; 
 int /*<<< orphan*/  ifnet_set_flags (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_softc (struct ifnet*) ; 
 scalar_t__ ifnet_type (struct ifnet*) ; 
 struct ifnet* ifunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_is64bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bond_ioctl(struct ifnet *ifp, u_long cmd, void * data)
{
    int 		error = 0;
    struct if_bond_req	ibr;
    struct ifaddr *	ifa;
    ifbond_ref		ifb;
    struct ifreq *	ifr;
    struct ifmediareq	*ifmr;
    struct ifnet *	port_ifp = NULL;
    user_addr_t		user_addr;

    if (ifnet_type(ifp) != IFT_IEEE8023ADLAG) {
	return (EOPNOTSUPP);
    }
    ifr = (struct ifreq *)data;
    ifa = (struct ifaddr *)data;

    switch (cmd) {
    case SIOCSIFADDR:
	ifnet_set_flags(ifp, IFF_UP, IFF_UP);
	break;

    case SIOCGIFMEDIA32:
    case SIOCGIFMEDIA64:
	bond_lock();
	ifb = (ifbond_ref)ifnet_softc(ifp);
	if (ifb == NULL || ifbond_flags_if_detaching(ifb)) {
	    bond_unlock();
	    return (ifb == NULL ? EOPNOTSUPP : EBUSY);
	}
	ifmr = (struct ifmediareq *)data;
	ifmr->ifm_current = IFM_ETHER;
	ifmr->ifm_mask = 0;
	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;
	ifmr->ifm_count = 1;
	if (ifb->ifb_mode == IF_BOND_MODE_LACP) {
	    if (ifb->ifb_active_lag != NULL) {
		ifmr->ifm_active = ifb->ifb_active_lag->lag_active_media;
		ifmr->ifm_status |= IFM_ACTIVE;
	    }
	}
	else if (ifb->ifb_distributing_count > 0) {
	    ifmr->ifm_active
		= ifb->ifb_distributing_array[0]->po_media_info.mi_active;
	    ifmr->ifm_status |= IFM_ACTIVE;
	}
	bond_unlock();
	user_addr = (cmd == SIOCGIFMEDIA64) ?
	    ((struct ifmediareq64 *)ifmr)->ifmu_ulist :
	    CAST_USER_ADDR_T(((struct ifmediareq32 *)ifmr)->ifmu_ulist);
	if (user_addr != USER_ADDR_NULL) {
	    error = copyout(&ifmr->ifm_current,
			    user_addr,
			    sizeof(int));
	}
	break;

    case SIOCSIFMEDIA:
	/* XXX send the SIFMEDIA to all children?  Or force autoselect? */
	error = EINVAL;
	break;

    case SIOCGIFDEVMTU:
	bond_lock();
	ifb = (ifbond_ref)ifnet_softc(ifp);
	if (ifb == NULL || ifbond_flags_if_detaching(ifb)) {
	    bond_unlock();
	    error = (ifb == NULL) ? EOPNOTSUPP : EBUSY;
	    break;
	}
	ifr->ifr_devmtu.ifdm_current = bond_device_mtu(ifp, ifb);
	bond_get_mtu_values(ifb, &ifr->ifr_devmtu.ifdm_min,
			    &ifr->ifr_devmtu.ifdm_max);
	bond_unlock();
	break;

    case SIOCGIFALTMTU:
	bond_lock();
	ifb = (ifbond_ref)ifnet_softc(ifp);
	if (ifb == NULL || ifbond_flags_if_detaching(ifb)) {
	    bond_unlock();
	    error = (ifb == NULL) ? EOPNOTSUPP : EBUSY;
	    break;
	}
	ifr->ifr_mtu = ifb->ifb_altmtu;
	bond_unlock();
	break;

    case SIOCSIFALTMTU:
	error = bond_set_mtu(ifp, ifr->ifr_mtu, 1);
	break;

    case SIOCSIFMTU:
	error = bond_set_mtu(ifp, ifr->ifr_mtu, 0);
	break;

    case SIOCSIFBOND:
	user_addr = proc_is64bit(current_proc())
	    ? ifr->ifr_data64 : CAST_USER_ADDR_T(ifr->ifr_data);
	error = copyin(user_addr, &ibr, sizeof(ibr));
	if (error) {
	    break;
	}
	switch (ibr.ibr_op) {
	case IF_BOND_OP_ADD_INTERFACE:
	case IF_BOND_OP_REMOVE_INTERFACE:
	    port_ifp = ifunit(ibr.ibr_ibru.ibru_if_name);
	    if (port_ifp == NULL) {
		error = ENXIO;
		break;
	    }
	    if (ifnet_type(port_ifp) != IFT_ETHER) {
		error = EPROTONOSUPPORT;
		break;
	    }
	    break;
	case IF_BOND_OP_SET_VERBOSE:
	case IF_BOND_OP_SET_MODE:
	    break;
	default:
	    error = EOPNOTSUPP;
	    break;
	}
	if (error != 0) {
	    break;
	}
	switch (ibr.ibr_op) {
	case IF_BOND_OP_ADD_INTERFACE:
	    error = bond_add_interface(ifp, port_ifp);
	    break;
	case IF_BOND_OP_REMOVE_INTERFACE:
	    bond_lock();
	    ifb = (ifbond_ref)ifnet_softc(ifp);
	    if (ifb == NULL || ifbond_flags_if_detaching(ifb)) {
		bond_unlock();
		return (ifb == NULL ? EOPNOTSUPP : EBUSY);
	    }
	    error = bond_remove_interface(ifb, port_ifp);
	    bond_unlock();
	    break;
	case IF_BOND_OP_SET_VERBOSE:
	    bond_lock();
	    if (g_bond == NULL) {
		bond_unlock();
		error = ENXIO;
		break;
	    }
	    g_bond->verbose = ibr.ibr_ibru.ibru_int_val;
	    bond_unlock();
	    break;
	case IF_BOND_OP_SET_MODE:
	    switch (ibr.ibr_ibru.ibru_int_val) {
	    case IF_BOND_MODE_LACP:
	    case IF_BOND_MODE_STATIC:
		break;
	    default:
		error = EINVAL;
		break;
	    }
	    if (error != 0) {
		break;
	    }
	    error = bond_set_mode(ifp, ibr.ibr_ibru.ibru_int_val);
	    break;
	}
	break; /* SIOCSIFBOND */
		
    case SIOCGIFBOND:
	user_addr = proc_is64bit(current_proc())
	    ? ifr->ifr_data64 : CAST_USER_ADDR_T(ifr->ifr_data);
	error = copyin(user_addr, &ibr, sizeof(ibr));
	if (error) {
	    break;
	}
	switch (ibr.ibr_op) {
	case IF_BOND_OP_GET_STATUS:
	    break;
	default:
	    error = EOPNOTSUPP;
	    break;
	}
	if (error != 0) {
	    break;
	}
	bond_lock();
	ifb = (ifbond_ref)ifnet_softc(ifp);
	if (ifb == NULL || ifbond_flags_if_detaching(ifb)) {
	    bond_unlock();
	    return (ifb == NULL ? EOPNOTSUPP : EBUSY);
	}
	switch (ibr.ibr_op) {
	case IF_BOND_OP_GET_STATUS:
	    error = bond_get_status(ifb, &ibr, user_addr);
	    break;
	}
	bond_unlock();
	break; /* SIOCGIFBOND */
		
    case SIOCSIFLLADDR:
	error = EOPNOTSUPP;
	break;

    case SIOCSIFFLAGS:
	/* enable/disable promiscuous mode */
	bond_lock();
	error = bond_set_promisc(ifp);
	bond_unlock();
	break;

    case SIOCADDMULTI:
    case SIOCDELMULTI:
	error = bond_setmulti(ifp);
	break;
    default:
	error = EOPNOTSUPP;
    }
    return error;
}