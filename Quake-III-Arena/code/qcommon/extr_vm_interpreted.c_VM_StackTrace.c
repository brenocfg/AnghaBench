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
struct TYPE_4__ {int /*<<< orphan*/ * dataBase; } ;
typedef  TYPE_1__ vm_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_ValueToSymbol (TYPE_1__*,int) ; 

void VM_StackTrace( vm_t *vm, int programCounter, int programStack ) {
	int		count;

	count = 0;
	do {
		Com_Printf( "%s\n", VM_ValueToSymbol( vm, programCounter ) );
		programStack =  *(int *)&vm->dataBase[programStack+4];
		programCounter = *(int *)&vm->dataBase[programStack];
	} while ( programCounter != -1 && ++count < 32 );

}