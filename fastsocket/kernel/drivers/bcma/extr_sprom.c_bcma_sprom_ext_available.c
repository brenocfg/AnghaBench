#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int id; } ;
struct TYPE_7__ {int capabilities; TYPE_4__* core; } ;
struct bcma_bus {TYPE_1__ chipinfo; TYPE_3__ drv_cc; } ;
struct TYPE_6__ {int rev; } ;
struct TYPE_8__ {TYPE_2__ id; } ;

/* Variables and functions */
 int BCMA_CC_CAP_SPROM ; 
 int /*<<< orphan*/  BCMA_CC_CHIPSTAT ; 
 int BCMA_CC_CHIPST_4313_SPROM_PRESENT ; 
 int BCMA_CC_CHIPST_4331_SPROM_PRESENT ; 
 int /*<<< orphan*/  BCMA_CC_SROM_CONTROL ; 
 int BCMA_CC_SROM_CONTROL_PRESENT ; 
#define  BCMA_CHIP_ID_BCM4313 129 
#define  BCMA_CHIP_ID_BCM4331 128 
 int bcma_read32 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bcma_sprom_ext_available(struct bcma_bus *bus)
{
	u32 chip_status;
	u32 srom_control;
	u32 present_mask;

	if (bus->drv_cc.core->id.rev >= 31) {
		if (!(bus->drv_cc.capabilities & BCMA_CC_CAP_SPROM))
			return false;

		srom_control = bcma_read32(bus->drv_cc.core,
					   BCMA_CC_SROM_CONTROL);
		return srom_control & BCMA_CC_SROM_CONTROL_PRESENT;
	}

	/* older chipcommon revisions use chip status register */
	chip_status = bcma_read32(bus->drv_cc.core, BCMA_CC_CHIPSTAT);
	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
		present_mask = BCMA_CC_CHIPST_4313_SPROM_PRESENT;
		break;

	case BCMA_CHIP_ID_BCM4331:
		present_mask = BCMA_CC_CHIPST_4331_SPROM_PRESENT;
		break;

	default:
		return true;
	}

	return chip_status & present_mask;
}