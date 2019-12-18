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
typedef  int u8 ;
struct usb_hcd {int dummy; } ;
struct pci_dev {int dummy; } ;
struct ohci_hcd {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_QUIRK_AMD_PLL ; 
 int /*<<< orphan*/  OHCI_QUIRK_AMD_PREFETCH ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_ATI_SBX00_SMBUS ; 
 int /*<<< orphan*/  PCI_REVISION_ID ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_ATI ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_dbg (struct ohci_hcd*,char*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ usb_amd_find_chipset_info () ; 

__attribute__((used)) static int ohci_quirk_amd700(struct usb_hcd *hcd)
{
	struct ohci_hcd *ohci = hcd_to_ohci(hcd);
	struct pci_dev *amd_smbus_dev;
	u8 rev = 0;

	if (usb_amd_find_chipset_info())
		ohci->flags |= OHCI_QUIRK_AMD_PLL;

	amd_smbus_dev = pci_get_device(PCI_VENDOR_ID_ATI,
			PCI_DEVICE_ID_ATI_SBX00_SMBUS, NULL);
	if (!amd_smbus_dev)
		return 0;

	pci_read_config_byte(amd_smbus_dev, PCI_REVISION_ID, &rev);

	/* SB800 needs pre-fetch fix */
	if ((rev >= 0x40) && (rev <= 0x4f)) {
		ohci->flags |= OHCI_QUIRK_AMD_PREFETCH;
		ohci_dbg(ohci, "enabled AMD prefetch quirk\n");
	}

	pci_dev_put(amd_smbus_dev);
	amd_smbus_dev = NULL;

	return 0;
}