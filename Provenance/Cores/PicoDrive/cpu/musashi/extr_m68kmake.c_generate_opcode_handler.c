#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  replace_struct ;
typedef  int /*<<< orphan*/  opcode_struct ;
typedef  int /*<<< orphan*/  body_struct ;
struct TYPE_2__ {char* ea_add; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EA_MODE_NONE ; 
 int /*<<< orphan*/  ID_OPHANDLER_EA_AY_16 ; 
 int /*<<< orphan*/  ID_OPHANDLER_EA_AY_32 ; 
 int /*<<< orphan*/  ID_OPHANDLER_EA_AY_8 ; 
 int /*<<< orphan*/  ID_OPHANDLER_OPER_AY_16 ; 
 int /*<<< orphan*/  ID_OPHANDLER_OPER_AY_32 ; 
 int /*<<< orphan*/  ID_OPHANDLER_OPER_AY_8 ; 
 int /*<<< orphan*/  MAX_LINE_LENGTH ; 
 int /*<<< orphan*/  add_opcode_output_table_entry (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  add_replace_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* g_ea_info_table ; 
 int /*<<< orphan*/  g_num_functions ; 
 int /*<<< orphan*/  g_prototype_file ; 
 int /*<<< orphan*/  get_base_name (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  set_opcode_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  write_body (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_function_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  write_prototype (int /*<<< orphan*/ ,char*) ; 

void generate_opcode_handler(FILE* filep, body_struct* body, replace_struct* replace, opcode_struct* opinfo, int ea_mode)
{
	char str[MAX_LINE_LENGTH+1];
	opcode_struct* op = malloc(sizeof(opcode_struct));

	/* Set the opcode structure and write the tables, prototypes, etc */
	set_opcode_struct(opinfo, op, ea_mode);
	get_base_name(str, op);
	write_prototype(g_prototype_file, str);
	add_opcode_output_table_entry(op, str);
	write_function_name(filep, str);

	/* Add any replace strings needed */
	if(ea_mode != EA_MODE_NONE)
	{
		sprintf(str, "EA_%s_8()", g_ea_info_table[ea_mode].ea_add);
		add_replace_string(replace, ID_OPHANDLER_EA_AY_8, str);
		sprintf(str, "EA_%s_16()", g_ea_info_table[ea_mode].ea_add);
		add_replace_string(replace, ID_OPHANDLER_EA_AY_16, str);
		sprintf(str, "EA_%s_32()", g_ea_info_table[ea_mode].ea_add);
		add_replace_string(replace, ID_OPHANDLER_EA_AY_32, str);
		sprintf(str, "OPER_%s_8()", g_ea_info_table[ea_mode].ea_add);
		add_replace_string(replace, ID_OPHANDLER_OPER_AY_8, str);
		sprintf(str, "OPER_%s_16()", g_ea_info_table[ea_mode].ea_add);
		add_replace_string(replace, ID_OPHANDLER_OPER_AY_16, str);
		sprintf(str, "OPER_%s_32()", g_ea_info_table[ea_mode].ea_add);
		add_replace_string(replace, ID_OPHANDLER_OPER_AY_32, str);
	}

	/* Now write the function body with the selected replace strings */
	write_body(filep, body, replace);
	g_num_functions++;
	free(op);
}