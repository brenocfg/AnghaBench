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
struct TYPE_4__ {int codeLength; scalar_t__* instructionPointers; scalar_t__ codeBase; } ;
typedef  TYPE_1__ vm_t ;

/* Variables and functions */
 char const* VM_ValueToSymbol (TYPE_1__*,int) ; 

const char *VM_SymbolForCompiledPointer( vm_t *vm, void *code ) {
	int			i;

	if ( code < (void *)vm->codeBase ) {
		return "Before code block";
	}
	if ( code >= (void *)(vm->codeBase + vm->codeLength) ) {
		return "After code block";
	}

	// find which original instruction it is after
	for ( i = 0 ; i < vm->codeLength ; i++ ) {
		if ( (void *)vm->instructionPointers[i] > code ) {
			break;
		}
	}
	i--;

	// now look up the bytecode instruction pointer
	return VM_ValueToSymbol( vm, i );
}