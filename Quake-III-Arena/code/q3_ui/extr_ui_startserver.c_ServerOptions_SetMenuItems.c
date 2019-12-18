#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_30__ {TYPE_8__ field; } ;
struct TYPE_28__ {int curvalue; } ;
struct TYPE_26__ {char* buffer; } ;
struct TYPE_27__ {TYPE_5__ field; } ;
struct TYPE_24__ {char* buffer; } ;
struct TYPE_25__ {TYPE_3__ field; } ;
struct TYPE_22__ {char* buffer; } ;
struct TYPE_23__ {TYPE_1__ field; } ;
struct TYPE_17__ {char* name; } ;
struct TYPE_18__ {TYPE_11__ generic; } ;
struct TYPE_16__ {scalar_t__ curvalue; } ;
struct TYPE_21__ {int gametype; int /*<<< orphan*/  mapnamebuffer; TYPE_12__ mappic; TYPE_10__ pure; TYPE_9__ hostname; TYPE_7__ friendlyfire; TYPE_6__ timelimit; TYPE_4__ flaglimit; TYPE_2__ fraglimit; } ;
struct TYPE_19__ {int /*<<< orphan*/  string; } ;
struct TYPE_20__ {int* maplist; size_t currentmap; TYPE_13__ mapname; } ;

/* Variables and functions */
 scalar_t__ Com_Clamp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
#define  GT_CTF 131 
#define  GT_FFA 130 
#define  GT_TEAM 129 
#define  GT_TOURNAMENT 128 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_strupr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ServerOptions_InitBotNames () ; 
 int /*<<< orphan*/  ServerOptions_InitPlayerItems () ; 
 int /*<<< orphan*/  ServerOptions_SetPlayerItems () ; 
 int /*<<< orphan*/  UI_Cvar_VariableString (char*) ; 
 TYPE_15__ s_serveroptions ; 
 TYPE_14__ s_startserver ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_VariableValue (char*) ; 

__attribute__((used)) static void ServerOptions_SetMenuItems( void ) {
	static char picname[64];

	switch( s_serveroptions.gametype ) {
	case GT_FFA:
	default:
		Com_sprintf( s_serveroptions.fraglimit.field.buffer, 4, "%i", (int)Com_Clamp( 0, 999, trap_Cvar_VariableValue( "ui_ffa_fraglimit" ) ) );
		Com_sprintf( s_serveroptions.timelimit.field.buffer, 4, "%i", (int)Com_Clamp( 0, 999, trap_Cvar_VariableValue( "ui_ffa_timelimit" ) ) );
		break;

	case GT_TOURNAMENT:
		Com_sprintf( s_serveroptions.fraglimit.field.buffer, 4, "%i", (int)Com_Clamp( 0, 999, trap_Cvar_VariableValue( "ui_tourney_fraglimit" ) ) );
		Com_sprintf( s_serveroptions.timelimit.field.buffer, 4, "%i", (int)Com_Clamp( 0, 999, trap_Cvar_VariableValue( "ui_tourney_timelimit" ) ) );
		break;

	case GT_TEAM:
		Com_sprintf( s_serveroptions.fraglimit.field.buffer, 4, "%i", (int)Com_Clamp( 0, 999, trap_Cvar_VariableValue( "ui_team_fraglimit" ) ) );
		Com_sprintf( s_serveroptions.timelimit.field.buffer, 4, "%i", (int)Com_Clamp( 0, 999, trap_Cvar_VariableValue( "ui_team_timelimit" ) ) );
		s_serveroptions.friendlyfire.curvalue = (int)Com_Clamp( 0, 1, trap_Cvar_VariableValue( "ui_team_friendly" ) );
		break;

	case GT_CTF:
		Com_sprintf( s_serveroptions.flaglimit.field.buffer, 4, "%i", (int)Com_Clamp( 0, 100, trap_Cvar_VariableValue( "ui_ctf_capturelimit" ) ) );
		Com_sprintf( s_serveroptions.timelimit.field.buffer, 4, "%i", (int)Com_Clamp( 0, 999, trap_Cvar_VariableValue( "ui_ctf_timelimit" ) ) );
		s_serveroptions.friendlyfire.curvalue = (int)Com_Clamp( 0, 1, trap_Cvar_VariableValue( "ui_ctf_friendly" ) );
		break;
	}

	Q_strncpyz( s_serveroptions.hostname.field.buffer, UI_Cvar_VariableString( "sv_hostname" ), sizeof( s_serveroptions.hostname.field.buffer ) );
	s_serveroptions.pure.curvalue = Com_Clamp( 0, 1, trap_Cvar_VariableValue( "sv_pure" ) );

	// set the map pic
	Com_sprintf( picname, 64, "levelshots/%s", s_startserver.maplist[s_startserver.currentmap] );
	s_serveroptions.mappic.generic.name = picname;

	// set the map name
	strcpy( s_serveroptions.mapnamebuffer, s_startserver.mapname.string );
	Q_strupr( s_serveroptions.mapnamebuffer );

	// get the player selections initialized
	ServerOptions_InitPlayerItems();
	ServerOptions_SetPlayerItems();

	// seed bot names
	ServerOptions_InitBotNames();
	ServerOptions_SetPlayerItems();
}