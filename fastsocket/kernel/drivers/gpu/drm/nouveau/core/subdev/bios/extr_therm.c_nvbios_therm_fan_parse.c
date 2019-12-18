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
typedef  int uint8_t ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct nvbios_therm_fan {size_t nr_fan_trip; int min_duty; int max_duty; int pwm_freq; int bump_period; int slow_down_period; int linear_min_temp; int linear_max_temp; struct nouveau_therm_trip_point* trip; } ;
struct nouveau_therm_trip_point {int hysteresis; int temp; int fan_duty; } ;
struct nouveau_bios {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int nv_ro16 (struct nouveau_bios*,scalar_t__) ; 
 scalar_t__ nvbios_therm_entry (struct nouveau_bios*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

int
nvbios_therm_fan_parse(struct nouveau_bios *bios,
			  struct nvbios_therm_fan *fan)
{
	struct nouveau_therm_trip_point *cur_trip = NULL;
	u8 ver, len, i;
	u16 entry;

	uint8_t duty_lut[] = { 0, 0, 25, 0, 40, 0, 50, 0,
				75, 0, 85, 0, 100, 0, 100, 0 };

	i = 0;
	fan->nr_fan_trip = 0;
	while ((entry = nvbios_therm_entry(bios, i++, &ver, &len))) {
		s16 value = nv_ro16(bios, entry + 1);

		switch (nv_ro08(bios, entry + 0)) {
		case 0x22:
			fan->min_duty = value & 0xff;
			fan->max_duty = (value & 0xff00) >> 8;
			break;
		case 0x24:
			fan->nr_fan_trip++;
			cur_trip = &fan->trip[fan->nr_fan_trip - 1];
			cur_trip->hysteresis = value & 0xf;
			cur_trip->temp = (value & 0xff0) >> 4;
			cur_trip->fan_duty = duty_lut[(value & 0xf000) >> 12];
			break;
		case 0x25:
			cur_trip = &fan->trip[fan->nr_fan_trip - 1];
			cur_trip->fan_duty = value;
			break;
		case 0x26:
			fan->pwm_freq = value;
			break;
		case 0x3b:
			fan->bump_period = value;
			break;
		case 0x3c:
			fan->slow_down_period = value;
			break;
		case 0x46:
			fan->linear_min_temp = nv_ro08(bios, entry + 1);
			fan->linear_max_temp = nv_ro08(bios, entry + 2);
			break;
		}
	}

	return 0;
}