#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int reg; unsigned short valmask; unsigned short val; } ;
typedef  TYPE_1__ reg_setting ;

/* Variables and functions */
 unsigned short* memregs ; 

__attribute__((used)) static void get_reg_setting(reg_setting *set)
{
	for (; set->reg; set++)
	{
		unsigned short val = memregs[set->reg >> 1];
		val &= set->valmask;
		set->val = val;
	}
}