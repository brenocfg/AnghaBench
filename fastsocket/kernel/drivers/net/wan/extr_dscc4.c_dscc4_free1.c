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
struct pci_dev {int dummy; } ;
struct dscc4_pci_priv {int /*<<< orphan*/  dev; struct dscc4_pci_priv* root; } ;
struct dscc4_dev_priv {int /*<<< orphan*/  dev; struct dscc4_dev_priv* root; } ;

/* Variables and functions */
 int dev_per_card ; 
 int /*<<< orphan*/  dscc4_to_dev (struct dscc4_pci_priv*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dscc4_pci_priv*) ; 
 struct dscc4_pci_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_hdlc_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dscc4_free1(struct pci_dev *pdev)
{
	struct dscc4_pci_priv *ppriv;
	struct dscc4_dev_priv *root;
	int i;

	ppriv = pci_get_drvdata(pdev);
	root = ppriv->root;

	for (i = 0; i < dev_per_card; i++)
		unregister_hdlc_device(dscc4_to_dev(root + i));

	pci_set_drvdata(pdev, NULL);

	for (i = 0; i < dev_per_card; i++)
		free_netdev(root[i].dev);
	kfree(root);
	kfree(ppriv);
}