#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ dataBase; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* currentVM ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int,int,int,int,int) ; 

void VM_LogSyscalls( int *args ) {
	static	int		callnum;
	static	FILE	*f;

	if ( !f ) {
		f = fopen("syscalls.log", "w" );
	}
	callnum++;
	fprintf(f, "%i: %i (%i) = %i %i %i %i\n", callnum, args - (int *)currentVM->dataBase,
		args[0], args[1], args[2], args[3], args[4] );
}