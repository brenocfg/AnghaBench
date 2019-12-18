#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ConfigIndex; int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct TYPE_5__ {int Attributes; struct net_device* Instance; int /*<<< orphan*/ * Handler; int /*<<< orphan*/  IRQInfo1; } ;
struct TYPE_4__ {int NumPorts1; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_3__ conf; TYPE_2__ irq; TYPE_1__ io; struct net_device* priv; } ;
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct el3_private {int /*<<< orphan*/  window_lock; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_16 ; 
 int IRQ_HANDLE_PRESENT ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int IRQ_TYPE_DYNAMIC_SHARING ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  el3_interrupt ; 
 int /*<<< orphan*/  el3_netdev_ops ; 
 int /*<<< orphan*/  netdev_ethtool_ops ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int tc574_config (struct pcmcia_device*) ; 

__attribute__((used)) static int tc574_probe(struct pcmcia_device *link)
{
	struct el3_private *lp;
	struct net_device *dev;

	DEBUG(0, "3c574_attach()\n");

	/* Create the PC card device object. */
	dev = alloc_etherdev(sizeof(struct el3_private));
	if (!dev)
		return -ENOMEM;
	lp = netdev_priv(dev);
	link->priv = dev;
	lp->p_dev = link;

	spin_lock_init(&lp->window_lock);
	link->io.NumPorts1 = 32;
	link->io.Attributes1 = IO_DATA_PATH_WIDTH_16;
	link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING|IRQ_HANDLE_PRESENT;
	link->irq.IRQInfo1 = IRQ_LEVEL_ID;
	link->irq.Handler = &el3_interrupt;
	link->irq.Instance = dev;
	link->conf.Attributes = CONF_ENABLE_IRQ;
	link->conf.IntType = INT_MEMORY_AND_IO;
	link->conf.ConfigIndex = 1;

	dev->netdev_ops = &el3_netdev_ops;
	SET_ETHTOOL_OPS(dev, &netdev_ethtool_ops);
	dev->watchdog_timeo = TX_TIMEOUT;

	return tc574_config(link);
}