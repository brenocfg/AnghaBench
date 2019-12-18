#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sdhci_pci_slot {TYPE_3__* host; TYPE_2__* chip; } ;
struct TYPE_6__ {int /*<<< orphan*/  quirks; scalar_t__ ioaddr; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {scalar_t__ revision; scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_JMICRON_JMB38X_MMC ; 
 scalar_t__ SDHCI_HOST_VERSION ; 
 int /*<<< orphan*/  SDHCI_QUIRK_BROKEN_ADMA ; 
 int SDHCI_VENDOR_VER_MASK ; 
 int SDHCI_VENDOR_VER_SHIFT ; 
 int /*<<< orphan*/  jmicron_enable_mmc (TYPE_3__*,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int jmicron_probe_slot(struct sdhci_pci_slot *slot)
{
	if (slot->chip->pdev->revision == 0) {
		u16 version;

		version = readl(slot->host->ioaddr + SDHCI_HOST_VERSION);
		version = (version & SDHCI_VENDOR_VER_MASK) >>
			SDHCI_VENDOR_VER_SHIFT;

		/*
		 * Older versions of the chip have lots of nasty glitches
		 * in the ADMA engine. It's best just to avoid it
		 * completely.
		 */
		if (version < 0xAC)
			slot->host->quirks |= SDHCI_QUIRK_BROKEN_ADMA;
	}

	/*
	 * The secondary interface requires a bit set to get the
	 * interrupts.
	 */
	if (slot->chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB38X_MMC)
		jmicron_enable_mmc(slot->host, 1);

	return 0;
}