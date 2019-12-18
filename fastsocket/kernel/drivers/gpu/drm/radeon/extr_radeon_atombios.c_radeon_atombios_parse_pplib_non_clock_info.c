#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_10__ {int default_power_state_index; TYPE_4__* power_state; int /*<<< orphan*/  default_vddci; scalar_t__ default_vddc; int /*<<< orphan*/  default_mclk; int /*<<< orphan*/  default_sclk; } ;
struct TYPE_6__ {int /*<<< orphan*/  default_sclk; int /*<<< orphan*/  default_mclk; } ;
struct radeon_device {int flags; TYPE_5__ pm; TYPE_1__ clock; } ;
struct _ATOM_PPLIB_NONCLOCK_INFO {int /*<<< orphan*/  usClassification; int /*<<< orphan*/  ulCapsAndSettings; } ;
struct TYPE_9__ {int misc; int misc2; int pcie_lanes; TYPE_3__* clock_info; TYPE_3__* default_clock_mode; void* type; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {scalar_t__ voltage; int /*<<< orphan*/  vddci; } ;
struct TYPE_8__ {TYPE_2__ voltage; int /*<<< orphan*/  sclk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 int ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE ; 
 int ATOM_PPLIB_CLASSIFICATION_BOOT ; 
#define  ATOM_PPLIB_CLASSIFICATION_UI_BALANCED 131 
#define  ATOM_PPLIB_CLASSIFICATION_UI_BATTERY 130 
 int ATOM_PPLIB_CLASSIFICATION_UI_MASK ; 
#define  ATOM_PPLIB_CLASSIFICATION_UI_NONE 129 
#define  ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE 128 
 int ATOM_PPLIB_PCIE_LINK_WIDTH_MASK ; 
 int ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT ; 
 int ATOM_PPLIB_SINGLE_DISPLAY_ONLY ; 
 void* POWER_STATE_TYPE_BALANCED ; 
 void* POWER_STATE_TYPE_BATTERY ; 
 void* POWER_STATE_TYPE_DEFAULT ; 
 void* POWER_STATE_TYPE_PERFORMANCE ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  RADEON_PM_STATE_SINGLE_DISPLAY_ONLY ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_get_default_voltages (struct radeon_device*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void radeon_atombios_parse_pplib_non_clock_info(struct radeon_device *rdev,
						       int state_index, int mode_index,
						       struct _ATOM_PPLIB_NONCLOCK_INFO *non_clock_info)
{
	int j;
	u32 misc = le32_to_cpu(non_clock_info->ulCapsAndSettings);
	u32 misc2 = le16_to_cpu(non_clock_info->usClassification);
	u16 vddc, vddci;

	radeon_atombios_get_default_voltages(rdev, &vddc, &vddci);

	rdev->pm.power_state[state_index].misc = misc;
	rdev->pm.power_state[state_index].misc2 = misc2;
	rdev->pm.power_state[state_index].pcie_lanes =
		((misc & ATOM_PPLIB_PCIE_LINK_WIDTH_MASK) >>
		 ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT) + 1;
	switch (misc2 & ATOM_PPLIB_CLASSIFICATION_UI_MASK) {
	case ATOM_PPLIB_CLASSIFICATION_UI_BATTERY:
		rdev->pm.power_state[state_index].type =
			POWER_STATE_TYPE_BATTERY;
		break;
	case ATOM_PPLIB_CLASSIFICATION_UI_BALANCED:
		rdev->pm.power_state[state_index].type =
			POWER_STATE_TYPE_BALANCED;
		break;
	case ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE:
		rdev->pm.power_state[state_index].type =
			POWER_STATE_TYPE_PERFORMANCE;
		break;
	case ATOM_PPLIB_CLASSIFICATION_UI_NONE:
		if (misc2 & ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE)
			rdev->pm.power_state[state_index].type =
				POWER_STATE_TYPE_PERFORMANCE;
		break;
	}
	rdev->pm.power_state[state_index].flags = 0;
	if (misc & ATOM_PPLIB_SINGLE_DISPLAY_ONLY)
		rdev->pm.power_state[state_index].flags |=
			RADEON_PM_STATE_SINGLE_DISPLAY_ONLY;
	if (misc2 & ATOM_PPLIB_CLASSIFICATION_BOOT) {
		rdev->pm.power_state[state_index].type =
			POWER_STATE_TYPE_DEFAULT;
		rdev->pm.default_power_state_index = state_index;
		rdev->pm.power_state[state_index].default_clock_mode =
			&rdev->pm.power_state[state_index].clock_info[mode_index - 1];
		if (ASIC_IS_DCE5(rdev) && !(rdev->flags & RADEON_IS_IGP)) {
			/* NI chips post without MC ucode, so default clocks are strobe mode only */
			rdev->pm.default_sclk = rdev->pm.power_state[state_index].clock_info[0].sclk;
			rdev->pm.default_mclk = rdev->pm.power_state[state_index].clock_info[0].mclk;
			rdev->pm.default_vddc = rdev->pm.power_state[state_index].clock_info[0].voltage.voltage;
			rdev->pm.default_vddci = rdev->pm.power_state[state_index].clock_info[0].voltage.vddci;
		} else {
			/* patch the table values with the default slck/mclk from firmware info */
			for (j = 0; j < mode_index; j++) {
				rdev->pm.power_state[state_index].clock_info[j].mclk =
					rdev->clock.default_mclk;
				rdev->pm.power_state[state_index].clock_info[j].sclk =
					rdev->clock.default_sclk;
				if (vddc)
					rdev->pm.power_state[state_index].clock_info[j].voltage.voltage =
						vddc;
			}
		}
	}
}