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
struct insn {size_t format; unsigned char opfrag; } ;

/* Variables and functions */
 size_t INSTR_INVALID ; 
 unsigned char** formats ; 
 struct insn* opcode ; 
 struct insn* opcode_01 ; 
 struct insn* opcode_a5 ; 
 struct insn* opcode_a7 ; 
 struct insn* opcode_b2 ; 
 struct insn* opcode_b3 ; 
 struct insn* opcode_b9 ; 
 struct insn* opcode_c0 ; 
 struct insn* opcode_c2 ; 
 struct insn* opcode_c8 ; 
 struct insn* opcode_e3 ; 
 struct insn* opcode_e5 ; 
 struct insn* opcode_eb ; 
 struct insn* opcode_ec ; 
 struct insn* opcode_ed ; 

__attribute__((used)) static struct insn *find_insn(unsigned char *code)
{
	unsigned char opfrag = code[1];
	unsigned char opmask;
	struct insn *table;

	switch (code[0]) {
	case 0x01:
		table = opcode_01;
		break;
	case 0xa5:
		table = opcode_a5;
		break;
	case 0xa7:
		table = opcode_a7;
		break;
	case 0xb2:
		table = opcode_b2;
		break;
	case 0xb3:
		table = opcode_b3;
		break;
	case 0xb9:
		table = opcode_b9;
		break;
	case 0xc0:
		table = opcode_c0;
		break;
	case 0xc2:
		table = opcode_c2;
		break;
	case 0xc8:
		table = opcode_c8;
		break;
	case 0xe3:
		table = opcode_e3;
		opfrag = code[5];
		break;
	case 0xe5:
		table = opcode_e5;
		break;
	case 0xeb:
		table = opcode_eb;
		opfrag = code[5];
		break;
	case 0xec:
		table = opcode_ec;
		opfrag = code[5];
		break;
	case 0xed:
		table = opcode_ed;
		opfrag = code[5];
		break;
	default:
		table = opcode;
		opfrag = code[0];
		break;
	}
	while (table->format != INSTR_INVALID) {
		opmask = formats[table->format][0];
		if (table->opfrag == (opfrag & opmask))
			return table;
		table++;
	}
	return NULL;
}