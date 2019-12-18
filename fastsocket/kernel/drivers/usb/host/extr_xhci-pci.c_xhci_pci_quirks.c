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
struct xhci_hcd {int hci_version; int limit_active_eps; int /*<<< orphan*/  quirks; } ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int revision; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_ASROCK_P67 ; 
 scalar_t__ PCI_DEVICE_ID_FRESCO_LOGIC_FL1400 ; 
 scalar_t__ PCI_DEVICE_ID_FRESCO_LOGIC_PDK ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_PANTHERPOINT_XHCI ; 
 scalar_t__ PCI_VENDOR_ID_AMD ; 
 scalar_t__ PCI_VENDOR_ID_ETRON ; 
 scalar_t__ PCI_VENDOR_ID_FRESCO_LOGIC ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 scalar_t__ PCI_VENDOR_ID_NEC ; 
 scalar_t__ PCI_VENDOR_ID_VIA ; 
 int /*<<< orphan*/  XHCI_AMD_0x96_HOST ; 
 int /*<<< orphan*/  XHCI_AMD_PLL_FIX ; 
 int /*<<< orphan*/  XHCI_AVOID_BEI ; 
 int /*<<< orphan*/  XHCI_BROKEN_MSI ; 
 int /*<<< orphan*/  XHCI_EP_LIMIT_QUIRK ; 
 int /*<<< orphan*/  XHCI_INTEL_HOST ; 
 int /*<<< orphan*/  XHCI_LPM_SUPPORT ; 
 int /*<<< orphan*/  XHCI_NEC_HOST ; 
 int /*<<< orphan*/  XHCI_RESET_EP_QUIRK ; 
 int /*<<< orphan*/  XHCI_RESET_ON_RESUME ; 
 int /*<<< orphan*/  XHCI_SPURIOUS_REBOOT ; 
 int /*<<< orphan*/  XHCI_SPURIOUS_SUCCESS ; 
 int /*<<< orphan*/  XHCI_SW_BW_CHECKING ; 
 int /*<<< orphan*/  XHCI_TRUST_TX_LENGTH ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 scalar_t__ usb_amd_find_chipset_info () ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,...) ; 

__attribute__((used)) static void xhci_pci_quirks(struct device *dev, struct xhci_hcd *xhci)
{
	struct pci_dev		*pdev = to_pci_dev(dev);

	/* Look for vendor-specific quirks */
	if (pdev->vendor == PCI_VENDOR_ID_FRESCO_LOGIC &&
			(pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK ||
			 pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_FL1400)) {
		if (pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK &&
				pdev->revision == 0x0) {
			xhci->quirks |= XHCI_RESET_EP_QUIRK;
			xhci_dbg(xhci, "QUIRK: Fresco Logic xHC needs configure"
					" endpoint cmd after reset endpoint\n");
		}
		/* Fresco Logic confirms: all revisions of this chip do not
		 * support MSI, even though some of them claim to in their PCI
		 * capabilities.
		 */
		xhci->quirks |= XHCI_BROKEN_MSI;
		xhci_dbg(xhci, "QUIRK: Fresco Logic revision %u "
				"has broken MSI implementation\n",
				pdev->revision);
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;
	}

	if (pdev->vendor == PCI_VENDOR_ID_NEC)
		xhci->quirks |= XHCI_NEC_HOST;

	if (pdev->vendor == PCI_VENDOR_ID_AMD && xhci->hci_version == 0x96)
		xhci->quirks |= XHCI_AMD_0x96_HOST;

	/* AMD PLL quirk */
	if (pdev->vendor == PCI_VENDOR_ID_AMD && usb_amd_find_chipset_info())
		xhci->quirks |= XHCI_AMD_PLL_FIX;
	if (pdev->vendor == PCI_VENDOR_ID_INTEL) {
		xhci->quirks |= XHCI_LPM_SUPPORT;
		xhci->quirks |= XHCI_INTEL_HOST;
	}
	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
			pdev->device == PCI_DEVICE_ID_INTEL_PANTHERPOINT_XHCI) {
		xhci->quirks |= XHCI_SPURIOUS_SUCCESS;
		xhci->quirks |= XHCI_EP_LIMIT_QUIRK;
		xhci->limit_active_eps = 64;
		xhci->quirks |= XHCI_SW_BW_CHECKING;
		/*
		 * PPT desktop boards DH77EB and DH77DF will power back on after
		 * a few seconds of being shutdown.  The fix for this is to
		 * switch the ports from xHCI to EHCI on shutdown.  We can't use
		 * DMI information to find those particular boards (since each
		 * vendor will change the board name), so we have to key off all
		 * PPT chipsets.
		 */
		xhci->quirks |= XHCI_SPURIOUS_REBOOT;
		xhci->quirks |= XHCI_AVOID_BEI;
	}
	if (pdev->vendor == PCI_VENDOR_ID_ETRON &&
			pdev->device == PCI_DEVICE_ID_ASROCK_P67) {
		xhci->quirks |= XHCI_RESET_ON_RESUME;
		xhci_dbg(xhci, "QUIRK: Resetting on resume\n");
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;
	}
	if (pdev->vendor == PCI_VENDOR_ID_VIA)
		xhci->quirks |= XHCI_RESET_ON_RESUME;
}