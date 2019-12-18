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
typedef  int /*<<< orphan*/  playerInfo_t ;
struct TYPE_2__ {int /*<<< orphan*/  playerinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANIM_IDLE ; 
 int /*<<< orphan*/  Controls_UpdateModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  UI_PlayerInfo_SetModel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ s_controls ; 

__attribute__((used)) static void Controls_InitModel( void )
{
	memset( &s_controls.playerinfo, 0, sizeof(playerInfo_t) );

	UI_PlayerInfo_SetModel( &s_controls.playerinfo, UI_Cvar_VariableString( "model" ) );

	Controls_UpdateModel( ANIM_IDLE );
}