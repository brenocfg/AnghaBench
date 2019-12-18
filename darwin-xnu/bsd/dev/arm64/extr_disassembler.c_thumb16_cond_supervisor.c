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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int BITS (int /*<<< orphan*/ ,int,int) ; 
 int FASTTRAP_T_B_COND ; 
 int FASTTRAP_T_INV ; 

__attribute__((used)) static
int thumb16_cond_supervisor(uint16_t instr)
{
	int opcode = BITS(instr,8,0xF);

	if ((opcode & 0xE) != 0xE)
		return FASTTRAP_T_B_COND;

	return FASTTRAP_T_INV;
}