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
struct TYPE_3__ {char* name; unsigned char size; char* spec_proc; char* spec_ea; char* ea_allowed; char* cpus; unsigned char* cycles; int op_mask; int op_match; int /*<<< orphan*/ * cpu_mode; } ;
typedef  TYPE_1__ opcode_struct ;

/* Variables and functions */
 int EA_ALLOWED_LENGTH ; 
 int /*<<< orphan*/  ID_INPUT_SEPARATOR ; 
 int /*<<< orphan*/  ID_TABLE_START ; 
 int MAX_LINE_LENGTH ; 
 int MAX_NAME_LENGTH ; 
 int MAX_SPEC_EA_LENGTH ; 
 int MAX_SPEC_PROC_LENGTH ; 
 int NUM_CPUS ; 
 char UNSPECIFIED_CH ; 
 int /*<<< orphan*/  check_atoi (char*,int*) ; 
 int /*<<< orphan*/  check_strsncpy (char*,char*,int) ; 
 int /*<<< orphan*/  error_exit (char*) ; 
 scalar_t__ fgetline (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_input_file ; 
 TYPE_1__* g_opcode_input_table ; 
 int /*<<< orphan*/  skip_spaces (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

void populate_table(void)
{
	char* ptr;
	char bitpattern[17];
	opcode_struct* op;
	char buff[MAX_LINE_LENGTH];
	int i;
	int temp;

	buff[0] = 0;

	/* Find the start of the table */
	while(strcmp(buff, ID_TABLE_START) != 0)
		if(fgetline(buff, MAX_LINE_LENGTH, g_input_file) < 0)
			error_exit("Premature EOF while reading table");

	/* Process the entire table */
	for(op = g_opcode_input_table;;op++)
	{
		if(fgetline(buff, MAX_LINE_LENGTH, g_input_file) < 0)
			error_exit("Premature EOF while reading table");
		if(strlen(buff) == 0)
			continue;
		/* We finish when we find an input separator */
		if(strcmp(buff, ID_INPUT_SEPARATOR) == 0)
			break;

		/* Extract the info from the table */
		ptr = buff;

		/* Name */
		ptr += skip_spaces(ptr);
		ptr += check_strsncpy(op->name, ptr, MAX_NAME_LENGTH);

		/* Size */
		ptr += skip_spaces(ptr);
		ptr += check_atoi(ptr, &temp);
		op->size = (unsigned char)temp;

		/* Special processing */
		ptr += skip_spaces(ptr);
		ptr += check_strsncpy(op->spec_proc, ptr, MAX_SPEC_PROC_LENGTH);

		/* Specified EA Mode */
		ptr += skip_spaces(ptr);
		ptr += check_strsncpy(op->spec_ea, ptr, MAX_SPEC_EA_LENGTH);

		/* Bit Pattern (more processing later) */
		ptr += skip_spaces(ptr);
		ptr += check_strsncpy(bitpattern, ptr, 17);

		/* Allowed Addressing Mode List */
		ptr += skip_spaces(ptr);
		ptr += check_strsncpy(op->ea_allowed, ptr, EA_ALLOWED_LENGTH);

		/* CPU operating mode (U = user or supervisor, S = supervisor only */
		ptr += skip_spaces(ptr);
		for(i=0;i<NUM_CPUS;i++)
		{
			op->cpu_mode[i] = *ptr++;
			ptr += skip_spaces(ptr);
		}

		/* Allowed CPUs for this instruction */
		for(i=0;i<NUM_CPUS;i++)
		{
			ptr += skip_spaces(ptr);
			if(*ptr == UNSPECIFIED_CH)
			{
				op->cpus[i] = UNSPECIFIED_CH;
				op->cycles[i] = 0;
				ptr++;
			}
			else
			{
				op->cpus[i] = '0' + i;
				ptr += check_atoi(ptr, &temp);
				op->cycles[i] = (unsigned char)temp;
			}
		}

		/* generate mask and match from bitpattern */
		op->op_mask = 0;
		op->op_match = 0;
		for(i=0;i<16;i++)
		{
			op->op_mask |= (bitpattern[i] != '.') << (15-i);
			op->op_match |= (bitpattern[i] == '1') << (15-i);
		}
	}
	/* Terminate the list */
	op->name[0] = 0;
}