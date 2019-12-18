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
 int /*<<< orphan*/  DASMFLAG_STEP_OVER ; 
 int /*<<< orphan*/  SET_OPCODE_FLAGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 char* get_ea_mode_str_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void d68000_jsr(void)
{
	sprintf(g_dasm_str, "jsr     %s", get_ea_mode_str_32(g_cpu_ir));
	SET_OPCODE_FLAGS(DASMFLAG_STEP_OVER);
}