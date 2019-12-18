#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ucNonClockStateIndex; int* ucClockStateIndices; } ;
union pplib_power_state {TYPE_1__ v1; } ;
typedef  union pplib_clock_info {int dummy; } pplib_clock_info ;
struct TYPE_9__ {int ucNumStates; int ucStateEntrySize; int ucNonClockSize; int ucClockInfoSize; int /*<<< orphan*/  usClockInfoArrayOffset; int /*<<< orphan*/  usNonClockInfoArrayOffset; int /*<<< orphan*/  usStateArrayOffset; int /*<<< orphan*/  sThermalController; } ;
union power_info {TYPE_2__ pplib; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct radeon_power_state {int dummy; } ;
struct radeon_pm_clock_info {int dummy; } ;
struct radeon_mode_info {TYPE_7__* atom_context; } ;
struct TYPE_13__ {int default_power_state_index; TYPE_5__* power_state; } ;
struct TYPE_10__ {int /*<<< orphan*/  default_sclk; int /*<<< orphan*/  default_mclk; } ;
struct radeon_device {TYPE_6__ pm; TYPE_3__ clock; struct radeon_mode_info mode_info; } ;
struct _ATOM_PPLIB_NONCLOCK_INFO {int dummy; } ;
struct TYPE_14__ {scalar_t__ bios; } ;
struct TYPE_12__ {int num_clock_modes; TYPE_4__* clock_info; TYPE_4__* default_clock_mode; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  sclk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_DEFAULT ; 
 int /*<<< orphan*/  PowerPlayInfo ; 
 int /*<<< orphan*/  RADEON_PM_MODE_NO_DISPLAY ; 
 int /*<<< orphan*/  atom_parse_data_header (TYPE_7__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_add_pplib_thermal_controller (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int radeon_atombios_parse_pplib_clock_info (struct radeon_device*,int,int,union pplib_clock_info*) ; 
 int /*<<< orphan*/  radeon_atombios_parse_pplib_non_clock_info (struct radeon_device*,int,int,struct _ATOM_PPLIB_NONCLOCK_INFO*) ; 

__attribute__((used)) static int radeon_atombios_parse_power_table_4_5(struct radeon_device *rdev)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	struct _ATOM_PPLIB_NONCLOCK_INFO *non_clock_info;
	union pplib_power_state *power_state;
	int i, j;
	int state_index = 0, mode_index = 0;
	union pplib_clock_info *clock_info;
	bool valid;
	union power_info *power_info;
	int index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
        u16 data_offset;
	u8 frev, crev;

	if (!atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset))
		return state_index;
	power_info = (union power_info *)(mode_info->atom_context->bios + data_offset);

	radeon_atombios_add_pplib_thermal_controller(rdev, &power_info->pplib.sThermalController);
	if (power_info->pplib.ucNumStates == 0)
		return state_index;
	rdev->pm.power_state = kzalloc(sizeof(struct radeon_power_state) *
				       power_info->pplib.ucNumStates, GFP_KERNEL);
	if (!rdev->pm.power_state)
		return state_index;
	/* first mode is usually default, followed by low to high */
	for (i = 0; i < power_info->pplib.ucNumStates; i++) {
		mode_index = 0;
		power_state = (union pplib_power_state *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(power_info->pplib.usStateArrayOffset) +
			 i * power_info->pplib.ucStateEntrySize);
		non_clock_info = (struct _ATOM_PPLIB_NONCLOCK_INFO *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(power_info->pplib.usNonClockInfoArrayOffset) +
			 (power_state->v1.ucNonClockStateIndex *
			  power_info->pplib.ucNonClockSize));
		rdev->pm.power_state[i].clock_info = kzalloc(sizeof(struct radeon_pm_clock_info) *
							     ((power_info->pplib.ucStateEntrySize - 1) ?
							      (power_info->pplib.ucStateEntrySize - 1) : 1),
							     GFP_KERNEL);
		if (!rdev->pm.power_state[i].clock_info)
			return state_index;
		if (power_info->pplib.ucStateEntrySize - 1) {
			for (j = 0; j < (power_info->pplib.ucStateEntrySize - 1); j++) {
				clock_info = (union pplib_clock_info *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(power_info->pplib.usClockInfoArrayOffset) +
					 (power_state->v1.ucClockStateIndices[j] *
					  power_info->pplib.ucClockInfoSize));
				valid = radeon_atombios_parse_pplib_clock_info(rdev,
									       state_index, mode_index,
									       clock_info);
				if (valid)
					mode_index++;
			}
		} else {
			rdev->pm.power_state[state_index].clock_info[0].mclk =
				rdev->clock.default_mclk;
			rdev->pm.power_state[state_index].clock_info[0].sclk =
				rdev->clock.default_sclk;
			mode_index++;
		}
		rdev->pm.power_state[state_index].num_clock_modes = mode_index;
		if (mode_index) {
			radeon_atombios_parse_pplib_non_clock_info(rdev, state_index, mode_index,
								   non_clock_info);
			state_index++;
		}
	}
	/* if multiple clock modes, mark the lowest as no display */
	for (i = 0; i < state_index; i++) {
		if (rdev->pm.power_state[i].num_clock_modes > 1)
			rdev->pm.power_state[i].clock_info[0].flags |=
				RADEON_PM_MODE_NO_DISPLAY;
	}
	/* first mode is usually default */
	if (rdev->pm.default_power_state_index == -1) {
		rdev->pm.power_state[0].type =
			POWER_STATE_TYPE_DEFAULT;
		rdev->pm.default_power_state_index = 0;
		rdev->pm.power_state[0].default_clock_mode =
			&rdev->pm.power_state[0].clock_info[0];
	}
	return state_index;
}