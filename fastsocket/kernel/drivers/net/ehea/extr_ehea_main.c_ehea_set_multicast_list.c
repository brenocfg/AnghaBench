#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; int mc_count; struct dev_mc_list* mc_list; } ;
struct ehea_port {TYPE_1__* adapter; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct TYPE_2__ {int max_mc_mac; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  ehea_add_multicast_entry (struct ehea_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_allmulti (struct net_device*,int) ; 
 int ehea_drop_multicast_list (struct net_device*) ; 
 int /*<<< orphan*/  ehea_info (char*,int) ; 
 int /*<<< orphan*/  ehea_promiscuous (struct net_device*,int) ; 
 int /*<<< orphan*/  ehea_update_bcmc_registrations () ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ehea_set_multicast_list(struct net_device *dev)
{
	struct ehea_port *port = netdev_priv(dev);
	struct dev_mc_list *k_mcl_entry;
	int ret, i;

	ehea_promiscuous(dev, !!(dev->flags & IFF_PROMISC));

	if (dev->flags & IFF_ALLMULTI) {
		ehea_allmulti(dev, 1);
		goto out;
	}
	ehea_allmulti(dev, 0);

	if (dev->mc_count) {
		ret = ehea_drop_multicast_list(dev);
		if (ret) {
			/* Dropping the current multicast list failed.
			 * Enabling ALL_MULTI is the best we can do.
			 */
			ehea_allmulti(dev, 1);
		}

		if (dev->mc_count > port->adapter->max_mc_mac) {
			ehea_info("Mcast registration limit reached (0x%llx). "
				  "Use ALLMULTI!",
				  port->adapter->max_mc_mac);
			goto out;
		}

		for (i = 0, k_mcl_entry = dev->mc_list; i < dev->mc_count; i++,
			     k_mcl_entry = k_mcl_entry->next)
			ehea_add_multicast_entry(port, k_mcl_entry->dmi_addr);

	}
out:
	ehea_update_bcmc_registrations();
	return;
}