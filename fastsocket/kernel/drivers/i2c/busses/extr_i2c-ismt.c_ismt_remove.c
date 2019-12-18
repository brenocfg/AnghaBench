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
struct ismt_priv {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBBAR ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct ismt_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ismt_remove(struct pci_dev *pdev)
{
	struct ismt_priv *priv = pci_get_drvdata(pdev);

	i2c_del_adapter(&priv->adapter);
	pci_release_region(pdev, SMBBAR);
}