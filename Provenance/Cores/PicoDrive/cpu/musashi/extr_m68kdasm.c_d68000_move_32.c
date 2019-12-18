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
 int g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 char* get_ea_mode_str_32 (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static void d68000_move_32(void)
{
	char* str = get_ea_mode_str_32(g_cpu_ir);
	sprintf(g_dasm_str, "move.l  %s, %s", str, get_ea_mode_str_32(((g_cpu_ir>>9) & 7) | ((g_cpu_ir>>3) & 0x38)));
}