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
typedef  scalar_t__ UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int CPU_REMEMBER_PC_STEPS ; 
 scalar_t__* CPU_remember_PC ; 
 int CPU_remember_PC_curpos ; 
 int /*<<< orphan*/ ** CPU_remember_op ; 
 int* CPU_remember_xpos ; 
 int /*<<< orphan*/  MEMORY_SafeGetByte (scalar_t__) ; 
 int /*<<< orphan*/  MEMORY_dPutByte (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  show_instruction (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void show_history(void)
{
	int i;
	for (i = 0; i < CPU_REMEMBER_PC_STEPS; i++) {
		int j;
		int k;
		UWORD saved_cpu = CPU_remember_PC[(CPU_remember_PC_curpos + i) % CPU_REMEMBER_PC_STEPS];
		UBYTE save_op[3];
		j = CPU_remember_xpos[(CPU_remember_PC_curpos + i) % CPU_REMEMBER_PC_STEPS];
		printf("%3d %3d ", j >> 8, j & 0xff);
		for (k = 0; k < 3; k++) {
			save_op[k] = MEMORY_SafeGetByte(saved_cpu + k);
			MEMORY_dPutByte(saved_cpu + k, CPU_remember_op[(CPU_remember_PC_curpos + i) % CPU_REMEMBER_PC_STEPS][k]);
		}
		show_instruction(stdout, CPU_remember_PC[(CPU_remember_PC_curpos + i) % CPU_REMEMBER_PC_STEPS]);
		for (k = 0; k < 3; k++) {
			MEMORY_dPutByte(saved_cpu + k, save_op[k]);
		}
	}
}