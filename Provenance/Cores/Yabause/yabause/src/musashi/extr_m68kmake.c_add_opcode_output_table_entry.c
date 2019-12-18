#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  op_mask; int /*<<< orphan*/  bits; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ opcode_struct ;

/* Variables and functions */
 scalar_t__ MAX_OPCODE_OUTPUT_TABLE_LENGTH ; 
 int /*<<< orphan*/  error_exit (char*) ; 
 TYPE_1__* g_opcode_output_table ; 
 scalar_t__ g_opcode_output_table_length ; 
 int /*<<< orphan*/  num_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void add_opcode_output_table_entry(opcode_struct* op, char* name)
{
	opcode_struct* ptr;
	if(g_opcode_output_table_length > MAX_OPCODE_OUTPUT_TABLE_LENGTH)
		error_exit("Opcode output table overflow");

	ptr = g_opcode_output_table + g_opcode_output_table_length++;

	*ptr = *op;
	strcpy(ptr->name, name);
	ptr->bits = num_bits(ptr->op_mask);
}