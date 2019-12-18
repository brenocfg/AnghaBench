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
typedef  int uint_t ;

/* Variables and functions */
 int VEX_B ; 
 int VEX_R ; 

__attribute__((used)) static void
dtrace_vex_adjust(uint_t vex_byte1, uint_t mode, uint_t *reg, uint_t *r_m)
{
#pragma unused (mode)
	if (reg != NULL && r_m == NULL) {
		if (!(vex_byte1 & VEX_B))
			*reg += 8;
	} else {
		if (reg != NULL && ((VEX_R & vex_byte1) == 0))
			*reg += 8;
		if (r_m != NULL && ((VEX_B & vex_byte1) == 0))
			*r_m += 8;
	}
}