#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int id; } ;
typedef  TYPE_1__ menucommon_s ;
struct TYPE_4__ {scalar_t__ demoversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_APPEND ; 
 scalar_t__ ID_CIN_END ; 
 int ID_CIN_IDLOGO ; 
 int QM_ACTIVATED ; 
 int* cinematics ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 TYPE_2__ uis ; 
 char* va (char*,int) ; 

__attribute__((used)) static void UI_CinematicsMenu_Event( void *ptr, int event ) {
	int		n;

	if (event != QM_ACTIVATED)
		return;

	n = ((menucommon_s*)ptr)->id - ID_CIN_IDLOGO;
	trap_Cvar_Set( "nextmap", va( "ui_cinematics %i", n ) );
	if( uis.demoversion && ((menucommon_s*)ptr)->id == ID_CIN_END ) {
		trap_Cmd_ExecuteText( EXEC_APPEND, "disconnect; cinematic demoEnd.RoQ 1\n" );
	}
	else {
		trap_Cmd_ExecuteText( EXEC_APPEND, va( "disconnect; cinematic %s.RoQ\n", cinematics[n] ) );
	}
}