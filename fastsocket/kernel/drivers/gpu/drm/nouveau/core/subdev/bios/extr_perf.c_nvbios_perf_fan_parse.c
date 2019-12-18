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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct nvbios_perf_fan {int /*<<< orphan*/  pwm_divisor; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  nv_ro16 (struct nouveau_bios*,scalar_t__) ; 
 scalar_t__ perf_table (struct nouveau_bios*,int*,int*,int*,int*) ; 

int
nvbios_perf_fan_parse(struct nouveau_bios *bios,
		      struct nvbios_perf_fan *fan)
{
	u8 ver = 0, hdr = 0, cnt = 0, len = 0;
	u16 perf = perf_table(bios, &ver, &hdr, &cnt, &len);
	if (!perf)
		return -ENODEV;

	if (ver >= 0x20 && ver < 0x40 && hdr > 6)
		fan->pwm_divisor = nv_ro16(bios, perf + 6);
	else
		fan->pwm_divisor = 0;

	return 0;
}