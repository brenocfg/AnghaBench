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
struct net_device {int flags; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  set_multicast_finish (struct net_device*) ; 
 int /*<<< orphan*/  set_multicast_one (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_multicast_start (struct net_device*) ; 
 int /*<<< orphan*/  set_promiscuous_mode (struct net_device*) ; 

__attribute__((used)) static void set_multicast_list(struct net_device *dev)
{
	struct dev_mc_list *pmc;

	if ((dev->flags & IFF_PROMISC) == 0) {
		set_multicast_start(dev);
		for (pmc = dev->mc_list; pmc != NULL; pmc = pmc->next)
			set_multicast_one(dev, pmc->dmi_addr);
		set_multicast_finish(dev);
	} else
		set_promiscuous_mode(dev);
}