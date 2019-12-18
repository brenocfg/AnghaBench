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
 int /*<<< orphan*/  M68040_PLUS ; 
 int g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void d68040_cpush(void)
{
	LIMIT_CPU_TYPES(M68040_PLUS);
	switch((g_cpu_ir>>3)&3)
	{
		case 0:
			sprintf(g_dasm_str, "cpush (illegal scope); (4)");
			break;
		case 1:
			sprintf(g_dasm_str, "cpushl  %d, (A%d); (4)", (g_cpu_ir>>6)&3, g_cpu_ir&7);
			break;
		case 2:
			sprintf(g_dasm_str, "cpushp  %d, (A%d); (4)", (g_cpu_ir>>6)&3, g_cpu_ir&7);
			break;
		case 3:
			sprintf(g_dasm_str, "cpusha  %d; (4)", (g_cpu_ir>>6)&3);
			break;
	}
}