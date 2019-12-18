#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * resource; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  retries; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct ismt_priv {TYPE_3__ adapter; int /*<<< orphan*/  smba; struct pci_dev* pci_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  ISMT_MAX_RETRIES ; 
 size_t SMBBAR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int acpi_check_resource_conflict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct ismt_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_3__*,struct ismt_priv*) ; 
 int ismt_dev_init (struct ismt_priv*) ; 
 TYPE_2__ ismt_driver ; 
 int /*<<< orphan*/  ismt_hw_init (struct ismt_priv*) ; 
 int ismt_int_init (struct ismt_priv*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,size_t) ; 
 int pci_request_region (struct pci_dev*,size_t,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_len (struct pci_dev*,size_t) ; 
 unsigned long pci_resource_start (struct pci_dev*,size_t) ; 
 scalar_t__ pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ismt_priv*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,size_t,unsigned long) ; 
 int /*<<< orphan*/  smbus_algorithm ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned long) ; 

__attribute__((used)) static int
ismt_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int err;
	struct ismt_priv *priv;
	unsigned long start, len;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	pci_set_drvdata(pdev, priv);
	i2c_set_adapdata(&priv->adapter, priv);
	priv->adapter.owner = THIS_MODULE;

	priv->adapter.class = I2C_CLASS_HWMON;

	priv->adapter.algo = &smbus_algorithm;

	/* set up the sysfs linkage to our parent device */
	priv->adapter.dev.parent = &pdev->dev;

	/* number of retries on lost arbitration */
	priv->adapter.retries = ISMT_MAX_RETRIES;

	priv->pci_dev = pdev;

	err = pcim_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "Failed to enable SMBus PCI device (%d)\n",
			err);
		return err;
	}

	/* enable bus mastering */
	pci_set_master(pdev);

	/* Determine the address of the SMBus area */
	start = pci_resource_start(pdev, SMBBAR);
	len = pci_resource_len(pdev, SMBBAR);
	if (!start || !len) {
		dev_err(&pdev->dev,
			"SMBus base address uninitialized, upgrade BIOS\n");
		return -ENODEV;
	}

	snprintf(priv->adapter.name, sizeof(priv->adapter.name),
		 "SMBus iSMT adapter at %lx", start);

	dev_dbg(&priv->pci_dev->dev, " start=0x%lX\n", start);
	dev_dbg(&priv->pci_dev->dev, " len=0x%lX\n", len);

	err = acpi_check_resource_conflict(&pdev->resource[SMBBAR]);
	if (err) {
		dev_err(&pdev->dev, "ACPI resource conflict!\n");
		return err;
	}

	err = pci_request_region(pdev, SMBBAR, ismt_driver.name);
	if (err) {
		dev_err(&pdev->dev,
			"Failed to request SMBus region 0x%lx-0x%lx\n",
			start, start + len);
		return err;
	}

	priv->smba = pcim_iomap(pdev, SMBBAR, len);
	if (!priv->smba) {
		dev_err(&pdev->dev, "Unable to ioremap SMBus BAR\n");
		err = -ENODEV;
		goto fail;
	}

	if ((pci_set_dma_mask(pdev, DMA_BIT_MASK(64)) != 0) ||
	    (pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64)) != 0)) {
		if ((pci_set_dma_mask(pdev, DMA_BIT_MASK(32)) != 0) ||
		    (pci_set_consistent_dma_mask(pdev,
						 DMA_BIT_MASK(32)) != 0)) {
			dev_err(&pdev->dev, "pci_set_dma_mask fail %p\n",
				pdev);
			goto fail;
		}
	}

	err = ismt_dev_init(priv);
	if (err)
		goto fail;

	ismt_hw_init(priv);

	err = ismt_int_init(priv);
	if (err)
		goto fail;

	err = i2c_add_adapter(&priv->adapter);
	if (err) {
		dev_err(&pdev->dev, "Failed to add SMBus iSMT adapter\n");
		err = -ENODEV;
		goto fail;
	}
	return 0;

fail:
	pci_release_region(pdev, SMBBAR);
	return err;
}