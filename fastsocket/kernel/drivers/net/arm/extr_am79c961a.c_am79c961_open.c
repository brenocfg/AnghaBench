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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  expires; } ;
struct dev_priv {TYPE_1__ timer; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  am79c961_init_for_open (struct net_device*) ; 
 int /*<<< orphan*/  am79c961_interrupt ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int
am79c961_open(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	int ret;

	memset (&priv->stats, 0, sizeof (priv->stats));

	ret = request_irq(dev->irq, am79c961_interrupt, 0, dev->name, dev);
	if (ret)
		return ret;

	am79c961_init_for_open(dev);

	netif_carrier_off(dev);

	priv->timer.expires = jiffies;
	add_timer(&priv->timer);

	netif_start_queue(dev);

	return 0;
}