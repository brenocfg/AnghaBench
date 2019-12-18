#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct smc_private {TYPE_4__ mii_if; int /*<<< orphan*/  lock; struct pcmcia_device* p_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct TYPE_6__ {int Attributes; struct net_device* Instance; int /*<<< orphan*/ * Handler; int /*<<< orphan*/  IRQInfo1; } ;
struct TYPE_5__ {int NumPorts1; int IOAddrLines; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_3__ conf; TYPE_2__ irq; TYPE_1__ io; struct net_device* priv; } ;
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 int IRQ_HANDLE_PRESENT ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int IRQ_TYPE_DYNAMIC_SHARING ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  ethtool_ops ; 
 int /*<<< orphan*/  mdio_read ; 
 int /*<<< orphan*/  mdio_write ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int smc91c92_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  smc_interrupt ; 
 int /*<<< orphan*/  smc_netdev_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smc91c92_probe(struct pcmcia_device *link)
{
    struct smc_private *smc;
    struct net_device *dev;

    DEBUG(0, "smc91c92_attach()\n");

    /* Create new ethernet device */
    dev = alloc_etherdev(sizeof(struct smc_private));
    if (!dev)
	return -ENOMEM;
    smc = netdev_priv(dev);
    smc->p_dev = link;
    link->priv = dev;

    spin_lock_init(&smc->lock);
    link->io.NumPorts1 = 16;
    link->io.Attributes1 = IO_DATA_PATH_WIDTH_AUTO;
    link->io.IOAddrLines = 4;
    link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING|IRQ_HANDLE_PRESENT;
    link->irq.IRQInfo1 = IRQ_LEVEL_ID;
    link->irq.Handler = &smc_interrupt;
    link->irq.Instance = dev;
    link->conf.Attributes = CONF_ENABLE_IRQ;
    link->conf.IntType = INT_MEMORY_AND_IO;

    /* The SMC91c92-specific entries in the device structure. */
    dev->netdev_ops = &smc_netdev_ops;
    SET_ETHTOOL_OPS(dev, &ethtool_ops);
    dev->watchdog_timeo = TX_TIMEOUT;

    smc->mii_if.dev = dev;
    smc->mii_if.mdio_read = mdio_read;
    smc->mii_if.mdio_write = mdio_write;
    smc->mii_if.phy_id_mask = 0x1f;
    smc->mii_if.reg_num_mask = 0x1f;

    return smc91c92_config(link);
}