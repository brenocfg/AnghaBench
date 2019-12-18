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
typedef  int /*<<< orphan*/  str ;
struct TYPE_2__ {scalar_t__ warmupTime; int maxclients; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RankClientDisconnect (int) ; 
 int MAX_INFO_VALUE ; 
 int /*<<< orphan*/  QGR_KEY_DEDICATED ; 
 int /*<<< orphan*/  QGR_KEY_FRAGLIMIT ; 
 int /*<<< orphan*/  QGR_KEY_GAMETYPE ; 
 int /*<<< orphan*/  QGR_KEY_HOSTNAME ; 
 int /*<<< orphan*/  QGR_KEY_MAP ; 
 int /*<<< orphan*/  QGR_KEY_MAXCLIENTS ; 
 int /*<<< orphan*/  QGR_KEY_MAXPING ; 
 int /*<<< orphan*/  QGR_KEY_MAXRATE ; 
 int /*<<< orphan*/  QGR_KEY_MINPING ; 
 int /*<<< orphan*/  QGR_KEY_MOD ; 
 int /*<<< orphan*/  QGR_KEY_TIMELIMIT ; 
 int /*<<< orphan*/  QGR_KEY_VERSION ; 
 scalar_t__ QGR_STATUS_ACTIVE ; 
 TYPE_1__ level ; 
 int trap_Cvar_VariableIntegerValue (char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 int /*<<< orphan*/  trap_RankReportInt (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_RankReportStr (int,int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ trap_RankUserStatus (int) ; 

void G_RankGameOver( void )
{
	int		i;
	char	str[MAX_INFO_VALUE];
	int		num;
	
	if( level.warmupTime != 0 )
	{
		// no reports during warmup period
		return;
	}
	
	for( i = 0; i < level.maxclients; i++ )
	{
		if( trap_RankUserStatus( i ) == QGR_STATUS_ACTIVE )
		{
			G_RankClientDisconnect( i );
		}
	}
	
	// hostname
	trap_Cvar_VariableStringBuffer( "sv_hostname", str, sizeof(str) );
	trap_RankReportStr( -1, -1, QGR_KEY_HOSTNAME, str );

	// map
	trap_Cvar_VariableStringBuffer( "mapname", str, sizeof(str) );
	trap_RankReportStr( -1, -1, QGR_KEY_MAP, str );

	// mod
	trap_Cvar_VariableStringBuffer( "fs_game", str, sizeof(str) );
	trap_RankReportStr( -1, -1, QGR_KEY_MOD, str );

	// gametype
	num = trap_Cvar_VariableIntegerValue("g_gametype");
	trap_RankReportInt( -1, -1, QGR_KEY_GAMETYPE, num, 0 );
	
	// fraglimit
	num = trap_Cvar_VariableIntegerValue("fraglimit");
	trap_RankReportInt( -1, -1, QGR_KEY_FRAGLIMIT, num, 0 );
	
	// timelimit
	num = trap_Cvar_VariableIntegerValue("timelimit");
	trap_RankReportInt( -1, -1, QGR_KEY_TIMELIMIT, num, 0 );

	// maxclients
	num = trap_Cvar_VariableIntegerValue("sv_maxclients");
	trap_RankReportInt( -1, -1, QGR_KEY_MAXCLIENTS, num, 0 );

	// maxrate
	num = trap_Cvar_VariableIntegerValue("sv_maxRate");
	trap_RankReportInt( -1, -1, QGR_KEY_MAXRATE, num, 0 );

	// minping
	num = trap_Cvar_VariableIntegerValue("sv_minPing");
	trap_RankReportInt( -1, -1, QGR_KEY_MINPING, num, 0 );

	// maxping
	num = trap_Cvar_VariableIntegerValue("sv_maxPing");
	trap_RankReportInt( -1, -1, QGR_KEY_MAXPING, num, 0 );

	// dedicated
	num = trap_Cvar_VariableIntegerValue("dedicated");
	trap_RankReportInt( -1, -1, QGR_KEY_DEDICATED, num, 0 );

	// version
	trap_Cvar_VariableStringBuffer( "version", str, sizeof(str) );
	trap_RankReportStr( -1, -1, QGR_KEY_VERSION, str );
}