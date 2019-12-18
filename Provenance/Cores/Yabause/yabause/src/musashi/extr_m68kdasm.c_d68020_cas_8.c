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
 int /*<<< orphan*/  g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 char* get_ea_mode_str_8 (int /*<<< orphan*/ ) ; 
 int read_imm_16 () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,char*) ; 

__attribute__((used)) static void d68020_cas_8(void)
{
	uint extension;
	LIMIT_CPU_TYPES(M68020_PLUS);
	extension = read_imm_16();
	sprintf(g_dasm_str, "cas.b   D%d, D%d, %s; (2+)", extension&7, (extension>>6)&7, get_ea_mode_str_8(g_cpu_ir));
}