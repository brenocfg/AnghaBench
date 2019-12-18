#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t tm_mon; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; } ;
typedef  TYPE_3__ qtime_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {scalar_t__ realTime; } ;
struct TYPE_7__ {scalar_t__ refreshtime; scalar_t__ numPlayersOnServers; scalar_t__ numDisplayServers; scalar_t__ nextDisplayRefresh; int /*<<< orphan*/  refreshActive; } ;
struct TYPE_11__ {TYPE_2__ uiDC; TYPE_1__ serverStatus; } ;
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_GLOBAL ; 
 int /*<<< orphan*/  AS_LOCAL ; 
 int /*<<< orphan*/  AS_MPLAYER ; 
 int /*<<< orphan*/  EXEC_NOW ; 
 int /*<<< orphan*/ * MonthAbbrev ; 
 char* UI_Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  UI_UpdatePendingPings () ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  trap_LAN_MarkServerVisible (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_LAN_ResetPings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_RealTime (TYPE_3__*) ; 
 TYPE_5__ uiInfo ; 
 TYPE_4__ ui_netSource ; 
 char* va (char*,int,...) ; 

__attribute__((used)) static void UI_StartServerRefresh(qboolean full)
{
	int		i;
	char	*ptr;

	qtime_t q;
	trap_RealTime(&q);
 	trap_Cvar_Set( va("ui_lastServerRefresh_%i", ui_netSource.integer), va("%s-%i, %i at %i:%i", MonthAbbrev[q.tm_mon],q.tm_mday, 1900+q.tm_year,q.tm_hour,q.tm_min));

	if (!full) {
		UI_UpdatePendingPings();
		return;
	}

	uiInfo.serverStatus.refreshActive = qtrue;
	uiInfo.serverStatus.nextDisplayRefresh = uiInfo.uiDC.realTime + 1000;
	// clear number of displayed servers
	uiInfo.serverStatus.numDisplayServers = 0;
	uiInfo.serverStatus.numPlayersOnServers = 0;
	// mark all servers as visible so we store ping updates for them
	trap_LAN_MarkServerVisible(ui_netSource.integer, -1, qtrue);
	// reset all the pings
	trap_LAN_ResetPings(ui_netSource.integer);
	//
	if( ui_netSource.integer == AS_LOCAL ) {
		trap_Cmd_ExecuteText( EXEC_NOW, "localservers\n" );
		uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 1000;
		return;
	}

	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 5000;
	if( ui_netSource.integer == AS_GLOBAL || ui_netSource.integer == AS_MPLAYER ) {
		if( ui_netSource.integer == AS_GLOBAL ) {
			i = 0;
		}
		else {
			i = 1;
		}

		ptr = UI_Cvar_VariableString("debug_protocol");
		if (strlen(ptr)) {
			trap_Cmd_ExecuteText( EXEC_NOW, va( "globalservers %d %s full empty\n", i, ptr));
		}
		else {
			trap_Cmd_ExecuteText( EXEC_NOW, va( "globalservers %d %d full empty\n", i, (int)trap_Cvar_VariableValue( "protocol" ) ) );
		}
	}
}