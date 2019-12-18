#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct net2280 {TYPE_2__ gadget; scalar_t__ enabled; scalar_t__ region; scalar_t__ regs; scalar_t__ got_irq; scalar_t__ requests; TYPE_1__* ep; int /*<<< orphan*/  driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_dma; int /*<<< orphan*/  dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFO (struct net2280*,char*) ; 
 int /*<<< orphan*/  dev_attr_registers ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net2280*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  net2280_led_shutdown (struct net2280*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net2280* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  pci_pool_free (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * the_controller ; 

__attribute__((used)) static void net2280_remove (struct pci_dev *pdev)
{
	struct net2280		*dev = pci_get_drvdata (pdev);

	BUG_ON(dev->driver);

	/* then clean up the resources we allocated during probe() */
	net2280_led_shutdown (dev);
	if (dev->requests) {
		int		i;
		for (i = 1; i < 5; i++) {
			if (!dev->ep [i].dummy)
				continue;
			pci_pool_free (dev->requests, dev->ep [i].dummy,
					dev->ep [i].td_dma);
		}
		pci_pool_destroy (dev->requests);
	}
	if (dev->got_irq)
		free_irq (pdev->irq, dev);
	if (dev->regs)
		iounmap (dev->regs);
	if (dev->region)
		release_mem_region (pci_resource_start (pdev, 0),
				pci_resource_len (pdev, 0));
	if (dev->enabled)
		pci_disable_device (pdev);
	device_unregister (&dev->gadget.dev);
	device_remove_file (&pdev->dev, &dev_attr_registers);
	pci_set_drvdata (pdev, NULL);

	INFO (dev, "unbind\n");

	the_controller = NULL;
}