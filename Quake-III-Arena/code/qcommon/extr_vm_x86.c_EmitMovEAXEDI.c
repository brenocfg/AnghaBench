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
struct TYPE_3__ {int* instructionPointers; } ;
typedef  TYPE_1__ vm_t ;

/* Variables and functions */
 int /*<<< orphan*/  Emit4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmitString (char*) ; 
 scalar_t__ LAST_COMMAND_MOV_EDI_EAX ; 
 scalar_t__ LastCommand ; 
 scalar_t__ OP_CONST ; 
 scalar_t__ OP_DIVI ; 
 scalar_t__ OP_DIVU ; 
 scalar_t__ OP_MULI ; 
 scalar_t__ OP_MULU ; 
 scalar_t__ OP_STORE1 ; 
 scalar_t__ OP_STORE2 ; 
 scalar_t__ OP_STORE4 ; 
 int* buf ; 
 int compiledOfs ; 
 int instruction ; 
 int /*<<< orphan*/  lastConst ; 
 scalar_t__ pop1 ; 

__attribute__((used)) static void EmitMovEAXEDI(vm_t *vm) {
	if (LastCommand == LAST_COMMAND_MOV_EDI_EAX) 
	{	// mov [edi], eax
		compiledOfs -= 2;
		vm->instructionPointers[ instruction-1 ] = compiledOfs;
		return;
	}
	if (pop1 == OP_DIVI || pop1 == OP_DIVU || pop1 == OP_MULI || pop1 == OP_MULU ||
		pop1 == OP_STORE4 || pop1 == OP_STORE2 || pop1 == OP_STORE1 ) 
	{	
		return;
	}
	if (pop1 == OP_CONST && buf[compiledOfs-6] == 0xC7 && buf[compiledOfs-5] == 0x07 ) 
	{	// mov edi, 0x123456
		compiledOfs -= 6;
		vm->instructionPointers[ instruction-1 ] = compiledOfs;
		EmitString( "B8" );			// mov	eax, 0x12345678
		Emit4( lastConst );
		return;
	}
	EmitString( "8B 07" );		// mov eax, dword ptr [edi]
}