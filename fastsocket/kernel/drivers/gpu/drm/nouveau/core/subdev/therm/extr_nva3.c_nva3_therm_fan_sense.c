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
 int nv_rd32 (struct nouveau_therm*,int) ; 

int
nva3_therm_fan_sense(struct nouveau_therm *therm)
{
	u32 tach = nv_rd32(therm, 0x00e728) & 0x0000ffff;
	u32 ctrl = nv_rd32(therm, 0x00e720);
	if (ctrl & 0x00000001)
		return tach * 60;
	return -ENODEV;
}