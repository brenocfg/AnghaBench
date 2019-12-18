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
struct rtl8180_priv {int /*<<< orphan*/  map; } ;
struct pci_dev {int dummy; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ieee80211_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void rtl8180_remove(struct pci_dev *pdev)
{
	struct ieee80211_hw *dev = pci_get_drvdata(pdev);
	struct rtl8180_priv *priv;

	if (!dev)
		return;

	ieee80211_unregister_hw(dev);

	priv = dev->priv;

	pci_iounmap(pdev, priv->map);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	ieee80211_free_hw(dev);
}