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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  base_addr; } ;
struct dev_priv {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISALED0 ; 
 unsigned int ISALED0_LNKST ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 unsigned int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 unsigned int read_ireg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void am79c961_timer(unsigned long data)
{
	struct net_device *dev = (struct net_device *)data;
	struct dev_priv *priv = netdev_priv(dev);
	unsigned int lnkstat, carrier;

	lnkstat = read_ireg(dev->base_addr, ISALED0) & ISALED0_LNKST;
	carrier = netif_carrier_ok(dev);

	if (lnkstat && !carrier) {
		netif_carrier_on(dev);
		printk("%s: link up\n", dev->name);
	} else if (!lnkstat && carrier) {
		netif_carrier_off(dev);
		printk("%s: link down\n", dev->name);
	}

	mod_timer(&priv->timer, jiffies + msecs_to_jiffies(500));
}