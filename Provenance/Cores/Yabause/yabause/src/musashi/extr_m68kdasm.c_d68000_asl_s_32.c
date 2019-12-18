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
 int* g_3bit_qdata_table ; 
 int g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void d68000_asl_s_32(void)
{
	sprintf(g_dasm_str, "asl.l   #%d, D%d", g_3bit_qdata_table[(g_cpu_ir>>9)&7], g_cpu_ir&7);
}