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
typedef  double* vec4_t ;
typedef  int /*<<< orphan*/  string ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int x; int y; } ;
struct TYPE_10__ {TYPE_2__ generic; } ;
struct TYPE_6__ {scalar_t__ shader; } ;
struct TYPE_9__ {char* playerModel; int* awardLevels; int numMaps; char** levelNames; int* levelScores; int* levelScoresSkill; int numBots; char** botNames; scalar_t__* botPics; int /*<<< orphan*/  selectedArenaInfo; scalar_t__ levelFocusPic; TYPE_5__* item_maps; int /*<<< orphan*/  menu; scalar_t__ levelSelectedPic; scalar_t__* levelCompletePic; TYPE_1__ item_player; int /*<<< orphan*/  playerPicName; scalar_t__ reinit; } ;
struct TYPE_8__ {int realtime; } ;

/* Variables and functions */
 int AWARDS_Y ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,...) ; 
 char* Info_ValueForKey (int /*<<< orphan*/ ,char*) ; 
 int MAX_INFO_VALUE ; 
 int /*<<< orphan*/  Menu_Draw (int /*<<< orphan*/ *) ; 
 TYPE_5__* Menu_ItemAtCursor (int /*<<< orphan*/ *) ; 
 int PLAYER_Y ; 
 int PULSE_DIVISOR ; 
 int /*<<< orphan*/  PlayerIcon (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_CleanStr (char*) ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  Q_strupr (char*) ; 
 int UI_BIGFONT ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawHandlePic (int,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_FillRect (int,int,int,int,int /*<<< orphan*/ ) ; 
 int UI_LEFT ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  UI_SPLevelMenu () ; 
 int /*<<< orphan*/  Vector4Copy (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  color_black ; 
 int /*<<< orphan*/  color_orange ; 
 int /*<<< orphan*/  color_red ; 
 int /*<<< orphan*/  color_white ; 
 int /*<<< orphan*/  color_yellow ; 
 scalar_t__ currentSet ; 
 TYPE_4__ levelMenuInfo ; 
 int selectedArena ; 
 scalar_t__ selectedArenaSet ; 
 double sin (int) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 int /*<<< orphan*/  trap_R_SetColor (double*) ; 
 TYPE_3__ uis ; 
 char* va (char*,scalar_t__) ; 

__attribute__((used)) static void UI_SPLevelMenu_MenuDraw( void ) {
	int				n, i;
	int				x, y;
	vec4_t			color;
	int				level;
//	int				fraglimit;
	int				pad;
	char			buf[MAX_INFO_VALUE];
	char			string[64];

	if(	levelMenuInfo.reinit ) {
		UI_PopMenu();
		UI_SPLevelMenu();
		return;
	}

	// draw player name
	trap_Cvar_VariableStringBuffer( "name", string, 32 );
	Q_CleanStr( string );
	UI_DrawProportionalString( 320, PLAYER_Y, string, UI_CENTER|UI_SMALLFONT, color_orange );

	// check for model changes
	trap_Cvar_VariableStringBuffer( "model", buf, sizeof(buf) );
	if( Q_stricmp( buf, levelMenuInfo.playerModel ) != 0 ) {
		Q_strncpyz( levelMenuInfo.playerModel, buf, sizeof(levelMenuInfo.playerModel) );
		PlayerIcon( levelMenuInfo.playerModel, levelMenuInfo.playerPicName, sizeof(levelMenuInfo.playerPicName) );
		levelMenuInfo.item_player.shader = 0;
	}

	// standard menu drawing
	Menu_Draw( &levelMenuInfo.menu );

	// draw player award levels
	y = AWARDS_Y;
	i = 0;
	for( n = 0; n < 6; n++ ) {
		level = levelMenuInfo.awardLevels[n];
		if( level > 0 ) {
			if( i & 1 ) {
				x = 224 - (i - 1 ) / 2 * (48 + 16);
			}
			else {
				x = 368 + i / 2 * (48 + 16);
			}
			i++;

			if( level == 1 ) {
				continue;
			}

			if( level >= 1000000 ) {
				Com_sprintf( string, sizeof(string), "%im", level / 1000000 );
			}
			else if( level >= 1000 ) {
				Com_sprintf( string, sizeof(string), "%ik", level / 1000 );
			}
			else {
				Com_sprintf( string, sizeof(string), "%i", level );
			}

			UI_DrawString( x + 24, y + 48, string, UI_CENTER, color_yellow );
		}
	}

	UI_DrawProportionalString( 18, 38, va( "Tier %i", selectedArenaSet + 1 ), UI_LEFT|UI_SMALLFONT, color_orange );

	for ( n = 0; n < levelMenuInfo.numMaps; n++ ) {
		x = levelMenuInfo.item_maps[n].generic.x;
		y = levelMenuInfo.item_maps[n].generic.y;
		UI_FillRect( x, y + 96, 128, 18, color_black );
	}

	if ( selectedArenaSet > currentSet ) {
		UI_DrawProportionalString( 320, 216, "ACCESS DENIED", UI_CENTER|UI_BIGFONT, color_red );
		return;
	}

	// show levelshots for levels of current tier
	Vector4Copy( color_white, color );
	color[3] = 0.5+0.5*sin(uis.realtime/PULSE_DIVISOR);
	for ( n = 0; n < levelMenuInfo.numMaps; n++ ) {
		x = levelMenuInfo.item_maps[n].generic.x;
		y = levelMenuInfo.item_maps[n].generic.y;

		UI_DrawString( x + 64, y + 96, levelMenuInfo.levelNames[n], UI_CENTER|UI_SMALLFONT, color_orange );

		if( levelMenuInfo.levelScores[n] == 1 ) {
			UI_DrawHandlePic( x, y, 128, 96, levelMenuInfo.levelCompletePic[levelMenuInfo.levelScoresSkill[n] - 1] ); 
		}

		if ( n == selectedArena ) {
			if( Menu_ItemAtCursor( &levelMenuInfo.menu ) == &levelMenuInfo.item_maps[n] ) {
				trap_R_SetColor( color );
			}
			UI_DrawHandlePic( x-1, y-1, 130, 130 - 14, levelMenuInfo.levelSelectedPic ); 
			trap_R_SetColor( NULL );
		}
		else if( Menu_ItemAtCursor( &levelMenuInfo.menu ) == &levelMenuInfo.item_maps[n] ) {
			trap_R_SetColor( color );
			UI_DrawHandlePic( x-31, y-30, 256, 256-27, levelMenuInfo.levelFocusPic); 
			trap_R_SetColor( NULL );
		}
	}

	// show map name and long name of selected level
	y = 192;
	Q_strncpyz( buf, Info_ValueForKey( levelMenuInfo.selectedArenaInfo, "map" ), 20 );
	Q_strupr( buf );
	Com_sprintf( string, sizeof(string), "%s: %s", buf, Info_ValueForKey( levelMenuInfo.selectedArenaInfo, "longname" ) );
	UI_DrawProportionalString( 320, y, string, UI_CENTER|UI_SMALLFONT, color_orange );

//	fraglimit = atoi( Info_ValueForKey( levelMenuInfo.selectedArenaInfo, "fraglimit" ) );
//	UI_DrawString( 18, 212, va("Frags %i", fraglimit) , UI_LEFT|UI_SMALLFONT, color_orange );

	// draw bot opponents
	y += 24;
	pad = (7 - levelMenuInfo.numBots) * (64 + 26) / 2;
	for( n = 0; n < levelMenuInfo.numBots; n++ ) {
		x = 18 + pad + (64 + 26) * n;
		if( levelMenuInfo.botPics[n] ) {
			UI_DrawHandlePic( x, y, 64, 64, levelMenuInfo.botPics[n]);
		}
		else {
			UI_FillRect( x, y, 64, 64, color_black );
			UI_DrawProportionalString( x+22, y+18, "?", UI_BIGFONT, color_orange );
		}
		UI_DrawString( x, y + 64, levelMenuInfo.botNames[n], UI_SMALLFONT|UI_LEFT, color_orange );
	}
}