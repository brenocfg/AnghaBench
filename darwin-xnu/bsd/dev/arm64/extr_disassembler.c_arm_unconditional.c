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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ BITS (int /*<<< orphan*/ ,int,int) ; 
 int FASTTRAP_T_INV ; 
 int arm_unconditional_misc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int arm_unconditional(uint32_t instr)
{
	if (BITS(instr,27,0x1) == 0)
		return arm_unconditional_misc(instr);

	/* The rest are privileged or BL/BLX, do not instrument */

	/* Do not need to instrument BL/BLX either, see comment in arm_misc(uint32_t) */

	return FASTTRAP_T_INV;
}