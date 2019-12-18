#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* u_int32_t ;
struct TYPE_5__ {void* if_unit; int /*<<< orphan*/  if_family; int /*<<< orphan*/ * if_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  ia6t_pltime; int /*<<< orphan*/  ia6t_vltime; int /*<<< orphan*/  ia6t_preferred; int /*<<< orphan*/  ia6t_expire; } ;
struct kev_msg {TYPE_3__* dv; int /*<<< orphan*/  ia_mac; TYPE_2__ link_data; TYPE_1__ ia_lifetime; void* ia6_flags; int /*<<< orphan*/  ia_plen; int /*<<< orphan*/  ia_prefixmask; int /*<<< orphan*/  ia_dstaddr; int /*<<< orphan*/  ia_net; int /*<<< orphan*/  ia_addr; void* event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct kev_in6_data {TYPE_3__* dv; int /*<<< orphan*/  ia_mac; TYPE_2__ link_data; TYPE_1__ ia_lifetime; void* ia6_flags; int /*<<< orphan*/  ia_plen; int /*<<< orphan*/  ia_prefixmask; int /*<<< orphan*/  ia_dstaddr; int /*<<< orphan*/  ia_net; int /*<<< orphan*/  ia_addr; void* event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct in6_ifaddr {int /*<<< orphan*/  ia_ifa; scalar_t__ ia6_flags; int /*<<< orphan*/  ia_plen; int /*<<< orphan*/  ia_prefixmask; int /*<<< orphan*/  ia_dstaddr; int /*<<< orphan*/  ia_net; int /*<<< orphan*/  ia_addr; } ;
struct in6_addrlifetime {int /*<<< orphan*/  ia6t_pltime; int /*<<< orphan*/  ia6t_vltime; int /*<<< orphan*/  ia6t_preferred; int /*<<< orphan*/  ia6t_expire; } ;
struct ifnet {scalar_t__ if_unit; int /*<<< orphan*/  if_family; int /*<<< orphan*/  if_name; } ;
typedef  int /*<<< orphan*/  in6_event_data ;
struct TYPE_6__ {int data_length; struct kev_msg* data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  KEV_INET6_SUBCLASS ; 
 int /*<<< orphan*/  KEV_NETWORK_CLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
 int /*<<< orphan*/  bzero (struct kev_msg*,int) ; 
 int /*<<< orphan*/  dlil_post_complete_msg (int /*<<< orphan*/ *,struct kev_msg*) ; 
 int /*<<< orphan*/  in6ifa_getlifetime (struct in6_ifaddr*,struct in6_addrlifetime*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
in6_post_msg(struct ifnet *ifp, u_int32_t event_code, struct in6_ifaddr *ifa,
    uint8_t *mac)
{
	struct kev_msg ev_msg;
	struct kev_in6_data in6_event_data;
	struct in6_addrlifetime ia6_lt;

	bzero(&in6_event_data, sizeof (struct kev_in6_data));
	bzero(&ev_msg, sizeof (struct kev_msg));
	ev_msg.vendor_code	= KEV_VENDOR_APPLE;
	ev_msg.kev_class	= KEV_NETWORK_CLASS;
	ev_msg.kev_subclass	= KEV_INET6_SUBCLASS;
	ev_msg.event_code	= event_code;

	if (ifa) {
		IFA_LOCK(&ifa->ia_ifa);
		in6_event_data.ia_addr		= ifa->ia_addr;
		in6_event_data.ia_net		= ifa->ia_net;
		in6_event_data.ia_dstaddr	= ifa->ia_dstaddr;
		in6_event_data.ia_prefixmask	= ifa->ia_prefixmask;
		in6_event_data.ia_plen		= ifa->ia_plen;
		in6_event_data.ia6_flags	= (u_int32_t)ifa->ia6_flags;

		/* retrieve time as calendar time (last arg is 1) */
		in6ifa_getlifetime(ifa, &ia6_lt, 1);
		in6_event_data.ia_lifetime.ia6t_expire = ia6_lt.ia6t_expire;
		in6_event_data.ia_lifetime.ia6t_preferred = ia6_lt.ia6t_preferred;
		in6_event_data.ia_lifetime.ia6t_vltime = ia6_lt.ia6t_vltime;
		in6_event_data.ia_lifetime.ia6t_pltime = ia6_lt.ia6t_pltime;
		IFA_UNLOCK(&ifa->ia_ifa);
	}

	if (ifp != NULL) {
		(void) strlcpy(&in6_event_data.link_data.if_name[0],
		    ifp->if_name, IFNAMSIZ);
		in6_event_data.link_data.if_family = ifp->if_family;
		in6_event_data.link_data.if_unit  = (u_int32_t)ifp->if_unit;
	}

	if (mac != NULL)
		memcpy(&in6_event_data.ia_mac, mac, 
		    sizeof(in6_event_data.ia_mac));

	ev_msg.dv[0].data_ptr    = &in6_event_data;
	ev_msg.dv[0].data_length = sizeof (in6_event_data);
	ev_msg.dv[1].data_length = 0;

	dlil_post_complete_msg(NULL, &ev_msg);
}