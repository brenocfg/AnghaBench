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
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ART_MENU0 ; 
 int /*<<< orphan*/  ART_MENU1 ; 
 int /*<<< orphan*/  ART_NEXT0 ; 
 int /*<<< orphan*/  ART_NEXT1 ; 
 int /*<<< orphan*/  ART_REPLAY0 ; 
 int /*<<< orphan*/  ART_REPLAY1 ; 
 int /*<<< orphan*/  qfalse ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_S_RegisterSound (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ui_medalPicNames ; 
 char** ui_medalSounds ; 

void UI_SPPostgameMenu_Cache( void ) {
	int			n;
	qboolean	buildscript;

	buildscript = trap_Cvar_VariableValue("com_buildscript");

	trap_R_RegisterShaderNoMip( ART_MENU0 );
	trap_R_RegisterShaderNoMip( ART_MENU1 );
	trap_R_RegisterShaderNoMip( ART_REPLAY0 );
	trap_R_RegisterShaderNoMip( ART_REPLAY1 );
	trap_R_RegisterShaderNoMip( ART_NEXT0 );
	trap_R_RegisterShaderNoMip( ART_NEXT1 );
	for( n = 0; n < 6; n++ ) {
		trap_R_RegisterShaderNoMip( ui_medalPicNames[n] );
		trap_S_RegisterSound( ui_medalSounds[n], qfalse );
	}

	if( buildscript ) {
		trap_S_RegisterSound( "music/loss.wav", qfalse );
		trap_S_RegisterSound( "music/win.wav", qfalse );
		trap_S_RegisterSound( "sound/player/announce/youwin.wav", qfalse );
	}
}