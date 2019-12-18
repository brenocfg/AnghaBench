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
struct uml_net_private {scalar_t__ user; } ;
struct net_device {int dummy; } ;
struct mcast_init {int /*<<< orphan*/  ttl; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; } ;
struct mcast_data {int /*<<< orphan*/  ttl; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; struct net_device* dev; } ;

/* Variables and functions */
 struct uml_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcast_init(struct net_device *dev, void *data)
{
	struct uml_net_private *pri;
	struct mcast_data *dpri;
	struct mcast_init *init = data;

	pri = netdev_priv(dev);
	dpri = (struct mcast_data *) pri->user;
	dpri->addr = init->addr;
	dpri->port = init->port;
	dpri->ttl = init->ttl;
	dpri->dev = dev;

	printk("mcast backend multicast address: %s:%u, TTL:%u\n",
	       dpri->addr, dpri->port, dpri->ttl);
}