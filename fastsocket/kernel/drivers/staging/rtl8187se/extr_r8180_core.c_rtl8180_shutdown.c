#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static void rtl8180_shutdown (struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	if (dev->netdev_ops->ndo_stop)
		dev->netdev_ops->ndo_stop(dev);
	pci_disable_device(pdev);
}