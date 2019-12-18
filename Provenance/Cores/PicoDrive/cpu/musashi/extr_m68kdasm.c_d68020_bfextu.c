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
 scalar_t__ BIT_5 (int) ; 
 scalar_t__ BIT_B (int) ; 
 int /*<<< orphan*/  LIMIT_CPU_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 int* g_5bit_data_table ; 
 int /*<<< orphan*/  g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 char* get_ea_mode_str_8 (int /*<<< orphan*/ ) ; 
 int read_imm_16 () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static void d68020_bfextu(void)
{
	uint extension;
	char offset[3];
	char width[3];

	LIMIT_CPU_TYPES(M68020_PLUS);

	extension = read_imm_16();

	if(BIT_B(extension))
		sprintf(offset, "D%d", (extension>>6)&7);
	else
		sprintf(offset, "%d", (extension>>6)&31);
	if(BIT_5(extension))
		sprintf(width, "D%d", extension&7);
	else
		sprintf(width, "%d", g_5bit_data_table[extension&31]);
	sprintf(g_dasm_str, "bfextu  D%d, %s {%s:%s}; (2+)", (extension>>12)&7, get_ea_mode_str_8(g_cpu_ir), offset, width);
}