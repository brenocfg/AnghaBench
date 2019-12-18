#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  if_unit; int /*<<< orphan*/  if_family; int /*<<< orphan*/ * if_name; } ;
struct kev_msg {TYPE_4__* dv; TYPE_3__ link_data; int /*<<< orphan*/  ia_netbroadcast; int /*<<< orphan*/  ia_subnetmask; int /*<<< orphan*/  ia_subnet; int /*<<< orphan*/  ia_netmask; int /*<<< orphan*/  ia_net; int /*<<< orphan*/  ia_addr; TYPE_1__ ia_dstaddr; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct kev_in_data {TYPE_4__* dv; TYPE_3__ link_data; int /*<<< orphan*/  ia_netbroadcast; int /*<<< orphan*/  ia_subnetmask; int /*<<< orphan*/  ia_subnet; int /*<<< orphan*/  ia_netmask; int /*<<< orphan*/  ia_net; int /*<<< orphan*/  ia_addr; TYPE_1__ ia_dstaddr; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct TYPE_13__ {struct sockaddr* ifa_dstaddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  sin_addr; } ;
struct in_ifaddr {int ia_flags; TYPE_5__ ia_ifa; struct sockaddr_in ia_dstaddr; int /*<<< orphan*/  ia_netbroadcast; int /*<<< orphan*/  ia_subnetmask; int /*<<< orphan*/  ia_subnet; int /*<<< orphan*/  ia_netmask; int /*<<< orphan*/  ia_net; TYPE_2__ ia_addr; } ;
struct ifreq {struct sockaddr_in ifr_dstaddr; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_unit; int /*<<< orphan*/  if_family; int /*<<< orphan*/  if_name; } ;
typedef  int /*<<< orphan*/  dstaddr ;
struct TYPE_12__ {int data_length; struct kev_msg* data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IFA_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  IFA_LOCK_ASSERT_HELD (TYPE_5__*) ; 
 int IFA_ROUTE ; 
 int /*<<< orphan*/  IFA_UNLOCK (TYPE_5__*) ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  KEV_INET_SIFDSTADDR ; 
 int /*<<< orphan*/  KEV_INET_SUBCLASS ; 
 int /*<<< orphan*/  KEV_NETWORK_CLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
 int /*<<< orphan*/  PF_INET ; 
 int RTF_HOST ; 
 int RTF_UP ; 
 scalar_t__ RTM_ADD ; 
 scalar_t__ RTM_DELETE ; 
#define  SIOCGIFDSTADDR 129 
#define  SIOCSIFDSTADDR 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct sockaddr_in*,struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  bzero (struct kev_msg*,int) ; 
 int /*<<< orphan*/  dlil_post_complete_msg (struct ifnet*,struct kev_msg*) ; 
 int ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int const,struct in_ifaddr*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  rtinit_locked (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __attribute__((noinline)) int
inctl_ifdstaddr(struct ifnet *ifp, struct in_ifaddr *ia, u_long cmd,
    struct ifreq *ifr)
{
	struct kev_in_data in_event_data;
	struct kev_msg ev_msg;
	struct sockaddr_in dstaddr;
	int error = 0;

	VERIFY(ifp != NULL);

	if (!(ifp->if_flags & IFF_POINTOPOINT))
		return (EINVAL);

	bzero(&in_event_data, sizeof (struct kev_in_data));
	bzero(&ev_msg, sizeof (struct kev_msg));

	switch (cmd) {
	case SIOCGIFDSTADDR:		/* struct ifreq */
		if (ia == NULL) {
			error = EADDRNOTAVAIL;
			break;
		}
		IFA_LOCK(&ia->ia_ifa);
		bcopy(&ia->ia_dstaddr, &ifr->ifr_dstaddr, sizeof (dstaddr));
		IFA_UNLOCK(&ia->ia_ifa);
		break;

	case SIOCSIFDSTADDR:		/* struct ifreq */
		VERIFY(ia != NULL);
		IFA_LOCK(&ia->ia_ifa);
		dstaddr = ia->ia_dstaddr;
		bcopy(&ifr->ifr_dstaddr, &ia->ia_dstaddr, sizeof (dstaddr));
		if (ia->ia_dstaddr.sin_family == AF_INET)
			ia->ia_dstaddr.sin_len = sizeof (struct sockaddr_in);
		IFA_UNLOCK(&ia->ia_ifa);
		/*
		 * NOTE: SIOCSIFDSTADDR is defined with struct ifreq
		 * as parameter, but here we are sending it down
		 * to the interface with a pointer to struct ifaddr,
		 * for legacy reasons.
		 */
		error = ifnet_ioctl(ifp, PF_INET, SIOCSIFDSTADDR, ia);
		IFA_LOCK(&ia->ia_ifa);
		if (error == EOPNOTSUPP)
			error = 0;
		if (error != 0) {
			ia->ia_dstaddr = dstaddr;
			IFA_UNLOCK(&ia->ia_ifa);
			break;
		}
		IFA_LOCK_ASSERT_HELD(&ia->ia_ifa);

		ev_msg.vendor_code	= KEV_VENDOR_APPLE;
		ev_msg.kev_class	= KEV_NETWORK_CLASS;
		ev_msg.kev_subclass	= KEV_INET_SUBCLASS;

		ev_msg.event_code	= KEV_INET_SIFDSTADDR;

		if (ia->ia_ifa.ifa_dstaddr) {
			in_event_data.ia_dstaddr = ((struct sockaddr_in *)
			    (void *)ia->ia_ifa.ifa_dstaddr)->sin_addr;
		} else {
			in_event_data.ia_dstaddr.s_addr = INADDR_ANY;
		}

		in_event_data.ia_addr		= ia->ia_addr.sin_addr;
		in_event_data.ia_net		= ia->ia_net;
		in_event_data.ia_netmask	= ia->ia_netmask;
		in_event_data.ia_subnet		= ia->ia_subnet;
		in_event_data.ia_subnetmask	= ia->ia_subnetmask;
		in_event_data.ia_netbroadcast	= ia->ia_netbroadcast;
		IFA_UNLOCK(&ia->ia_ifa);
		(void) strlcpy(&in_event_data.link_data.if_name[0],
		    ifp->if_name, IFNAMSIZ);
		in_event_data.link_data.if_family = ifp->if_family;
		in_event_data.link_data.if_unit  = (u_int32_t)ifp->if_unit;

		ev_msg.dv[0].data_ptr    = &in_event_data;
		ev_msg.dv[0].data_length = sizeof (struct kev_in_data);
		ev_msg.dv[1].data_length = 0;

		dlil_post_complete_msg(ifp, &ev_msg);

		lck_mtx_lock(rnh_lock);
		IFA_LOCK(&ia->ia_ifa);
		if (ia->ia_flags & IFA_ROUTE) {
			ia->ia_ifa.ifa_dstaddr = (struct sockaddr *)&dstaddr;
			IFA_UNLOCK(&ia->ia_ifa);
			rtinit_locked(&(ia->ia_ifa), (int)RTM_DELETE, RTF_HOST);
			IFA_LOCK(&ia->ia_ifa);
			ia->ia_ifa.ifa_dstaddr =
			    (struct sockaddr *)&ia->ia_dstaddr;
			IFA_UNLOCK(&ia->ia_ifa);
			rtinit_locked(&(ia->ia_ifa), (int)RTM_ADD,
			    RTF_HOST|RTF_UP);
		} else {
			IFA_UNLOCK(&ia->ia_ifa);
		}
		lck_mtx_unlock(rnh_lock);
		break;



	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}