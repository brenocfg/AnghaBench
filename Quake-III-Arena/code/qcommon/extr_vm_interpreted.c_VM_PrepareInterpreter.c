#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int codeLength; int* instructionPointers; scalar_t__ codeBase; } ;
typedef  TYPE_1__ vm_t ;
struct TYPE_6__ {int codeOffset; int instructionCount; int codeLength; } ;
typedef  TYPE_2__ vmHeader_t ;
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 scalar_t__ Hunk_Alloc (int,int /*<<< orphan*/ ) ; 
#define  OP_ARG 149 
#define  OP_BLOCK_COPY 148 
#define  OP_CONST 147 
#define  OP_ENTER 146 
#define  OP_EQ 145 
#define  OP_EQF 144 
#define  OP_GEF 143 
#define  OP_GEI 142 
#define  OP_GEU 141 
#define  OP_GTF 140 
#define  OP_GTI 139 
#define  OP_GTU 138 
#define  OP_LEAVE 137 
#define  OP_LEF 136 
#define  OP_LEI 135 
#define  OP_LEU 134 
#define  OP_LOCAL 133 
#define  OP_LTF 132 
#define  OP_LTI 131 
#define  OP_LTU 130 
#define  OP_NE 129 
#define  OP_NEF 128 
 int /*<<< orphan*/  h_high ; 
 int loadWord (int*) ; 

void VM_PrepareInterpreter( vm_t *vm, vmHeader_t *header ) {
	int		op;
	int		pc;
	byte	*code;
	int		instruction;
	int		*codeBase;

	vm->codeBase = Hunk_Alloc( vm->codeLength*4, h_high );			// we're now int aligned
//	memcpy( vm->codeBase, (byte *)header + header->codeOffset, vm->codeLength );

	// we don't need to translate the instructions, but we still need
	// to find each instructions starting point for jumps
	pc = 0;
	instruction = 0;
	code = (byte *)header + header->codeOffset;
	codeBase = (int *)vm->codeBase;

	while ( instruction < header->instructionCount ) {
		vm->instructionPointers[ instruction ] = pc;
		instruction++;

		op = code[ pc ];
		codeBase[pc] = op;
		if ( pc > header->codeLength ) {
			Com_Error( ERR_FATAL, "VM_PrepareInterpreter: pc > header->codeLength" );
		}

		pc++;

		// these are the only opcodes that aren't a single byte
		switch ( op ) {
		case OP_ENTER:
		case OP_CONST:
		case OP_LOCAL:
		case OP_LEAVE:
		case OP_EQ:
		case OP_NE:
		case OP_LTI:
		case OP_LEI:
		case OP_GTI:
		case OP_GEI:
		case OP_LTU:
		case OP_LEU:
		case OP_GTU:
		case OP_GEU:
		case OP_EQF:
		case OP_NEF:
		case OP_LTF:
		case OP_LEF:
		case OP_GTF:
		case OP_GEF:
		case OP_BLOCK_COPY:
			codeBase[pc+0] = loadWord(&code[pc]);
			pc += 4;
			break;
		case OP_ARG:
			codeBase[pc+0] = code[pc];
			pc += 1;
			break;
		default:
			break;
		}

	}
	pc = 0;
	instruction = 0;
	code = (byte *)header + header->codeOffset;
	codeBase = (int *)vm->codeBase;

	while ( instruction < header->instructionCount ) {
		op = code[ pc ];
		instruction++;
		pc++;
		switch ( op ) {
		case OP_ENTER:
		case OP_CONST:
		case OP_LOCAL:
		case OP_LEAVE:
		case OP_EQ:
		case OP_NE:
		case OP_LTI:
		case OP_LEI:
		case OP_GTI:
		case OP_GEI:
		case OP_LTU:
		case OP_LEU:
		case OP_GTU:
		case OP_GEU:
		case OP_EQF:
		case OP_NEF:
		case OP_LTF:
		case OP_LEF:
		case OP_GTF:
		case OP_GEF:
		case OP_BLOCK_COPY:
			switch(op) {
				case OP_EQ:
				case OP_NE:
				case OP_LTI:
				case OP_LEI:
				case OP_GTI:
				case OP_GEI:
				case OP_LTU:
				case OP_LEU:
				case OP_GTU:
				case OP_GEU:
				case OP_EQF:
				case OP_NEF:
				case OP_LTF:
				case OP_LEF:
				case OP_GTF:
				case OP_GEF:
				codeBase[pc] = vm->instructionPointers[codeBase[pc]];
				break;
			default:
				break;
			}
			pc += 4;
			break;
		case OP_ARG:
			pc += 1;
			break;
		default:
			break;
		}

	}
}