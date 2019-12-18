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
struct sdhci_pci_chip {int quirks; TYPE_1__* pdev; } ;
struct pci_dev {scalar_t__ bus; int /*<<< orphan*/  devfn; } ;
struct TYPE_2__ {scalar_t__ revision; scalar_t__ device; scalar_t__ bus; int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_JMICRON_JMB38X_MMC ; 
 scalar_t__ PCI_DEVICE_ID_JMICRON_JMB38X_SD ; 
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_JMICRON ; 
 int SDHCI_QUIRK_32BIT_ADMA_SIZE ; 
 int SDHCI_QUIRK_32BIT_DMA_ADDR ; 
 int SDHCI_QUIRK_32BIT_DMA_SIZE ; 
 int SDHCI_QUIRK_BROKEN_SMALL_PIO ; 
 int SDHCI_QUIRK_RESET_AFTER_REQUEST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int jmicron_pmos (struct sdhci_pci_chip*,int) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 

__attribute__((used)) static int jmicron_probe(struct sdhci_pci_chip *chip)
{
	int ret;

	if (chip->pdev->revision == 0) {
		chip->quirks |= SDHCI_QUIRK_32BIT_DMA_ADDR |
			  SDHCI_QUIRK_32BIT_DMA_SIZE |
			  SDHCI_QUIRK_32BIT_ADMA_SIZE |
			  SDHCI_QUIRK_RESET_AFTER_REQUEST |
			  SDHCI_QUIRK_BROKEN_SMALL_PIO;
	}

	/*
	 * JMicron chips can have two interfaces to the same hardware
	 * in order to work around limitations in Microsoft's driver.
	 * We need to make sure we only bind to one of them.
	 *
	 * This code assumes two things:
	 *
	 * 1. The PCI code adds subfunctions in order.
	 *
	 * 2. The MMC interface has a lower subfunction number
	 *    than the SD interface.
	 */
	if (chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB38X_SD) {
		struct pci_dev *sd_dev;

		sd_dev = NULL;
		while ((sd_dev = pci_get_device(PCI_VENDOR_ID_JMICRON,
			PCI_DEVICE_ID_JMICRON_JMB38X_MMC, sd_dev)) != NULL) {
			if ((PCI_SLOT(chip->pdev->devfn) ==
				PCI_SLOT(sd_dev->devfn)) &&
				(chip->pdev->bus == sd_dev->bus))
				break;
		}

		if (sd_dev) {
			pci_dev_put(sd_dev);
			dev_info(&chip->pdev->dev, "Refusing to bind to "
				"secondary interface.\n");
			return -ENODEV;
		}
	}

	/*
	 * JMicron chips need a bit of a nudge to enable the power
	 * output pins.
	 */
	ret = jmicron_pmos(chip, 1);
	if (ret) {
		dev_err(&chip->pdev->dev, "Failure enabling card power\n");
		return ret;
	}

	return 0;
}