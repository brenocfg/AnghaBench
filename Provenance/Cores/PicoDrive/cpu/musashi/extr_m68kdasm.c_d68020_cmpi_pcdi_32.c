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
 int /*<<< orphan*/  LIMIT_CPU_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68010_PLUS ; 
 int /*<<< orphan*/  g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 char* get_ea_mode_str_32 (int /*<<< orphan*/ ) ; 
 char* get_imm_str_s32 () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static void d68020_cmpi_pcdi_32(void)
{
	char* str;
	LIMIT_CPU_TYPES(M68010_PLUS);
	str = get_imm_str_s32();
	sprintf(g_dasm_str, "cmpi.l  %s, %s; (2+)", str, get_ea_mode_str_32(g_cpu_ir));
}