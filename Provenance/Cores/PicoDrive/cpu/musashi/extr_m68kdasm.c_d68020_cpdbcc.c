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
 int /*<<< orphan*/  LIMIT_CPU_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 char** g_cpcc ; 
 int g_cpu_ir ; 
 int g_cpu_pc ; 
 int /*<<< orphan*/  g_dasm_str ; 
 char* get_imm_str_s16 () ; 
 scalar_t__ make_int_16 (int) ; 
 int read_imm_16 () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,char*,int,char*,int,int) ; 

__attribute__((used)) static void d68020_cpdbcc(void)
{
	uint extension1;
	uint extension2;
	uint new_pc = g_cpu_pc;
	LIMIT_CPU_TYPES(M68020_PLUS);
	extension1 = read_imm_16();
	extension2 = read_imm_16();
	new_pc += make_int_16(read_imm_16());
	sprintf(g_dasm_str, "%ddb%-4s D%d,%s; %x (extension = %x) (2-3)", (g_cpu_ir>>9)&7, g_cpcc[extension1&0x3f], g_cpu_ir&7, get_imm_str_s16(), new_pc, extension2);
}