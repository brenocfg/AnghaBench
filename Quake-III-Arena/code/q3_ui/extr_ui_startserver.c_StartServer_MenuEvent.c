#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; } ;
typedef  TYPE_2__ menucommon_s ;
struct TYPE_4__ {size_t curvalue; } ;
struct TYPE_6__ {int /*<<< orphan*/  multiplayer; TYPE_1__ gametype; int /*<<< orphan*/  page; int /*<<< orphan*/  maxpages; } ;

/* Variables and functions */
#define  ID_NEXTPAGE 131 
#define  ID_PREVPAGE 130 
#define  ID_STARTSERVERBACK 129 
#define  ID_STARTSERVERNEXT 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  StartServer_Update () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_ServerOptionsMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gametype_remap ; 
 TYPE_3__ s_startserver ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void StartServer_MenuEvent( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_PREVPAGE:
		if( s_startserver.page > 0 ) {
			s_startserver.page--;
			StartServer_Update();
		}
		break;

	case ID_NEXTPAGE:
		if( s_startserver.page < s_startserver.maxpages - 1 ) {
			s_startserver.page++;
			StartServer_Update();
		}
		break;

	case ID_STARTSERVERNEXT:
		trap_Cvar_SetValue( "g_gameType", gametype_remap[s_startserver.gametype.curvalue] );
		UI_ServerOptionsMenu( s_startserver.multiplayer );
		break;

	case ID_STARTSERVERBACK:
		UI_PopMenu();
		break;
	}
}