#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ismt_priv {int using_msi; TYPE_1__* pci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ismt_priv*) ; 
 int /*<<< orphan*/  ismt_do_interrupt ; 
 int /*<<< orphan*/  ismt_do_msi_interrupt ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int pci_enable_msi (TYPE_1__*) ; 

__attribute__((used)) static int ismt_int_init(struct ismt_priv *priv)
{
	int err;

	/* Try using MSI interrupts */
	err = pci_enable_msi(priv->pci_dev);
	if (err) {
		dev_warn(&priv->pci_dev->dev,
			 "Unable to use MSI interrupts, falling back to legacy\n");
		goto intx;
	}

	err = devm_request_irq(&priv->pci_dev->dev,
			       priv->pci_dev->irq,
			       ismt_do_msi_interrupt,
			       0,
			       "ismt-msi",
			       priv);
	if (err) {
		pci_disable_msi(priv->pci_dev);
		goto intx;
	}

	priv->using_msi = true;
	goto done;

	/* Try using legacy interrupts */
intx:
	err = devm_request_irq(&priv->pci_dev->dev,
			       priv->pci_dev->irq,
			       ismt_do_interrupt,
			       IRQF_SHARED,
			       "ismt-intx",
			       priv);
	if (err) {
		dev_err(&priv->pci_dev->dev, "no usable interrupts\n");
		return -ENODEV;
	}

	priv->using_msi = false;

done:
	return 0;
}