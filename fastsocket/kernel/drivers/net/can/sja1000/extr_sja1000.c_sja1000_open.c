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
struct sja1000_priv {int flags; int /*<<< orphan*/  open_time; int /*<<< orphan*/  irq_flags; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EAGAIN ; 
 int SJA1000_CUSTOM_IRQ_HANDLER ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  set_reset_mode (struct net_device*) ; 
 int /*<<< orphan*/  sja1000_interrupt ; 
 int /*<<< orphan*/  sja1000_start (struct net_device*) ; 

__attribute__((used)) static int sja1000_open(struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);
	int err;

	/* set chip into reset mode */
	set_reset_mode(dev);

	/* common open */
	err = open_candev(dev);
	if (err)
		return err;

	/* register interrupt handler, if not done by the device driver */
	if (!(priv->flags & SJA1000_CUSTOM_IRQ_HANDLER)) {
		err = request_irq(dev->irq, &sja1000_interrupt, priv->irq_flags,
				  dev->name, (void *)dev);
		if (err) {
			close_candev(dev);
			return -EAGAIN;
		}
	}

	/* init and start chi */
	sja1000_start(dev);
	priv->open_time = jiffies;

	netif_start_queue(dev);

	return 0;
}