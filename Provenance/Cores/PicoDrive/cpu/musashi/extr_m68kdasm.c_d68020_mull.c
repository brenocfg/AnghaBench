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
 scalar_t__ BIT_A (int) ; 
 scalar_t__ BIT_B (int) ; 
 int /*<<< orphan*/  LIMIT_CPU_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 int /*<<< orphan*/  g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 char* get_ea_mode_str_32 (int /*<<< orphan*/ ) ; 
 int read_imm_16 () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char,char*,int,...) ; 

__attribute__((used)) static void d68020_mull(void)
{
	uint extension;
	LIMIT_CPU_TYPES(M68020_PLUS);
	extension = read_imm_16();

	if(BIT_A(extension))
		sprintf(g_dasm_str, "mul%c.l %s, D%d-D%d; (2+)", BIT_B(extension) ? 's' : 'u', get_ea_mode_str_32(g_cpu_ir), extension&7, (extension>>12)&7);
	else
		sprintf(g_dasm_str, "mul%c.l  %s, D%d; (2+)", BIT_B(extension) ? 's' : 'u', get_ea_mode_str_32(g_cpu_ir), (extension>>12)&7);
}