#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_4__ {int /*<<< orphan*/  device_base; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PRV_STATE_OFF ; 
 int /*<<< orphan*/  isl38xx_disable_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  islpci_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 

__attribute__((used)) static int
prism54_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *ndev = pci_get_drvdata(pdev);
	islpci_private *priv = ndev ? netdev_priv(ndev) : NULL;
	BUG_ON(!priv);


	pci_save_state(pdev);

	/* tell the device not to trigger interrupts for now... */
	isl38xx_disable_interrupts(priv->device_base);

	/* from now on assume the hardware was already powered down
	   and don't touch it anymore */
	islpci_set_state(priv, PRV_STATE_OFF);

	netif_stop_queue(ndev);
	netif_device_detach(ndev);

	return 0;
}