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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ks8851_net {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ks8851_write_mac_addr (struct net_device*) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks8851_init_mac(struct ks8851_net *ks)
{
	struct net_device *dev = ks->netdev;

	random_ether_addr(dev->dev_addr);
	ks8851_write_mac_addr(dev);
}