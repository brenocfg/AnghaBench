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
struct TYPE_3__ {int programStack; int (* systemCall ) (int*) ;scalar_t__ dataBase; } ;
typedef  TYPE_1__ vm_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int* callOpStack ; 
 int callProgramStack ; 
 int callSyscallNum ; 
 TYPE_1__* currentVM ; 
 int stub1 (int*) ; 

void callAsmCall(void)
{
	vm_t	*savedVM;
	int		*callOpStack2;

	savedVM = currentVM;
	callOpStack2 = callOpStack;

	// save the stack to allow recursive VM entry
	currentVM->programStack = callProgramStack - 4;
	*(int *)((byte *)currentVM->dataBase + callProgramStack + 4) = callSyscallNum;
//VM_LogSyscalls(  (int *)((byte *)currentVM->dataBase + programStack + 4) );
	*(callOpStack2+1) = currentVM->systemCall( (int *)((byte *)currentVM->dataBase + callProgramStack + 4) );

 	currentVM = savedVM;
}