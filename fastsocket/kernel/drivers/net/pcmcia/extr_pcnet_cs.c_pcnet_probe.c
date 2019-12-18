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
struct TYPE_6__ {int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct TYPE_5__ {int /*<<< orphan*/  IRQInfo1; int /*<<< orphan*/  Attributes; } ;
struct pcmcia_device {TYPE_2__ conf; TYPE_1__ irq; struct net_device* priv; } ;
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_7__ {struct pcmcia_device* p_dev; } ;
typedef  TYPE_3__ pcnet_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int /*<<< orphan*/  IRQ_TYPE_DYNAMIC_SHARING ; 
 TYPE_3__* PRIV (struct net_device*) ; 
 struct net_device* __alloc_ei_netdev (int) ; 
 int pcnet_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcnet_netdev_ops ; 

__attribute__((used)) static int pcnet_probe(struct pcmcia_device *link)
{
    pcnet_dev_t *info;
    struct net_device *dev;

    DEBUG(0, "pcnet_attach()\n");

    /* Create new ethernet device */
    dev = __alloc_ei_netdev(sizeof(pcnet_dev_t));
    if (!dev) return -ENOMEM;
    info = PRIV(dev);
    info->p_dev = link;
    link->priv = dev;

    link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
    link->irq.IRQInfo1 = IRQ_LEVEL_ID;
    link->conf.Attributes = CONF_ENABLE_IRQ;
    link->conf.IntType = INT_MEMORY_AND_IO;

    dev->netdev_ops = &pcnet_netdev_ops;

    return pcnet_config(link);
}