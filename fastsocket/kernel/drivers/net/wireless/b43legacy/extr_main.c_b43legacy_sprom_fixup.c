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
struct ssb_bus {TYPE_2__ sprom; TYPE_1__ boardinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BFL_PACTRL ; 
 scalar_t__ PCI_VENDOR_ID_APPLE ; 

__attribute__((used)) static void b43legacy_sprom_fixup(struct ssb_bus *bus)
{
	/* boardflags workarounds */
	if (bus->boardinfo.vendor == PCI_VENDOR_ID_APPLE &&
	    bus->boardinfo.type == 0x4E &&
	    bus->sprom.board_rev > 0x40)
		bus->sprom.boardflags_lo |= B43legacy_BFL_PACTRL;
}