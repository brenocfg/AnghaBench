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
typedef  int u64 ;
struct whci_card {struct pci_dev* pci; } ;
struct pci_dev {scalar_t__ vendor; int device; int class; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int UWBCAPDATA_TO_CAP_ID (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__,int,int,unsigned int,unsigned long long,unsigned long long) ; 

__attribute__((used)) static
u64 whci_capdata_quirks(struct whci_card *card, u64 capdata)
{
	u64 capdata_orig = capdata;
	struct pci_dev *pci_dev = card->pci;
	if (pci_dev->vendor == PCI_VENDOR_ID_INTEL
	    && (pci_dev->device == 0x0c3b || pci_dev->device == 0004)
	    && pci_dev->class == 0x0d1010) {
		switch (UWBCAPDATA_TO_CAP_ID(capdata)) {
			/* WLP capability has 0x100 bytes of aperture */
		case 0x80:
			capdata |= 0x40 << 8; break;
			/* WUSB capability has 0x80 bytes of aperture
			 * and ID is 1 */
		case 0x02:
			capdata &= ~0xffff;
			capdata |= 0x2001;
			break;
		}
	}
	if (capdata_orig != capdata)
		dev_warn(&pci_dev->dev,
			 "PCI v%04x d%04x c%06x#%02x: "
			 "corrected capdata from %016Lx to %016Lx\n",
			 pci_dev->vendor, pci_dev->device, pci_dev->class,
			 (unsigned)UWBCAPDATA_TO_CAP_ID(capdata),
			 (unsigned long long)capdata_orig,
			 (unsigned long long)capdata);
	return capdata;
}