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

/* Variables and functions */
 int CPU_REMEMBER_JMP_STEPS ; 
 int /*<<< orphan*/ * CPU_remember_JMP ; 
 int CPU_remember_jmp_curpos ; 
 int /*<<< orphan*/  show_instruction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void show_last_jumps(void)
{
	int i;
	for (i = 0; i < CPU_REMEMBER_JMP_STEPS; i++)
		show_instruction(stdout, CPU_remember_JMP[(CPU_remember_jmp_curpos + i) % CPU_REMEMBER_JMP_STEPS]);
}