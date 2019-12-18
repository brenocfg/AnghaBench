#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t size; char* cpus; int* cycles; int /*<<< orphan*/  name; int /*<<< orphan*/  spec_proc; } ;
typedef  TYPE_1__ opcode_struct ;

/* Variables and functions */
 int CPU_TYPE_000 ; 
 int CPU_TYPE_010 ; 
 int CPU_TYPE_020 ; 
 int EA_MODE_I ; 
 int** g_clr_cycle_table ; 
 int*** g_ea_cycle_table ; 
 int* g_jmp_cycle_table ; 
 int* g_jsr_cycle_table ; 
 int* g_lea_cycle_table ; 
 int** g_moves_cycle_table ; 
 int* g_pea_cycle_table ; 
 int* g_size_select_table ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int get_oper_cycles(opcode_struct* op, int ea_mode, int cpu_type)
{
	int size = g_size_select_table[op->size];

	if(op->cpus[cpu_type] == '.')
		return 0;

	if(cpu_type < CPU_TYPE_020)
	{
		if(cpu_type == CPU_TYPE_010)
		{
			if(strcmp(op->name, "moves") == 0)
				return op->cycles[cpu_type] + g_moves_cycle_table[ea_mode][size];
			if(strcmp(op->name, "clr") == 0)
				return op->cycles[cpu_type] + g_clr_cycle_table[ea_mode][size];
		}

		/* ASG: added these cases -- immediate modes take 2 extra cycles here */
		if(cpu_type == CPU_TYPE_000 && ea_mode == EA_MODE_I &&
		   ((strcmp(op->name, "add") == 0 && strcmp(op->spec_proc, "er") == 0) ||
			strcmp(op->name, "adda")   == 0                                    ||
			(strcmp(op->name, "and") == 0 && strcmp(op->spec_proc, "er") == 0) ||
			(strcmp(op->name, "or") == 0 && strcmp(op->spec_proc, "er") == 0)  ||
			(strcmp(op->name, "sub") == 0 && strcmp(op->spec_proc, "er") == 0) ||
			strcmp(op->name, "suba")   == 0))
			return op->cycles[cpu_type] + g_ea_cycle_table[ea_mode][cpu_type][size] + 2;

		if(strcmp(op->name, "jmp") == 0)
			return op->cycles[cpu_type] + g_jmp_cycle_table[ea_mode];
		if(strcmp(op->name, "jsr") == 0)
			return op->cycles[cpu_type] + g_jsr_cycle_table[ea_mode];
		if(strcmp(op->name, "lea") == 0)
			return op->cycles[cpu_type] + g_lea_cycle_table[ea_mode];
		if(strcmp(op->name, "pea") == 0)
			return op->cycles[cpu_type] + g_pea_cycle_table[ea_mode];
	}
	return op->cycles[cpu_type] + g_ea_cycle_table[ea_mode][cpu_type][size];
}