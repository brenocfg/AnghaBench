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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ems_pci_card {int channels; int /*<<< orphan*/ * conf_addr; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/ * base_addr; struct net_device** net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_sja1000dev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct ems_pci_card*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ems_pci_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_sja1000dev (struct net_device*) ; 

__attribute__((used)) static void ems_pci_del_card(struct pci_dev *pdev)
{
	struct ems_pci_card *card = pci_get_drvdata(pdev);
	struct net_device *dev;
	int i = 0;

	for (i = 0; i < card->channels; i++) {
		dev = card->net_dev[i];

		if (!dev)
			continue;

		dev_info(&pdev->dev, "Removing %s.\n", dev->name);
		unregister_sja1000dev(dev);
		free_sja1000dev(dev);
	}

	if (card->base_addr != NULL)
		pci_iounmap(card->pci_dev, card->base_addr);

	if (card->conf_addr != NULL)
		pci_iounmap(card->pci_dev, card->conf_addr);

	kfree(card);

	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}