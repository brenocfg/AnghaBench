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
 int /*<<< orphan*/  EmitString (char*) ; 
 scalar_t__ LAST_COMMAND_SUB_DI_4 ; 
 scalar_t__ LAST_COMMAND_SUB_DI_8 ; 
 scalar_t__ LastCommand ; 
 int compiledOfs ; 
 int instruction ; 
 scalar_t__* jused ; 

__attribute__((used)) static void EmitAddEDI4(vm_t *vm) {
	if (LastCommand == LAST_COMMAND_SUB_DI_4 && jused[instruction-1] == 0) 
	{		// sub di,4
		compiledOfs -= 3;
		vm->instructionPointers[ instruction-1 ] = compiledOfs;
		return;
	}
	if (LastCommand == LAST_COMMAND_SUB_DI_8 && jused[instruction-1] == 0) 
	{		// sub di,8
		compiledOfs -= 3;
		vm->instructionPointers[ instruction-1 ] = compiledOfs;
		EmitString( "83 EF 04" );	//	sub edi,4
		return;
	}
	EmitString( "83 C7 04" );	//	add edi,4
}