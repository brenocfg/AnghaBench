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
struct pcmcia_device {struct com20020_dev_t* priv; scalar_t__ dev_node; } ;
struct net_device {scalar_t__ irq; } ;
struct com20020_dev_t {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  com20020_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct com20020_dev_t*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void com20020_detach(struct pcmcia_device *link)
{
    struct com20020_dev_t *info = link->priv;
    struct net_device *dev = info->dev;

    DEBUG(1,"detach...\n");

    DEBUG(0, "com20020_detach(0x%p)\n", link);

    if (link->dev_node) {
	DEBUG(1,"unregister...\n");

	unregister_netdev(dev);

	/*
	 * this is necessary because we register our IRQ separately
	 * from card services.
	 */
	if (dev->irq)
	    free_irq(dev->irq, dev);
    }

    com20020_release(link);

    /* Unlink device structure, free bits */
    DEBUG(1,"unlinking...\n");
    if (link->priv)
    {
	dev = info->dev;
	if (dev)
	{
	    DEBUG(1,"kfree...\n");
	    free_netdev(dev);
	}
	DEBUG(1,"kfree2...\n");
	kfree(info);
    }

}