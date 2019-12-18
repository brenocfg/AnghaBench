#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* servername; char* updateInfoString; int connState; char* connectPacketCount; int /*<<< orphan*/  messageString; } ;
typedef  TYPE_2__ uiClientState_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  downloadName ;
struct TYPE_15__ {int widthInChars; int /*<<< orphan*/  buffer; } ;
struct TYPE_10__ {char* name; int x; int y; scalar_t__ callback; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int width; TYPE_9__ field; TYPE_1__ generic; } ;
struct TYPE_13__ {int x; int /*<<< orphan*/  wrapAround; scalar_t__ nitems; } ;
struct TYPE_12__ {int /*<<< orphan*/  menuBackShader; } ;

/* Variables and functions */
#define  CA_CHALLENGING 132 
#define  CA_CONNECTED 131 
#define  CA_CONNECTING 130 
#define  CA_LOADING 129 
#define  CA_PRIMED 128 
 int /*<<< orphan*/  CS_SERVERINFO ; 
 int /*<<< orphan*/  Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  Field_Clear (TYPE_9__*) ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_VALUE ; 
 int /*<<< orphan*/  MField_Draw (TYPE_6__*) ; 
 int /*<<< orphan*/  MTYPE_FIELD ; 
 int /*<<< orphan*/  Menu_AddItem (TYPE_5__*,void*) ; 
 int /*<<< orphan*/  Menu_Cache () ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SCREEN_HEIGHT ; 
 int SCREEN_WIDTH ; 
 int UI_BIGFONT ; 
 int UI_CENTER ; 
 int UI_DROPSHADOW ; 
 int /*<<< orphan*/  UI_DisplayDownloadInfo (char*) ; 
 int /*<<< orphan*/  UI_DrawHandlePic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawProportionalString_AutoWrapped (int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  UI_SetColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_white ; 
 int lastConnState ; 
 char* lastLoadingText ; 
 int /*<<< orphan*/  menu_text_color ; 
 TYPE_6__ passwordField ; 
 scalar_t__ passwordNeeded ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  s_customize_player_action ; 
 TYPE_5__ s_ingame_menu ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 int /*<<< orphan*/  trap_GetClientState (TYPE_2__*) ; 
 scalar_t__ trap_GetConfigString (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__ uis ; 
 char* va (char*,char*) ; 

void UI_DrawConnectScreen( qboolean overlay ) {
	char			*s;
	uiClientState_t	cstate;
	char			info[MAX_INFO_VALUE];

	Menu_Cache();

	if ( !overlay ) {
		// draw the dialog background
		UI_SetColor( color_white );
		UI_DrawHandlePic( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, uis.menuBackShader );
	}

	// see what information we should display
	trap_GetClientState( &cstate );

	info[0] = '\0';
	if( trap_GetConfigString( CS_SERVERINFO, info, sizeof(info) ) ) {
		UI_DrawProportionalString( 320, 16, va( "Loading %s", Info_ValueForKey( info, "mapname" ) ), UI_BIGFONT|UI_CENTER|UI_DROPSHADOW, color_white );
	}

	UI_DrawProportionalString( 320, 64, va("Connecting to %s", cstate.servername), UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, menu_text_color );
	//UI_DrawProportionalString( 320, 96, "Press Esc to abort", UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, menu_text_color );

	// display global MOTD at bottom
	UI_DrawProportionalString( SCREEN_WIDTH/2, SCREEN_HEIGHT-32, 
		Info_ValueForKey( cstate.updateInfoString, "motd" ), UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, menu_text_color );
	
	// print any server info (server full, bad version, etc)
	if ( cstate.connState < CA_CONNECTED ) {
		UI_DrawProportionalString_AutoWrapped( 320, 192, 630, 20, cstate.messageString, UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, menu_text_color );
	}

#if 0
	// display password field
	if ( passwordNeeded ) {
		s_ingame_menu.x = SCREEN_WIDTH * 0.50 - 128;
		s_ingame_menu.nitems = 0;
		s_ingame_menu.wrapAround = qtrue;

		passwordField.generic.type = MTYPE_FIELD;
		passwordField.generic.name = "Password:";
		passwordField.generic.callback = 0;
		passwordField.generic.x		= 10;
		passwordField.generic.y		= 180;
		Field_Clear( &passwordField.field );
		passwordField.width = 256;
		passwordField.field.widthInChars = 16;
		Q_strncpyz( passwordField.field.buffer, Cvar_VariableString("password"), 
			sizeof(passwordField.field.buffer) );

		Menu_AddItem( &s_ingame_menu, ( void * ) &s_customize_player_action );

		MField_Draw( &passwordField );
	}
#endif

	if ( lastConnState > cstate.connState ) {
		lastLoadingText[0] = '\0';
	}
	lastConnState = cstate.connState;

	switch ( cstate.connState ) {
	case CA_CONNECTING:
		s = va("Awaiting challenge...%i", cstate.connectPacketCount);
		break;
	case CA_CHALLENGING:
		s = va("Awaiting connection...%i", cstate.connectPacketCount);
		break;
	case CA_CONNECTED: {
		char downloadName[MAX_INFO_VALUE];

			trap_Cvar_VariableStringBuffer( "cl_downloadName", downloadName, sizeof(downloadName) );
			if (*downloadName) {
				UI_DisplayDownloadInfo( downloadName );
				return;
			}
		}
		s = "Awaiting gamestate...";
		break;
	case CA_LOADING:
		return;
	case CA_PRIMED:
		return;
	default:
		return;
	}

	UI_DrawProportionalString( 320, 128, s, UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, color_white );

	// password required / connection rejected information goes here
}