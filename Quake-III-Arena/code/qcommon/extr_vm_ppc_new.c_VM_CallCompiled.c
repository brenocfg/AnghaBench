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
struct TYPE_4__ {int programStack; int dataMask; int instructionPointersLength; int /*<<< orphan*/  currentlyInterpreting; scalar_t__ instructionPointers; scalar_t__ codeBase; int /*<<< orphan*/ * dataBase; } ;
typedef  TYPE_1__ vm_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  AsmCall ; 
 TYPE_1__* currentVM ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 void stub1 (int,int,int,int,int,int,int,int) ; 
 void stub2 (int,int,int,int,int,int,int,int) ; 

int	VM_CallCompiled( vm_t *vm, int *args ) {
	int		stack[1024];
	int		programStack;
	int		stackOnEntry;
	byte	*image;

	currentVM = vm;

	//printf("VM_CallCompiled: %p   %08lx %08lx %08lx\n",
	//	vm, args[0],args[1],args[2]);
		
	// interpret the code
	vm->currentlyInterpreting = qtrue;

	// we might be called recursively, so this might not be the very top
	programStack = vm->programStack;
	stackOnEntry = programStack;
	image = vm->dataBase;
	
	// set up the stack frame 
	programStack -= 48;

	*(int *)&image[ programStack + 44] = args[9];
	*(int *)&image[ programStack + 40] = args[8];
	*(int *)&image[ programStack + 36] = args[7];
	*(int *)&image[ programStack + 32] = args[6];
	*(int *)&image[ programStack + 28] = args[5];
	*(int *)&image[ programStack + 24] = args[4];
	*(int *)&image[ programStack + 20] = args[3];
	*(int *)&image[ programStack + 16] = args[2];
	*(int *)&image[ programStack + 12] = args[1];
	*(int *)&image[ programStack + 8 ] = args[0];
	*(int *)&image[ programStack + 4 ] = 0;	// return stack
	*(int *)&image[ programStack ] = -1;	// will terminate the loop on return

	// Cheesy... manually save registers used by VM call...
	// off we go into generated code...
	// the PPC calling standard says the parms will all go into R3 - R11, so 
	// no special asm code is needed here
#ifdef __GNUC__
	((void(*)(int, int, int, int, int, int, int, int))(vm->codeBase))( 
		programStack, (int)&stack, 
		(int)image, vm->dataMask, (int)&AsmCall, 
		(int)vm->instructionPointers, vm->instructionPointersLength,
        (int)vm );
#else
	((void(*)(int, int, int, int, int, int, int, int))(vm->codeBase))( 
		programStack, (int)&stack, 
		(int)image, vm->dataMask, *(int *)&AsmCall /* skip function pointer header */, 
		(int)vm->instructionPointers, vm->instructionPointersLength,
        (int)vm );
#endif
	vm->programStack = stackOnEntry;

    vm->currentlyInterpreting = qfalse;

	return stack[1];
}