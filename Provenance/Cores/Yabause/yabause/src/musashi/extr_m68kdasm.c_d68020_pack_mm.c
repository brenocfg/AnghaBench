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
 int /*<<< orphan*/  M68020_PLUS ; 
 int g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 char* get_imm_str_u16 () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,char*) ; 

__attribute__((used)) static void d68020_pack_mm(void)
{
	LIMIT_CPU_TYPES(M68020_PLUS);
	sprintf(g_dasm_str, "pack    -(A%d), -(A%d), %s; (2+)", g_cpu_ir&7, (g_cpu_ir>>9)&7, get_imm_str_u16());
}