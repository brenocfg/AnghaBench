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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int* dev_addr; struct in_device* ip_ptr; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_local; } ;
struct in_device {struct in_ifaddr* ifa_list; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct net_device* MASTER_TO_SLAVE (struct net_device*) ; 
 int /*<<< orphan*/  isdn_lock_drivers () ; 
 int /*<<< orphan*/  isdn_net_reset (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 

__attribute__((used)) static int
isdn_net_open(struct net_device *dev)
{
	int i;
	struct net_device *p;
	struct in_device *in_dev;

	/* moved here from isdn_net_reset, because only the master has an
	   interface associated which is supposed to be started. BTW:
	   we need to call netif_start_queue, not netif_wake_queue here */
	netif_start_queue(dev);

	isdn_net_reset(dev);
	/* Fill in the MAC-level header (not needed, but for compatibility... */
	for (i = 0; i < ETH_ALEN - sizeof(u32); i++)
		dev->dev_addr[i] = 0xfc;
	if ((in_dev = dev->ip_ptr) != NULL) {
		/*
		 *      Any address will do - we take the first
		 */
		struct in_ifaddr *ifa = in_dev->ifa_list;
		if (ifa != NULL)
			memcpy(dev->dev_addr+2, &ifa->ifa_local, 4);
	}

	/* If this interface has slaves, start them also */
	p = MASTER_TO_SLAVE(dev);
	if (p) {
		while (p) {
			isdn_net_reset(p);
			p = MASTER_TO_SLAVE(p);
		}
	}
	isdn_lock_drivers();
	return 0;
}