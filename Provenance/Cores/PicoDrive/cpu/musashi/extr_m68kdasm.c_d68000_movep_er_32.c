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
 int read_imm_16 () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static void d68000_movep_er_32(void)
{
	sprintf(g_dasm_str, "movep.l ($%x,A%d), D%d", read_imm_16(), g_cpu_ir&7, (g_cpu_ir>>9)&7);
}