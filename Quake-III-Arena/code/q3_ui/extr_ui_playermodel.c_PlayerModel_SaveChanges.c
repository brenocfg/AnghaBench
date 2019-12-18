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
struct TYPE_2__ {int /*<<< orphan*/  modelskin; } ;

/* Variables and functions */
 TYPE_1__ s_playermodel ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PlayerModel_SaveChanges( void )
{
	trap_Cvar_Set( "model", s_playermodel.modelskin );
	trap_Cvar_Set( "headmodel", s_playermodel.modelskin );
	trap_Cvar_Set( "team_model", s_playermodel.modelskin );
	trap_Cvar_Set( "team_headmodel", s_playermodel.modelskin );
}