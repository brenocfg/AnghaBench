#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int length; } ;
typedef  TYPE_1__ replace_struct ;
struct TYPE_11__ {int op_mask; int op_match; scalar_t__ name; } ;
typedef  TYPE_2__ opcode_struct ;
typedef  int /*<<< orphan*/  body_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ID_OPHANDLER_CC ; 
 int /*<<< orphan*/  ID_OPHANDLER_NOT_CC ; 
 int /*<<< orphan*/  add_replace_string (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 char*** g_cc_table ; 
 int /*<<< orphan*/  generate_opcode_ea_variants (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 

void generate_opcode_cc_variants(FILE* filep, body_struct* body, replace_struct* replace, opcode_struct* op_in, int offset)
{
	char repl[20];
	char replnot[20];
	int i;
	int old_length = replace->length;
	opcode_struct* op = malloc(sizeof(opcode_struct));

	*op = *op_in;

	op->op_mask |= 0x0f00;

	/* Do all condition codes except t and f */
	for(i=2;i<16;i++)
	{
		/* Add replace strings for this condition code */
		sprintf(repl, "COND_%s()", g_cc_table[i][1]);
		sprintf(replnot, "COND_NOT_%s()", g_cc_table[i][1]);

		add_replace_string(replace, ID_OPHANDLER_CC, repl);
		add_replace_string(replace, ID_OPHANDLER_NOT_CC, replnot);

		/* Set the new opcode info */
		strcpy(op->name+offset, g_cc_table[i][0]);

		op->op_match = (op->op_match & 0xf0ff) | (i<<8);

		/* Generate all opcode variants for this modified opcode */
		generate_opcode_ea_variants(filep, body, replace, op);
		/* Remove the above replace strings */
		replace->length = old_length;
	}
	free(op);
}