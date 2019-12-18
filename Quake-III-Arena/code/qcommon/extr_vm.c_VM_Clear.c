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
typedef  int /*<<< orphan*/  vm_t ;
struct TYPE_3__ {scalar_t__ dllHandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int MAX_VM ; 
 int /*<<< orphan*/  Sys_UnloadDll (scalar_t__) ; 
 int /*<<< orphan*/ * currentVM ; 
 int /*<<< orphan*/ * lastVM ; 
 TYPE_1__* vmTable ; 

void VM_Clear(void) {
	int i;
	for (i=0;i<MAX_VM; i++) {
		if ( vmTable[i].dllHandle ) {
			Sys_UnloadDll( vmTable[i].dllHandle );
		}
		Com_Memset( &vmTable[i], 0, sizeof( vm_t ) );
	}
	currentVM = NULL;
	lastVM = NULL;
}