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
struct usbdrv_private {int dummy; } ;
struct pci_dev {int dummy; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;

/* Variables and functions */
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  usbdrv_clear_structs (struct net_device*) ; 

void usbdrv_remove1(struct pci_dev *pcid)
{
    struct net_device *dev;
    struct usbdrv_private *macp;

    if (!(dev = (struct net_device *) pci_get_drvdata(pcid)))
        return;

    macp = dev->ml_priv;
    unregister_netdev(dev);

    usbdrv_clear_structs(dev);
}