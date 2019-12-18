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
typedef  int u32 ;
struct nouveau_therm {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  nv_error (struct nouveau_therm*,char*,int) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_therm*,int,int,int) ; 

__attribute__((used)) static int
nv40_fan_pwm_ctrl(struct nouveau_therm *therm, int line, bool enable)
{
	u32 mask = enable ? 0x80000000 : 0x0000000;
	if      (line == 2) nv_mask(therm, 0x0010f0, 0x80000000, mask);
	else if (line == 9) nv_mask(therm, 0x0015f4, 0x80000000, mask);
	else {
		nv_error(therm, "unknown pwm ctrl for gpio %d\n", line);
		return -ENODEV;
	}
	return 0;
}