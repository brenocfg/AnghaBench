#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  if_unit; int /*<<< orphan*/  if_family; int /*<<< orphan*/ * if_name; } ;
struct kev_msg {TYPE_4__* dv; TYPE_3__ link_data; int /*<<< orphan*/  ia_netbroadcast; int /*<<< orphan*/  ia_subnetmask; int /*<<< orphan*/  ia_subnet; int /*<<< orphan*/  ia_netmask; int /*<<< orphan*/  ia_net; int /*<<< orphan*/  ia_addr; TYPE_1__ ia_dstaddr; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct kev_in_data {TYPE_4__* dv; TYPE_3__ link_data; int /*<<< orphan*/  ia_netbroadcast; int /*<<< orphan*/  ia_subnetmask; int /*<<< orphan*/  ia_subnet; int /*<<< orphan*/  ia_netmask; int /*<<< orphan*/  ia_net; int /*<<< orphan*/  ia_addr; TYPE_1__ ia_dstaddr; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct TYPE_11__ {scalar_t__ ifa_dstaddr; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin_addr; } ;
struct in_ifaddr {TYPE_5__ ia_ifa; int /*<<< orphan*/  ia_netbroadcast; int /*<<< orphan*/  ia_subnetmask; int /*<<< orphan*/  ia_subnet; int /*<<< orphan*/  ia_netmask; int /*<<< orphan*/  ia_net; TYPE_2__ ia_addr; int /*<<< orphan*/  ia_broadaddr; } ;
struct ifreq {int /*<<< orphan*/  ifr_broadaddr; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_unit; int /*<<< orphan*/  if_family; int /*<<< orphan*/  if_name; } ;
struct TYPE_10__ {int data_length; struct kev_msg* data_ptr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int /*<<< orphan*/  IFA_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (TYPE_5__*) ; 
 int IFF_BROADCAST ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  KEV_INET_SIFBRDADDR ; 
 int /*<<< orphan*/  KEV_INET_SUBCLASS ; 
 int /*<<< orphan*/  KEV_NETWORK_CLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
#define  SIOCGIFBRDADDR 129 
#define  SIOCSIFBRDADDR 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct kev_msg*,int) ; 
 int /*<<< orphan*/  dlil_post_complete_msg (struct ifnet*,struct kev_msg*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __attribute__((noinline)) int
inctl_ifbrdaddr(struct ifnet *ifp, struct in_ifaddr *ia, u_long cmd,
    struct ifreq *ifr)
{
	struct kev_in_data in_event_data;
	struct kev_msg ev_msg;
	int error = 0;

	VERIFY(ifp != NULL);

	if (ia == NULL)
		return (EADDRNOTAVAIL);

	if (!(ifp->if_flags & IFF_BROADCAST))
		return (EINVAL);

	bzero(&in_event_data, sizeof (struct kev_in_data));
	bzero(&ev_msg, sizeof (struct kev_msg));

	switch (cmd) {
	case SIOCGIFBRDADDR:		/* struct ifreq */
		IFA_LOCK(&ia->ia_ifa);
		bcopy(&ia->ia_broadaddr, &ifr->ifr_broadaddr,
		    sizeof (struct sockaddr_in));
		IFA_UNLOCK(&ia->ia_ifa);
		break;

	case SIOCSIFBRDADDR:		/* struct ifreq */
		IFA_LOCK(&ia->ia_ifa);
		bcopy(&ifr->ifr_broadaddr, &ia->ia_broadaddr,
		    sizeof (struct sockaddr_in));

		ev_msg.vendor_code	= KEV_VENDOR_APPLE;
		ev_msg.kev_class	= KEV_NETWORK_CLASS;
		ev_msg.kev_subclass	= KEV_INET_SUBCLASS;

		ev_msg.event_code = KEV_INET_SIFBRDADDR;

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
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}