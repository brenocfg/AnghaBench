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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVAR_SERVERINFO ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 TYPE_1__* Cvar_FindVar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Set_f () ; 

void Cvar_SetS_f( void ) {
	cvar_t	*v;

	if ( Cmd_Argc() != 3 ) {
		Com_Printf ("usage: sets <variable> <value>\n");
		return;
	}
	Cvar_Set_f();
	v = Cvar_FindVar( Cmd_Argv( 1 ) );
	if ( !v ) {
		return;
	}
	v->flags |= CVAR_SERVERINFO;
}