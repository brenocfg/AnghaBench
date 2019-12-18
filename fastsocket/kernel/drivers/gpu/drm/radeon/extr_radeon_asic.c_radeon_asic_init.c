#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int flags; int num_crtc; int family; TYPE_3__* asic; int /*<<< orphan*/ * bios; } ;
struct TYPE_23__ {int /*<<< orphan*/ * set_memory_clock; int /*<<< orphan*/ * get_memory_clock; int /*<<< orphan*/ * set_engine_clock; int /*<<< orphan*/ * get_engine_clock; } ;
struct TYPE_22__ {int /*<<< orphan*/ * set_backlight_level; } ;
struct TYPE_24__ {TYPE_2__ pm; TYPE_1__ display; } ;

/* Variables and functions */
#define  CHIP_ARUBA 183 
#define  CHIP_BARTS 182 
#define  CHIP_CAICOS 181 
#define  CHIP_CAYMAN 180 
#define  CHIP_CEDAR 179 
#define  CHIP_CYPRESS 178 
#define  CHIP_HEMLOCK 177 
#define  CHIP_JUNIPER 176 
#define  CHIP_OLAND 175 
#define  CHIP_PALM 174 
#define  CHIP_PITCAIRN 173 
#define  CHIP_R100 172 
#define  CHIP_R200 171 
#define  CHIP_R300 170 
#define  CHIP_R350 169 
#define  CHIP_R420 168 
#define  CHIP_R423 167 
#define  CHIP_R520 166 
#define  CHIP_R580 165 
#define  CHIP_R600 164 
#define  CHIP_REDWOOD 163 
#define  CHIP_RS100 162 
#define  CHIP_RS200 161 
#define  CHIP_RS300 160 
#define  CHIP_RS400 159 
#define  CHIP_RS480 158 
#define  CHIP_RS600 157 
#define  CHIP_RS690 156 
#define  CHIP_RS740 155 
#define  CHIP_RS780 154 
#define  CHIP_RS880 153 
#define  CHIP_RV100 152 
#define  CHIP_RV200 151 
#define  CHIP_RV250 150 
#define  CHIP_RV280 149 
#define  CHIP_RV350 148 
#define  CHIP_RV380 147 
#define  CHIP_RV410 146 
#define  CHIP_RV515 145 
#define  CHIP_RV530 144 
#define  CHIP_RV560 143 
#define  CHIP_RV570 142 
#define  CHIP_RV610 141 
#define  CHIP_RV620 140 
#define  CHIP_RV630 139 
#define  CHIP_RV635 138 
#define  CHIP_RV670 137 
#define  CHIP_RV710 136 
#define  CHIP_RV730 135 
#define  CHIP_RV740 134 
#define  CHIP_RV770 133 
#define  CHIP_SUMO 132 
#define  CHIP_SUMO2 131 
#define  CHIP_TAHITI 130 
#define  CHIP_TURKS 129 
#define  CHIP_VERDE 128 
 int EINVAL ; 
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int RADEON_SINGLE_CRTC ; 
 TYPE_3__ btc_asic ; 
 TYPE_3__ cayman_asic ; 
 TYPE_3__ evergreen_asic ; 
 TYPE_3__ r100_asic ; 
 TYPE_3__ r200_asic ; 
 TYPE_3__ r300_asic ; 
 TYPE_3__ r300_asic_pcie ; 
 TYPE_3__ r420_asic ; 
 TYPE_3__ r520_asic ; 
 TYPE_3__ r600_asic ; 
 int /*<<< orphan*/  radeon_legacy_get_engine_clock ; 
 int /*<<< orphan*/  radeon_legacy_get_memory_clock ; 
 int /*<<< orphan*/  radeon_legacy_set_backlight_level ; 
 int /*<<< orphan*/  radeon_legacy_set_engine_clock ; 
 int /*<<< orphan*/  radeon_register_accessor_init (struct radeon_device*) ; 
 TYPE_3__ rs400_asic ; 
 TYPE_3__ rs600_asic ; 
 TYPE_3__ rs690_asic ; 
 TYPE_3__ rs780_asic ; 
 TYPE_3__ rv515_asic ; 
 TYPE_3__ rv770_asic ; 
 TYPE_3__ si_asic ; 
 TYPE_3__ sumo_asic ; 
 TYPE_3__ trinity_asic ; 

