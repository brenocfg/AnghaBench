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
struct TYPE_3__ {int /*<<< orphan*/ * dataMask; int /*<<< orphan*/ * instructionPointersLength; int /*<<< orphan*/ * codeLength; scalar_t__ compiled; scalar_t__ dllHandle; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ vm_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int MAX_VM ; 
 TYPE_1__* vmTable ; 

void VM_VmInfo_f( void ) {
	vm_t	*vm;
	int		i;

	Com_Printf( "Registered virtual machines:\n" );
	for ( i = 0 ; i < MAX_VM ; i++ ) {
		vm = &vmTable[i];
		if ( !vm->name[0] ) {
			break;
		}
		Com_Printf( "%s : ", vm->name );
		if ( vm->dllHandle ) {
			Com_Printf( "native\n" );
			continue;
		}
		if ( vm->compiled ) {
			Com_Printf( "compiled on load\n" );
		} else {
			Com_Printf( "interpreted\n" );
		}
		Com_Printf( "    code length : %7i\n", vm->codeLength );
		Com_Printf( "    table length: %7i\n", vm->instructionPointersLength );
		Com_Printf( "    data length : %7i\n", vm->dataMask + 1 );
	}
}