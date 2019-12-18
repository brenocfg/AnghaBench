#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int id; } ;
typedef  TYPE_4__ menucommon_s ;
struct TYPE_8__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_7__ {int curvalue; } ;
struct TYPE_6__ {int curvalue; } ;
struct TYPE_10__ {TYPE_3__ quality; TYPE_2__ musicvolume; TYPE_1__ sfxvolume; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_APPEND ; 
#define  ID_BACK 135 
#define  ID_DISPLAY 134 
#define  ID_EFFECTSVOLUME 133 
#define  ID_GRAPHICS 132 
#define  ID_MUSICVOLUME 131 
#define  ID_NETWORK 130 
#define  ID_QUALITY 129 
#define  ID_SOUND 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_DisplayOptionsMenu () ; 
 int /*<<< orphan*/  UI_ForceMenuOff () ; 
 int /*<<< orphan*/  UI_GraphicsOptionsMenu () ; 
 int /*<<< orphan*/  UI_NetworkOptionsMenu () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 TYPE_5__ soundOptionsInfo ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 

__attribute__((used)) static void UI_SoundOptionsMenu_Event( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_GRAPHICS:
		UI_PopMenu();
		UI_GraphicsOptionsMenu();
		break;

	case ID_DISPLAY:
		UI_PopMenu();
		UI_DisplayOptionsMenu();
		break;

	case ID_SOUND:
		break;

	case ID_NETWORK:
		UI_PopMenu();
		UI_NetworkOptionsMenu();
		break;

	case ID_EFFECTSVOLUME:
		trap_Cvar_SetValue( "s_volume", soundOptionsInfo.sfxvolume.curvalue / 10 );
		break;

	case ID_MUSICVOLUME:
		trap_Cvar_SetValue( "s_musicvolume", soundOptionsInfo.musicvolume.curvalue / 10 );
		break;

	case ID_QUALITY:
		if( soundOptionsInfo.quality.curvalue ) {
			trap_Cvar_SetValue( "s_khz", 22 );
			trap_Cvar_SetValue( "s_compression", 0 );
		}
		else {
			trap_Cvar_SetValue( "s_khz", 11 );
			trap_Cvar_SetValue( "s_compression", 1 );
		}
		UI_ForceMenuOff();
		trap_Cmd_ExecuteText( EXEC_APPEND, "snd_restart\n" );
		break;
/*
	case ID_A3D:
		if( soundOptionsInfo.a3d.curvalue ) {
			trap_Cmd_ExecuteText( EXEC_NOW, "s_enable_a3d\n" );
		}
		else {
			trap_Cmd_ExecuteText( EXEC_NOW, "s_disable_a3d\n" );
		}
		soundOptionsInfo.a3d.curvalue = (int)trap_Cvar_VariableValue( "s_usingA3D" );
		break;
*/
	case ID_BACK:
		UI_PopMenu();
		break;
	}
}