int radeon_asic_init(struct radeon_device *rdev)
{
	radeon_register_accessor_init(rdev);

	/* set the number of crtcs */
	if (rdev->flags & RADEON_SINGLE_CRTC)
		rdev->num_crtc = 1;
	else
		rdev->num_crtc = 2;

	switch (rdev->family) {
	case CHIP_R100:
	case CHIP_RV100:
	case CHIP_RS100:
	case CHIP_RV200:
	case CHIP_RS200:
		rdev->asic = &r100_asic;
		break;
	case CHIP_R200:
	case CHIP_RV250:
	case CHIP_RS300:
	case CHIP_RV280:
		rdev->asic = &r200_asic;
		break;
	case CHIP_R300:
	case CHIP_R350:
	case CHIP_RV350:
	case CHIP_RV380:
		if (rdev->flags & RADEON_IS_PCIE)
			rdev->asic = &r300_asic_pcie;
		else
			rdev->asic = &r300_asic;
		break;
	case CHIP_R420:
	case CHIP_R423:
	case CHIP_RV410:
		rdev->asic = &r420_asic;
		/* handle macs */
		if (rdev->bios == NULL) {
			rdev->asic->pm.get_engine_clock = &radeon_legacy_get_engine_clock;
			rdev->asic->pm.set_engine_clock = &radeon_legacy_set_engine_clock;
			rdev->asic->pm.get_memory_clock = &radeon_legacy_get_memory_clock;
			rdev->asic->pm.set_memory_clock = NULL;
			rdev->asic->display.set_backlight_level = &radeon_legacy_set_backlight_level;
		}
		break;
	case CHIP_RS400:
	case CHIP_RS480:
		rdev->asic = &rs400_asic;
		break;
	case CHIP_RS600:
		rdev->asic = &rs600_asic;
		break;
	case CHIP_RS690:
	case CHIP_RS740:
		rdev->asic = &rs690_asic;
		break;
	case CHIP_RV515:
		rdev->asic = &rv515_asic;
		break;
	case CHIP_R520:
	case CHIP_RV530:
	case CHIP_RV560:
	case CHIP_RV570:
	case CHIP_R580:
		rdev->asic = &r520_asic;
		break;
	case CHIP_R600:
	case CHIP_RV610:
	case CHIP_RV630:
	case CHIP_RV620:
	case CHIP_RV635:
	case CHIP_RV670:
		rdev->asic = &r600_asic;
		break;
	case CHIP_RS780:
	case CHIP_RS880:
		rdev->asic = &rs780_asic;
		break;
	case CHIP_RV770:
	case CHIP_RV730:
	case CHIP_RV710:
	case CHIP_RV740:
		rdev->asic = &rv770_asic;
		break;
	case CHIP_CEDAR:
	case CHIP_REDWOOD:
	case CHIP_JUNIPER:
	case CHIP_CYPRESS:
	case CHIP_HEMLOCK:
		/* set num crtcs */
		if (rdev->family == CHIP_CEDAR)
			rdev->num_crtc = 4;
		else
			rdev->num_crtc = 6;
		rdev->asic = &evergreen_asic;
		break;
	case CHIP_PALM:
	case CHIP_SUMO:
	case CHIP_SUMO2:
		rdev->asic = &sumo_asic;
		break;
	case CHIP_BARTS:
	case CHIP_TURKS:
	case CHIP_CAICOS:
		/* set num crtcs */
		if (rdev->family == CHIP_CAICOS)
			rdev->num_crtc = 4;
		else
			rdev->num_crtc = 6;
		rdev->asic = &btc_asic;
		break;
	case CHIP_CAYMAN:
		rdev->asic = &cayman_asic;
		/* set num crtcs */
		rdev->num_crtc = 6;
		break;
	case CHIP_ARUBA:
		rdev->asic = &trinity_asic;
		/* set num crtcs */
		rdev->num_crtc = 4;
		break;
	case CHIP_TAHITI:
	case CHIP_PITCAIRN:
	case CHIP_VERDE:
	case CHIP_OLAND:
		rdev->asic = &si_asic;
		/* set num crtcs */
		if (rdev->family == CHIP_OLAND)
			rdev->num_crtc = 2;
		else
			rdev->num_crtc = 6;
		break;
	default:
		/* FIXME: not supported yet */
		return -EINVAL;
	}

	if (rdev->flags & RADEON_IS_IGP) {
		rdev->asic->pm.get_memory_clock = NULL;
		rdev->asic->pm.set_memory_clock = NULL;
	}

	return 0;
}