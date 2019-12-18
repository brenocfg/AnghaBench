#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int board_rev; int /*<<< orphan*/  boardflags_lo; } ;
struct TYPE_3__ {scalar_t__ vendor; int type; } ;
struct ssb_bus {int chip_id; scalar_t__ bustype; TYPE_2__ sprom; struct pci_dev* host_pci; TYPE_1__ boardinfo; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUSTEK ; 
 int /*<<< orphan*/  B43_BFL_BTCOEXIST ; 
 int /*<<< orphan*/  B43_BFL_PACTRL ; 
 int /*<<< orphan*/  BROADCOM ; 
 int /*<<< orphan*/  DELL ; 
 int /*<<< orphan*/  HP ; 
 scalar_t__ IS_PDEV (struct pci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LINKSYS ; 
 int /*<<< orphan*/  MOTOROLA ; 
 scalar_t__ PCI_VENDOR_ID_APPLE ; 
 scalar_t__ SSB_BOARDVENDOR_DELL ; 
 scalar_t__ SSB_BUSTYPE_PCI ; 

__attribute__((used)) static void b43_sprom_fixup(struct ssb_bus *bus)
{
	struct pci_dev *pdev;

	/* boardflags workarounds */
	if (bus->boardinfo.vendor == SSB_BOARDVENDOR_DELL &&
	    bus->chip_id == 0x4301 && bus->sprom.board_rev == 0x74)
		bus->sprom.boardflags_lo |= B43_BFL_BTCOEXIST;
	if (bus->boardinfo.vendor == PCI_VENDOR_ID_APPLE &&
	    bus->boardinfo.type == 0x4E && bus->sprom.board_rev > 0x40)
		bus->sprom.boardflags_lo |= B43_BFL_PACTRL;
	if (bus->bustype == SSB_BUSTYPE_PCI) {
		pdev = bus->host_pci;
		if (IS_PDEV(pdev, BROADCOM, 0x4318, ASUSTEK, 0x100F) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320,    DELL, 0x0003) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320,      HP, 0x12f8) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320, LINKSYS, 0x0015) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320, LINKSYS, 0x0014) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320, LINKSYS, 0x0013) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320, MOTOROLA, 0x7010))
			bus->sprom.boardflags_lo &= ~B43_BFL_BTCOEXIST;
	}
}