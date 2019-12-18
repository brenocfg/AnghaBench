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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {int temp; int hysteresis; } ;
struct TYPE_7__ {int temp; int hysteresis; } ;
struct TYPE_6__ {int temp; int hysteresis; } ;
struct TYPE_5__ {int temp; int hysteresis; } ;
struct nvbios_therm_sensor {int offset_constant; int offset_num; int offset_den; int slope_mult; int slope_div; TYPE_4__ thrs_shutdown; TYPE_3__ thrs_fan_boost; TYPE_2__ thrs_down_clock; TYPE_1__ thrs_critical; } ;
struct nouveau_bios {int dummy; } ;
typedef  int s8 ;
typedef  int s16 ;
typedef  enum nvbios_therm_domain { ____Placeholder_nvbios_therm_domain } nvbios_therm_domain ;

/* Variables and functions */
 int EINVAL ; 
 int NVBIOS_THERM_DOMAIN_CORE ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int nv_ro16 (struct nouveau_bios*,scalar_t__) ; 
 scalar_t__ nvbios_therm_entry (struct nouveau_bios*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

int
nvbios_therm_sensor_parse(struct nouveau_bios *bios,
			  enum nvbios_therm_domain domain,
			  struct nvbios_therm_sensor *sensor)
{
	s8 thrs_section, sensor_section, offset;
	u8 ver, len, i;
	u16 entry;

	/* we only support the core domain for now */
	if (domain != NVBIOS_THERM_DOMAIN_CORE)
		return -EINVAL;

	/* Read the entries from the table */
	thrs_section = 0;
	sensor_section = -1;
	i = 0;
	while ((entry = nvbios_therm_entry(bios, i++, &ver, &len))) {
		s16 value = nv_ro16(bios, entry + 1);

		switch (nv_ro08(bios, entry + 0)) {
		case 0x0:
			thrs_section = value;
			if (value > 0)
				return 0; /* we do not try to support ambient */
			break;
		case 0x01:
			sensor_section++;
			if (sensor_section == 0) {
				offset = ((s8) nv_ro08(bios, entry + 2)) / 2;
				sensor->offset_constant = offset;
			}
			break;

		case 0x04:
			if (thrs_section == 0) {
				sensor->thrs_critical.temp = (value & 0xff0) >> 4;
				sensor->thrs_critical.hysteresis = value & 0xf;
			}
			break;

		case 0x07:
			if (thrs_section == 0) {
				sensor->thrs_down_clock.temp = (value & 0xff0) >> 4;
				sensor->thrs_down_clock.hysteresis = value & 0xf;
			}
			break;

		case 0x08:
			if (thrs_section == 0) {
				sensor->thrs_fan_boost.temp = (value & 0xff0) >> 4;
				sensor->thrs_fan_boost.hysteresis = value & 0xf;
			}
			break;

		case 0x10:
			if (sensor_section == 0)
				sensor->offset_num = value;
			break;

		case 0x11:
			if (sensor_section == 0)
				sensor->offset_den = value;
			break;

		case 0x12:
			if (sensor_section == 0)
				sensor->slope_mult = value;
			break;

		case 0x13:
			if (sensor_section == 0)
				sensor->slope_div = value;
			break;
		case 0x32:
			if (thrs_section == 0) {
				sensor->thrs_shutdown.temp = (value & 0xff0) >> 4;
				sensor->thrs_shutdown.hysteresis = value & 0xf;
			}
			break;
		}
	}

	return 0;
}