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
struct usbdrv_private {int /*<<< orphan*/  pdev; int /*<<< orphan*/  regp; struct usbdrv_private* ml_priv; } ;
struct net_device {int /*<<< orphan*/  pdev; int /*<<< orphan*/  regp; struct net_device* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct usbdrv_private*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void usbdrv_clear_structs(struct net_device *dev)
{
    struct usbdrv_private *macp = dev->ml_priv;


#if (WLAN_HOSTIF == WLAN_PCI)
    iounmap(macp->regp);

    pci_release_regions(macp->pdev);
    pci_disable_device(macp->pdev);
    pci_set_drvdata(macp->pdev, NULL);
#endif

    kfree(macp);

    kfree(dev);

}