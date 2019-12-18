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
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ CPU_regPC ; 
 size_t MEMORY_SafeGetByte (scalar_t__) ; 
 scalar_t__ MONITOR_break_addr ; 
 void* MONITOR_break_step ; 
 int* MONITOR_optype6502 ; 
 void* TRUE ; 
 void* break_over ; 

__attribute__((used)) static void step_over(void)
{
	UBYTE opcode = MEMORY_SafeGetByte(CPU_regPC);
	if ((opcode & 0x1f) == 0x10 || opcode == 0x20) {
		/* branch or JSR: set breakpoint after it */
		MONITOR_break_addr = CPU_regPC + (MONITOR_optype6502[MEMORY_SafeGetByte(CPU_regPC)] & 0x3);
		break_over = TRUE;
	}
	else
		MONITOR_break_step = TRUE;
}