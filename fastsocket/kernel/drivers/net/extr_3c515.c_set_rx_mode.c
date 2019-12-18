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
struct net_device {int base_addr; int flags; scalar_t__ mc_list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ EL3_CMD ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 short RxBroadcast ; 
 short RxMulticast ; 
 short RxProm ; 
 short RxStation ; 
 short SetRxFilter ; 
 int corkscrew_debug ; 
 int /*<<< orphan*/  outw (short,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_rx_mode(struct net_device *dev)
{
	int ioaddr = dev->base_addr;
	short new_mode;

	if (dev->flags & IFF_PROMISC) {
		if (corkscrew_debug > 3)
			pr_debug("%s: Setting promiscuous mode.\n",
			       dev->name);
		new_mode = SetRxFilter | RxStation | RxMulticast | RxBroadcast | RxProm;
	} else if ((dev->mc_list) || (dev->flags & IFF_ALLMULTI)) {
		new_mode = SetRxFilter | RxStation | RxMulticast | RxBroadcast;
	} else
		new_mode = SetRxFilter | RxStation | RxBroadcast;

	outw(new_mode, ioaddr + EL3_CMD);
}