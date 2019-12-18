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
 int /*<<< orphan*/  nv_wr32 (struct nouveau_therm*,int,int) ; 
 int pwm_info (struct nouveau_therm*,int*,int*,int*) ; 

int
nv50_fan_pwm_set(struct nouveau_therm *therm, int line, u32 divs, u32 duty)
{
	int ctrl, id, ret = pwm_info(therm, &line, &ctrl, &id);
	if (ret)
		return ret;

	nv_wr32(therm, 0x00e114 + (id * 8), divs);
	nv_wr32(therm, 0x00e118 + (id * 8), duty | 0x80000000);
	return 0;
}