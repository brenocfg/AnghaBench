#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct net_device* Instance; int /*<<< orphan*/  Handler; } ;
struct TYPE_5__ {int ConfigIndex; int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct pcmcia_device {TYPE_2__ irq; TYPE_1__ conf; struct net_device* priv; } ;
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_timeout_task; struct pcmcia_device* p_dev; struct net_device* dev; } ;
typedef  TYPE_3__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  netdev_ethtool_ops ; 
 int /*<<< orphan*/  netdev_ops ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 
 int xirc2ps_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  xirc2ps_interrupt ; 
 int /*<<< orphan*/  xirc2ps_tx_timeout_task ; 

__attribute__((used)) static int
xirc2ps_probe(struct pcmcia_device *link)
{
    struct net_device *dev;
    local_info_t *local;

    DEBUG(0, "attach()\n");

    /* Allocate the device structure */
    dev = alloc_etherdev(sizeof(local_info_t));
    if (!dev)
	    return -ENOMEM;
    local = netdev_priv(dev);
    local->dev = dev;
    local->p_dev = link;
    link->priv = dev;

    /* General socket configuration */
    link->conf.Attributes = CONF_ENABLE_IRQ;
    link->conf.IntType = INT_MEMORY_AND_IO;
    link->conf.ConfigIndex = 1;
    link->irq.Handler = xirc2ps_interrupt;
    link->irq.Instance = dev;

    /* Fill in card specific entries */
    dev->netdev_ops = &netdev_ops;
    dev->ethtool_ops = &netdev_ethtool_ops;
    dev->watchdog_timeo = TX_TIMEOUT;
    INIT_WORK(&local->tx_timeout_task, xirc2ps_tx_timeout_task);

    return xirc2ps_config(link);
}