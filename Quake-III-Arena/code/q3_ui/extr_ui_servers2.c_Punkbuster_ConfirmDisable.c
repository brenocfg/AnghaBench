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
typedef  scalar_t__ qboolean ;
struct TYPE_3__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_4__ {TYPE_1__ punkbuster; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Clamp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_Message (int /*<<< orphan*/ ) ; 
 TYPE_2__ g_arenaservers ; 
 int /*<<< orphan*/  punkbuster_msg ; 
 int /*<<< orphan*/  trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  trap_SetPbClStatus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Punkbuster_ConfirmDisable( qboolean result ) {
	if (result)
	{
		trap_SetPbClStatus(0);
		UI_Message( punkbuster_msg );
	}
	g_arenaservers.punkbuster.curvalue = Com_Clamp( 0, 1, trap_Cvar_VariableValue( "cl_punkbuster" ) );
}