#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CL_Shutdown () ; 
 int /*<<< orphan*/  Com_Shutdown () ; 
 int /*<<< orphan*/  FS_Shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_Shutdown (char*) ; 
 int /*<<< orphan*/  Sys_Quit () ; 
 int /*<<< orphan*/  com_errorEntered ; 
 int /*<<< orphan*/  qtrue ; 

void Com_Quit_f( void ) {
	// don't try to shutdown if we are in a recursive error
	if ( !com_errorEntered ) {
		SV_Shutdown ("Server quit\n");
		CL_Shutdown ();
		Com_Shutdown ();
		FS_Shutdown(qtrue);
	}
	Sys_Quit ();
}