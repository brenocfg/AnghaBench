#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kev_msg {scalar_t__ vendor_code; scalar_t__ kev_class; scalar_t__ kev_subclass; scalar_t__ event_code; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/ * ifaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ KEV_DL_LINK_ADDRESS_CHANGED ; 
 scalar_t__ KEV_DL_SUBCLASS ; 
 scalar_t__ KEV_NETWORK_CLASS ; 
 scalar_t__ KEV_VENDOR_APPLE ; 
 int /*<<< orphan*/  ifnet_free_address_list (int /*<<< orphan*/ **) ; 
 scalar_t__ ifnet_get_address_list_family (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_arp_init_ifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ether_inet_event(ifnet_t ifp, protocol_family_t protocol,
    const struct kev_msg *event)
{
#pragma unused(protocol)
	ifaddr_t *addresses;

	if (event->vendor_code !=  KEV_VENDOR_APPLE ||
	    event->kev_class != KEV_NETWORK_CLASS ||
	    event->kev_subclass != KEV_DL_SUBCLASS ||
	    event->event_code != KEV_DL_LINK_ADDRESS_CHANGED) {
		return;
	}

	if (ifnet_get_address_list_family(ifp, &addresses, AF_INET) == 0) {
		int i;

		for (i = 0; addresses[i] != NULL; i++) {
			inet_arp_init_ifaddr(ifp, addresses[i]);
		}

		ifnet_free_address_list(addresses);
	}
}