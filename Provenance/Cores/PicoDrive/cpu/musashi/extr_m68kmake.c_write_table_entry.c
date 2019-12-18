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
struct TYPE_3__ {char* name; int op_mask; int op_match; int* cycles; } ;
typedef  TYPE_1__ opcode_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NUM_CPUS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void write_table_entry(FILE* filep, opcode_struct* op)
{
	int i;

	fprintf(filep, "\t{%-28s, 0x%04x, 0x%04x, {",
		op->name, op->op_mask, op->op_match);

	for(i=0;i<NUM_CPUS;i++)
	{
		fprintf(filep, "%3d", op->cycles[i]);
		if(i < NUM_CPUS-1)
			fprintf(filep, ", ");
	}

	fprintf(filep, "}},\n");
}