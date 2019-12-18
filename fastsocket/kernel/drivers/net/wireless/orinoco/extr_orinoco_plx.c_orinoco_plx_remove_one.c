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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  iobase; } ;
struct orinoco_private {TYPE_1__ hw; struct orinoco_pci_card* card; } ;
struct orinoco_pci_card {int /*<<< orphan*/  bridge_io; int /*<<< orphan*/  attr_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct orinoco_private*) ; 
 int /*<<< orphan*/  free_orinocodev (struct orinoco_private*) ; 
 int /*<<< orphan*/  orinoco_if_del (struct orinoco_private*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct orinoco_private* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void orinoco_plx_remove_one(struct pci_dev *pdev)
{
	struct orinoco_private *priv = pci_get_drvdata(pdev);
	struct orinoco_pci_card *card = priv->card;

	orinoco_if_del(priv);
	free_irq(pdev->irq, priv);
	pci_set_drvdata(pdev, NULL);
	free_orinocodev(priv);
	pci_iounmap(pdev, priv->hw.iobase);
	pci_iounmap(pdev, card->attr_io);
	pci_iounmap(pdev, card->bridge_io);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}