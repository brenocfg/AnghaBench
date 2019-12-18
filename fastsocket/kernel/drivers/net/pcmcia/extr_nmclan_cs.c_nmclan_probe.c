#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ConfigIndex; int /*<<< orphan*/  Present; int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct TYPE_7__ {int Attributes; struct net_device* Instance; int /*<<< orphan*/ * Handler; int /*<<< orphan*/  IRQInfo1; } ;
struct TYPE_6__ {int NumPorts1; int IOAddrLines; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_3__ conf; TYPE_2__ irq; TYPE_1__ io; struct net_device* priv; } ;
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_free_frames; int /*<<< orphan*/  bank_lock; struct pcmcia_device* p_dev; } ;
typedef  TYPE_4__ mace_private ;

/* Variables and functions */
 int /*<<< orphan*/  AM2150_MAX_TX_FRAMES ; 
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  DEBUG (int,char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 int IRQ_HANDLE_PRESENT ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int IRQ_TYPE_EXCLUSIVE ; 
 int /*<<< orphan*/  PRESENT_OPTION ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  mace_interrupt ; 
 int /*<<< orphan*/  mace_netdev_ops ; 
 int /*<<< orphan*/  netdev_ethtool_ops ; 
 TYPE_4__* netdev_priv (struct net_device*) ; 
 int nmclan_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  rcsid ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nmclan_probe(struct pcmcia_device *link)
{
    mace_private *lp;
    struct net_device *dev;

    DEBUG(0, "nmclan_attach()\n");
    DEBUG(1, "%s\n", rcsid);

    /* Create new ethernet device */
    dev = alloc_etherdev(sizeof(mace_private));
    if (!dev)
	    return -ENOMEM;
    lp = netdev_priv(dev);
    lp->p_dev = link;
    link->priv = dev;
    
    spin_lock_init(&lp->bank_lock);
    link->io.NumPorts1 = 32;
    link->io.Attributes1 = IO_DATA_PATH_WIDTH_AUTO;
    link->io.IOAddrLines = 5;
    link->irq.Attributes = IRQ_TYPE_EXCLUSIVE | IRQ_HANDLE_PRESENT;
    link->irq.IRQInfo1 = IRQ_LEVEL_ID;
    link->irq.Handler = &mace_interrupt;
    link->irq.Instance = dev;
    link->conf.Attributes = CONF_ENABLE_IRQ;
    link->conf.IntType = INT_MEMORY_AND_IO;
    link->conf.ConfigIndex = 1;
    link->conf.Present = PRESENT_OPTION;

    lp->tx_free_frames=AM2150_MAX_TX_FRAMES;

    dev->netdev_ops = &mace_netdev_ops;
    SET_ETHTOOL_OPS(dev, &netdev_ethtool_ops);
    dev->watchdog_timeo = TX_TIMEOUT;

    return nmclan_config(link);
}