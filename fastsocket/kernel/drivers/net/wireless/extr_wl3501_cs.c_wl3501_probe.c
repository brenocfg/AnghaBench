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
struct TYPE_7__ {int /*<<< orphan*/ * spy_data; } ;
struct wl3501_card {TYPE_3__ wireless_data; struct pcmcia_device* p_dev; int /*<<< orphan*/  spy_data; } ;
struct TYPE_8__ {int Attributes; struct net_device* Instance; int /*<<< orphan*/  Handler; int /*<<< orphan*/  IRQInfo1; } ;
struct TYPE_6__ {int ConfigIndex; int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct TYPE_5__ {int NumPorts1; int IOAddrLines; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_4__ irq; struct net_device* priv; TYPE_2__ conf; TYPE_1__ io; } ;
struct net_device {int watchdog_timeo; int /*<<< orphan*/ * wireless_handlers; TYPE_3__* wireless_data; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int IRQ_HANDLE_PRESENT ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int IRQ_TYPE_DYNAMIC_SHARING ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  ops ; 
 int wl3501_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  wl3501_handler_def ; 
 int /*<<< orphan*/  wl3501_interrupt ; 
 int /*<<< orphan*/  wl3501_netdev_ops ; 

__attribute__((used)) static int wl3501_probe(struct pcmcia_device *p_dev)
{
	struct net_device *dev;
	struct wl3501_card *this;

	/* The io structure describes IO port mapping */
	p_dev->io.NumPorts1	= 16;
	p_dev->io.Attributes1	= IO_DATA_PATH_WIDTH_8;
	p_dev->io.IOAddrLines	= 5;

	/* Interrupt setup */
	p_dev->irq.Attributes	= IRQ_TYPE_DYNAMIC_SHARING | IRQ_HANDLE_PRESENT;
	p_dev->irq.IRQInfo1	= IRQ_LEVEL_ID;
	p_dev->irq.Handler = wl3501_interrupt;

	/* General socket configuration */
	p_dev->conf.Attributes	= CONF_ENABLE_IRQ;
	p_dev->conf.IntType	= INT_MEMORY_AND_IO;
	p_dev->conf.ConfigIndex	= 1;

	dev = alloc_etherdev(sizeof(struct wl3501_card));
	if (!dev)
		goto out_link;


	dev->netdev_ops		= &wl3501_netdev_ops;
	dev->watchdog_timeo	= 5 * HZ;

	this = netdev_priv(dev);
	this->wireless_data.spy_data = &this->spy_data;
	this->p_dev = p_dev;
	dev->wireless_data	= &this->wireless_data;
	dev->wireless_handlers	= &wl3501_handler_def;
	SET_ETHTOOL_OPS(dev, &ops);
	netif_stop_queue(dev);
	p_dev->priv = p_dev->irq.Instance = dev;

	return wl3501_config(p_dev);
out_link:
	return -ENOMEM;
}