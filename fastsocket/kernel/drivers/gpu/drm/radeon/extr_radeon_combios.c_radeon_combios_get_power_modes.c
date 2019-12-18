#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct radeon_power_state {int dummy; } ;
struct radeon_pm_clock_info {int dummy; } ;
struct radeon_i2c_bus_rec {int valid; int hw_capable; int mm_i2c; int i2c_id; } ;
struct TYPE_16__ {int default_power_state_index; int num_power_states; int current_power_state_index; scalar_t__ current_clock_mode_index; TYPE_7__* power_state; TYPE_2__* i2c_bus; } ;
struct TYPE_12__ {scalar_t__ default_mclk; scalar_t__ default_sclk; } ;
struct radeon_device {int flags; TYPE_8__ pm; TYPE_4__ clock; struct drm_device* ddev; } ;
struct i2c_board_info {int addr; int /*<<< orphan*/  type; } ;
struct drm_device {TYPE_1__* pdev; } ;
struct TYPE_15__ {int num_clock_modes; int misc; int misc2; int pcie_lanes; scalar_t__ flags; TYPE_6__* clock_info; TYPE_6__* default_clock_mode; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int valid; int reg; int mask; } ;
struct TYPE_13__ {int active_high; int delay; void* type; TYPE_3__ gpio; } ;
struct TYPE_14__ {scalar_t__ mclk; scalar_t__ sclk; TYPE_5__ voltage; } ;
struct TYPE_10__ {int /*<<< orphan*/  adapter; } ;
struct TYPE_9__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBIOS_OVERDRIVE_INFO_TABLE ; 
 int /*<<< orphan*/  COMBIOS_POWERPLAY_INFO_TABLE ; 
 int DDC_GPIO ; 
 int DDC_LCD ; 
 int DDC_MONID ; 
 int /*<<< orphan*/  DRM_INFO (char*,char const*,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_BATTERY ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_DEFAULT ; 
 int RADEON_IS_MOBILITY ; 
 scalar_t__ RADEON_PM_STATE_SINGLE_DISPLAY_ONLY ; 
 int RBIOS16 (int) ; 
 void* RBIOS32 (int) ; 
 int RBIOS8 (int) ; 
 void* VOLTAGE_GPIO ; 
 void* VOLTAGE_NONE ; 
 int combios_get_table_offset (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct radeon_i2c_bus_rec combios_setup_i2c_bus (struct radeon_device*,int,int,int) ; 
 int /*<<< orphan*/  i2c_new_device (int /*<<< orphan*/ *,struct i2c_board_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* radeon_i2c_lookup (struct radeon_device*,struct radeon_i2c_bus_rec*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 char const** thermal_controller_names ; 

void radeon_combios_get_power_modes(struct radeon_device *rdev)
{
	struct drm_device *dev = rdev->ddev;
	u16 offset, misc, misc2 = 0;
	u8 rev, blocks, tmp;
	int state_index = 0;
	struct radeon_i2c_bus_rec i2c_bus;

	rdev->pm.default_power_state_index = -1;

	/* allocate 2 power states */
	rdev->pm.power_state = kzalloc(sizeof(struct radeon_power_state) * 2, GFP_KERNEL);
	if (rdev->pm.power_state) {
		/* allocate 1 clock mode per state */
		rdev->pm.power_state[0].clock_info =
			kzalloc(sizeof(struct radeon_pm_clock_info) * 1, GFP_KERNEL);
		rdev->pm.power_state[1].clock_info =
			kzalloc(sizeof(struct radeon_pm_clock_info) * 1, GFP_KERNEL);
		if (!rdev->pm.power_state[0].clock_info ||
		    !rdev->pm.power_state[1].clock_info)
			goto pm_failed;
	} else
		goto pm_failed;

	/* check for a thermal chip */
	offset = combios_get_table_offset(dev, COMBIOS_OVERDRIVE_INFO_TABLE);
	if (offset) {
		u8 thermal_controller = 0, gpio = 0, i2c_addr = 0, clk_bit = 0, data_bit = 0;

		rev = RBIOS8(offset);

		if (rev == 0) {
			thermal_controller = RBIOS8(offset + 3);
			gpio = RBIOS8(offset + 4) & 0x3f;
			i2c_addr = RBIOS8(offset + 5);
		} else if (rev == 1) {
			thermal_controller = RBIOS8(offset + 4);
			gpio = RBIOS8(offset + 5) & 0x3f;
			i2c_addr = RBIOS8(offset + 6);
		} else if (rev == 2) {
			thermal_controller = RBIOS8(offset + 4);
			gpio = RBIOS8(offset + 5) & 0x3f;
			i2c_addr = RBIOS8(offset + 6);
			clk_bit = RBIOS8(offset + 0xa);
			data_bit = RBIOS8(offset + 0xb);
		}
		if ((thermal_controller > 0) && (thermal_controller < 3)) {
			DRM_INFO("Possible %s thermal controller at 0x%02x\n",
				 thermal_controller_names[thermal_controller],
				 i2c_addr >> 1);
			if (gpio == DDC_LCD) {
				/* MM i2c */
				i2c_bus.valid = true;
				i2c_bus.hw_capable = true;
				i2c_bus.mm_i2c = true;
				i2c_bus.i2c_id = 0xa0;
			} else if (gpio == DDC_GPIO)
				i2c_bus = combios_setup_i2c_bus(rdev, gpio, 1 << clk_bit, 1 << data_bit);
			else
				i2c_bus = combios_setup_i2c_bus(rdev, gpio, 0, 0);
			rdev->pm.i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);
			if (rdev->pm.i2c_bus) {
				struct i2c_board_info info = { };
				const char *name = thermal_controller_names[thermal_controller];
				info.addr = i2c_addr >> 1;
				strlcpy(info.type, name, sizeof(info.type));
				i2c_new_device(&rdev->pm.i2c_bus->adapter, &info);
			}
		}
	} else {
		/* boards with a thermal chip, but no overdrive table */

		/* Asus 9600xt has an f75375 on the monid bus */
		if ((dev->pdev->device == 0x4152) &&
		    (dev->pdev->subsystem_vendor == 0x1043) &&
		    (dev->pdev->subsystem_device == 0xc002)) {
			i2c_bus = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
			rdev->pm.i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);
			if (rdev->pm.i2c_bus) {
				struct i2c_board_info info = { };
				const char *name = "f75375";
				info.addr = 0x28;
				strlcpy(info.type, name, sizeof(info.type));
				i2c_new_device(&rdev->pm.i2c_bus->adapter, &info);
				DRM_INFO("Possible %s thermal controller at 0x%02x\n",
					 name, info.addr);
			}
		}
	}

	if (rdev->flags & RADEON_IS_MOBILITY) {
		offset = combios_get_table_offset(dev, COMBIOS_POWERPLAY_INFO_TABLE);
		if (offset) {
			rev = RBIOS8(offset);
			blocks = RBIOS8(offset + 0x2);
			/* power mode 0 tends to be the only valid one */
			rdev->pm.power_state[state_index].num_clock_modes = 1;
			rdev->pm.power_state[state_index].clock_info[0].mclk = RBIOS32(offset + 0x5 + 0x2);
			rdev->pm.power_state[state_index].clock_info[0].sclk = RBIOS32(offset + 0x5 + 0x6);
			if ((rdev->pm.power_state[state_index].clock_info[0].mclk == 0) ||
			    (rdev->pm.power_state[state_index].clock_info[0].sclk == 0))
				goto default_mode;
			rdev->pm.power_state[state_index].type =
				POWER_STATE_TYPE_BATTERY;
			misc = RBIOS16(offset + 0x5 + 0x0);
			if (rev > 4)
				misc2 = RBIOS16(offset + 0x5 + 0xe);
			rdev->pm.power_state[state_index].misc = misc;
			rdev->pm.power_state[state_index].misc2 = misc2;
			if (misc & 0x4) {
				rdev->pm.power_state[state_index].clock_info[0].voltage.type = VOLTAGE_GPIO;
				if (misc & 0x8)
					rdev->pm.power_state[state_index].clock_info[0].voltage.active_high =
						true;
				else
					rdev->pm.power_state[state_index].clock_info[0].voltage.active_high =
						false;
				rdev->pm.power_state[state_index].clock_info[0].voltage.gpio.valid = true;
				if (rev < 6) {
					rdev->pm.power_state[state_index].clock_info[0].voltage.gpio.reg =
						RBIOS16(offset + 0x5 + 0xb) * 4;
					tmp = RBIOS8(offset + 0x5 + 0xd);
					rdev->pm.power_state[state_index].clock_info[0].voltage.gpio.mask = (1 << tmp);
				} else {
					u8 entries = RBIOS8(offset + 0x5 + 0xb);
					u16 voltage_table_offset = RBIOS16(offset + 0x5 + 0xc);
					if (entries && voltage_table_offset) {
						rdev->pm.power_state[state_index].clock_info[0].voltage.gpio.reg =
							RBIOS16(voltage_table_offset) * 4;
						tmp = RBIOS8(voltage_table_offset + 0x2);
						rdev->pm.power_state[state_index].clock_info[0].voltage.gpio.mask = (1 << tmp);
					} else
						rdev->pm.power_state[state_index].clock_info[0].voltage.gpio.valid = false;
				}
				switch ((misc2 & 0x700) >> 8) {
				case 0:
				default:
					rdev->pm.power_state[state_index].clock_info[0].voltage.delay = 0;
					break;
				case 1:
					rdev->pm.power_state[state_index].clock_info[0].voltage.delay = 33;
					break;
				case 2:
					rdev->pm.power_state[state_index].clock_info[0].voltage.delay = 66;
					break;
				case 3:
					rdev->pm.power_state[state_index].clock_info[0].voltage.delay = 99;
					break;
				case 4:
					rdev->pm.power_state[state_index].clock_info[0].voltage.delay = 132;
					break;
				}
			} else
				rdev->pm.power_state[state_index].clock_info[0].voltage.type = VOLTAGE_NONE;
			if (rev > 6)
				rdev->pm.power_state[state_index].pcie_lanes =
					RBIOS8(offset + 0x5 + 0x10);
			rdev->pm.power_state[state_index].flags = RADEON_PM_STATE_SINGLE_DISPLAY_ONLY;
			state_index++;
		} else {
			/* XXX figure out some good default low power mode for mobility cards w/out power tables */
		}
	} else {
		/* XXX figure out some good default low power mode for desktop cards */
	}

default_mode:
	/* add the default mode */
	rdev->pm.power_state[state_index].type =
		POWER_STATE_TYPE_DEFAULT;
	rdev->pm.power_state[state_index].num_clock_modes = 1;
	rdev->pm.power_state[state_index].clock_info[0].mclk = rdev->clock.default_mclk;
	rdev->pm.power_state[state_index].clock_info[0].sclk = rdev->clock.default_sclk;
	rdev->pm.power_state[state_index].default_clock_mode = &rdev->pm.power_state[state_index].clock_info[0];
	if ((state_index > 0) &&
	    (rdev->pm.power_state[0].clock_info[0].voltage.type == VOLTAGE_GPIO))
		rdev->pm.power_state[state_index].clock_info[0].voltage =
			rdev->pm.power_state[0].clock_info[0].voltage;
	else
		rdev->pm.power_state[state_index].clock_info[0].voltage.type = VOLTAGE_NONE;
	rdev->pm.power_state[state_index].pcie_lanes = 16;
	rdev->pm.power_state[state_index].flags = 0;
	rdev->pm.default_power_state_index = state_index;
	rdev->pm.num_power_states = state_index + 1;

	rdev->pm.current_power_state_index = rdev->pm.default_power_state_index;
	rdev->pm.current_clock_mode_index = 0;
	return;

pm_failed:
	rdev->pm.default_power_state_index = state_index;
	rdev->pm.num_power_states = 0;

	rdev->pm.current_power_state_index = rdev->pm.default_power_state_index;
	rdev->pm.current_clock_mode_index = 0;
}