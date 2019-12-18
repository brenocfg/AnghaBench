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
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ opcode_struct ;

/* Variables and functions */
 TYPE_1__* g_opcode_input_table ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

opcode_struct* find_illegal_opcode(void)
{
	opcode_struct* op;

	for(op = g_opcode_input_table;op->name != NULL;op++)
	{
		if(strcmp(op->name, "illegal") == 0)
			return op;
	}
	return NULL;
}