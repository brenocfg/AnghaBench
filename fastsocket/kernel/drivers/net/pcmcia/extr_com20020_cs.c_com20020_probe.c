#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct net_device* Instance; int /*<<< orphan*/  IRQInfo1; int /*<<< orphan*/  Attributes; } ;
struct TYPE_10__ {int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct TYPE_9__ {int NumPorts1; int IOAddrLines; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_5__* priv; TYPE_4__ irq; TYPE_3__ conf; TYPE_2__ io; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct com20020_dev_t {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  owner; } ;
struct arcnet_local {int clockm; TYPE_1__ hw; int /*<<< orphan*/  clockp; int /*<<< orphan*/  backplane; int /*<<< orphan*/  timeout; } ;
struct TYPE_12__ {struct net_device* dev; } ;
typedef  TYPE_5__ com20020_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int /*<<< orphan*/  IRQ_TYPE_EXCLUSIVE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct net_device* alloc_arcdev (char*) ; 
 int /*<<< orphan*/  backplane ; 
 int clockm ; 
 int /*<<< orphan*/  clockp ; 
 int com20020_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 TYPE_5__* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  node ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int com20020_probe(struct pcmcia_device *p_dev)
{
    com20020_dev_t *info;
    struct net_device *dev;
    struct arcnet_local *lp;

    DEBUG(0, "com20020_attach()\n");

    /* Create new network device */
    info = kzalloc(sizeof(struct com20020_dev_t), GFP_KERNEL);
    if (!info)
	goto fail_alloc_info;

    dev = alloc_arcdev("");
    if (!dev)
	goto fail_alloc_dev;

    lp = netdev_priv(dev);
    lp->timeout = timeout;
    lp->backplane = backplane;
    lp->clockp = clockp;
    lp->clockm = clockm & 3;
    lp->hw.owner = THIS_MODULE;

    /* fill in our module parameters as defaults */
    dev->dev_addr[0] = node;

    p_dev->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
    p_dev->io.NumPorts1 = 16;
    p_dev->io.IOAddrLines = 16;
    p_dev->irq.Attributes = IRQ_TYPE_EXCLUSIVE;
    p_dev->irq.IRQInfo1 = IRQ_LEVEL_ID;
    p_dev->conf.Attributes = CONF_ENABLE_IRQ;
    p_dev->conf.IntType = INT_MEMORY_AND_IO;

    p_dev->irq.Instance = info->dev = dev;
    p_dev->priv = info;

    return com20020_config(p_dev);

fail_alloc_dev:
    kfree(info);
fail_alloc_info:
    return -ENOMEM;
}