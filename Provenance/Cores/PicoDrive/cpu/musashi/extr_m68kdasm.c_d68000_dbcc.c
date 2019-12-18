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
typedef  int uint ;

/* Variables and functions */
 int /*<<< orphan*/  DASMFLAG_STEP_OVER ; 
 int /*<<< orphan*/  SET_OPCODE_FLAGS (int /*<<< orphan*/ ) ; 
 char** g_cc ; 
 int g_cpu_ir ; 
 int g_cpu_pc ; 
 int /*<<< orphan*/  g_dasm_str ; 
 int make_int_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_imm_16 () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 

__attribute__((used)) static void d68000_dbcc(void)
{
	uint temp_pc = g_cpu_pc;
	sprintf(g_dasm_str, "db%-2s    D%d, $%x", g_cc[(g_cpu_ir>>8)&0xf], g_cpu_ir & 7, temp_pc + make_int_16(read_imm_16()));
	SET_OPCODE_FLAGS(DASMFLAG_STEP_OVER);
}