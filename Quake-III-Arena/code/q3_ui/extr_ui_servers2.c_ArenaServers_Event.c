#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidfunc_f ;
struct TYPE_15__ {int id; } ;
typedef  TYPE_7__ menucommon_s ;
struct TYPE_14__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_13__ {int curvalue; } ;
struct TYPE_12__ {int curvalue; } ;
struct TYPE_11__ {int curvalue; } ;
struct TYPE_10__ {int curvalue; } ;
struct TYPE_9__ {int curvalue; } ;
struct TYPE_16__ {TYPE_6__ punkbuster; int /*<<< orphan*/  list; TYPE_5__ showempty; TYPE_4__ showfull; TYPE_3__ sortkey; TYPE_2__ gametype; TYPE_1__ master; } ;

/* Variables and functions */
 int /*<<< orphan*/  ArenaServers_Go () ; 
 int /*<<< orphan*/  ArenaServers_Remove () ; 
 int /*<<< orphan*/  ArenaServers_SaveChanges () ; 
 int /*<<< orphan*/  ArenaServers_SetType (int) ; 
 int /*<<< orphan*/  ArenaServers_Sort (int) ; 
 int /*<<< orphan*/  ArenaServers_StartRefresh () ; 
 int /*<<< orphan*/  ArenaServers_StopRefresh () ; 
 int /*<<< orphan*/  ArenaServers_UpdateMenu () ; 
 int /*<<< orphan*/  ArenaServers_UpdatePicture () ; 
#define  ID_BACK 142 
#define  ID_CONNECT 141 
#define  ID_CREATE 140 
#define  ID_GAMETYPE 139 
#define  ID_LIST 138 
#define  ID_MASTER 137 
#define  ID_PUNKBUSTER 136 
#define  ID_REFRESH 135 
#define  ID_REMOVE 134 
#define  ID_SCROLL_DOWN 133 
#define  ID_SCROLL_UP 132 
#define  ID_SHOW_EMPTY 131 
#define  ID_SHOW_FULL 130 
#define  ID_SORTKEY 129 
#define  ID_SPECIFY 128 
 int /*<<< orphan*/  K_DOWNARROW ; 
 int /*<<< orphan*/  K_UPARROW ; 
 int /*<<< orphan*/  Punkbuster_ConfirmDisable ; 
 int /*<<< orphan*/  Punkbuster_ConfirmEnable ; 
 int QM_ACTIVATED ; 
 int QM_GOTFOCUS ; 
 int /*<<< orphan*/  ScrollList_Key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_ConfirmMenu_Style (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UI_INVERSE ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  UI_SpecifyServerMenu () ; 
 int /*<<< orphan*/  UI_StartServerMenu (int /*<<< orphan*/ ) ; 
 TYPE_8__ g_arenaservers ; 
 int g_emptyservers ; 
 int g_fullservers ; 
 int g_gametype ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 

__attribute__((used)) static void ArenaServers_Event( void* ptr, int event ) {
	int		id;
	int value;

	id = ((menucommon_s*)ptr)->id;

	if( event != QM_ACTIVATED && id != ID_LIST ) {
		return;
	}

	switch( id ) {
	case ID_MASTER:
		value = g_arenaservers.master.curvalue;
		if (value >= 1)
		{
			value++;
		}
		trap_Cvar_SetValue( "ui_browserMaster", value );
		ArenaServers_SetType( value );
		break;

	case ID_GAMETYPE:
		trap_Cvar_SetValue( "ui_browserGameType", g_arenaservers.gametype.curvalue );
		g_gametype = g_arenaservers.gametype.curvalue;
		ArenaServers_UpdateMenu();
		break;

	case ID_SORTKEY:
		trap_Cvar_SetValue( "ui_browserSortKey", g_arenaservers.sortkey.curvalue );
		ArenaServers_Sort( g_arenaservers.sortkey.curvalue );
		ArenaServers_UpdateMenu();
		break;

	case ID_SHOW_FULL:
		trap_Cvar_SetValue( "ui_browserShowFull", g_arenaservers.showfull.curvalue );
		g_fullservers = g_arenaservers.showfull.curvalue;
		ArenaServers_UpdateMenu();
		break;

	case ID_SHOW_EMPTY:
		trap_Cvar_SetValue( "ui_browserShowEmpty", g_arenaservers.showempty.curvalue );
		g_emptyservers = g_arenaservers.showempty.curvalue;
		ArenaServers_UpdateMenu();
		break;

	case ID_LIST:
		if( event == QM_GOTFOCUS ) {
			ArenaServers_UpdatePicture();
		}
		break;

	case ID_SCROLL_UP:
		ScrollList_Key( &g_arenaservers.list, K_UPARROW );
		break;

	case ID_SCROLL_DOWN:
		ScrollList_Key( &g_arenaservers.list, K_DOWNARROW );
		break;

	case ID_BACK:
		ArenaServers_StopRefresh();
		ArenaServers_SaveChanges();
		UI_PopMenu();
		break;

	case ID_REFRESH:
		ArenaServers_StartRefresh();
		break;

	case ID_SPECIFY:
		UI_SpecifyServerMenu();
		break;

	case ID_CREATE:
		UI_StartServerMenu( qtrue );
		break;

	case ID_CONNECT:
		ArenaServers_Go();
		break;

	case ID_REMOVE:
		ArenaServers_Remove();
		ArenaServers_UpdateMenu();
		break;
	
	case ID_PUNKBUSTER:
		if (g_arenaservers.punkbuster.curvalue)			
		{
			UI_ConfirmMenu_Style( "Enable Punkbuster?",  UI_CENTER|UI_INVERSE|UI_SMALLFONT, (voidfunc_f)NULL, Punkbuster_ConfirmEnable );
		}
		else
		{
			UI_ConfirmMenu_Style( "Disable Punkbuster?", UI_CENTER|UI_INVERSE|UI_SMALLFONT, (voidfunc_f)NULL, Punkbuster_ConfirmDisable );
		}
		break;
	}
}