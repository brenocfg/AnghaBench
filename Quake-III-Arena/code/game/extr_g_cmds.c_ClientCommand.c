#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ gentity_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_29__ {scalar_t__ intermissiontime; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd_CallTeamVote_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_CallVote_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_FollowCycle_f (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Cmd_Follow_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_GameCommand_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_Give_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_God_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_Kill_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_LevelShot_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_Noclip_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_Notarget_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_Say_f (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_Score_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_SetViewpos_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_Stats_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_TeamTask_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_TeamVote_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_Team_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_Tell_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_VoiceTaunt_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_VoiceTell_f (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_Voice_f (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_Vote_f (TYPE_1__*) ; 
 int /*<<< orphan*/  Cmd_Where_f (TYPE_1__*) ; 
 int MAX_TOKEN_CHARS ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  SAY_ALL ; 
 int /*<<< orphan*/  SAY_TEAM ; 
 TYPE_1__* g_entities ; 
 TYPE_2__ level ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Argv (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_SendServerCommand (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char*) ; 

void ClientCommand( int clientNum ) {
	gentity_t *ent;
	char	cmd[MAX_TOKEN_CHARS];

	ent = g_entities + clientNum;
	if ( !ent->client ) {
		return;		// not fully in game yet
	}


	trap_Argv( 0, cmd, sizeof( cmd ) );

	if (Q_stricmp (cmd, "say") == 0) {
		Cmd_Say_f (ent, SAY_ALL, qfalse);
		return;
	}
	if (Q_stricmp (cmd, "say_team") == 0) {
		Cmd_Say_f (ent, SAY_TEAM, qfalse);
		return;
	}
	if (Q_stricmp (cmd, "tell") == 0) {
		Cmd_Tell_f ( ent );
		return;
	}
	if (Q_stricmp (cmd, "vsay") == 0) {
		Cmd_Voice_f (ent, SAY_ALL, qfalse, qfalse);
		return;
	}
	if (Q_stricmp (cmd, "vsay_team") == 0) {
		Cmd_Voice_f (ent, SAY_TEAM, qfalse, qfalse);
		return;
	}
	if (Q_stricmp (cmd, "vtell") == 0) {
		Cmd_VoiceTell_f ( ent, qfalse );
		return;
	}
	if (Q_stricmp (cmd, "vosay") == 0) {
		Cmd_Voice_f (ent, SAY_ALL, qfalse, qtrue);
		return;
	}
	if (Q_stricmp (cmd, "vosay_team") == 0) {
		Cmd_Voice_f (ent, SAY_TEAM, qfalse, qtrue);
		return;
	}
	if (Q_stricmp (cmd, "votell") == 0) {
		Cmd_VoiceTell_f ( ent, qtrue );
		return;
	}
	if (Q_stricmp (cmd, "vtaunt") == 0) {
		Cmd_VoiceTaunt_f ( ent );
		return;
	}
	if (Q_stricmp (cmd, "score") == 0) {
		Cmd_Score_f (ent);
		return;
	}

	// ignore all other commands when at intermission
	if (level.intermissiontime) {
		Cmd_Say_f (ent, qfalse, qtrue);
		return;
	}

	if (Q_stricmp (cmd, "give") == 0)
		Cmd_Give_f (ent);
	else if (Q_stricmp (cmd, "god") == 0)
		Cmd_God_f (ent);
	else if (Q_stricmp (cmd, "notarget") == 0)
		Cmd_Notarget_f (ent);
	else if (Q_stricmp (cmd, "noclip") == 0)
		Cmd_Noclip_f (ent);
	else if (Q_stricmp (cmd, "kill") == 0)
		Cmd_Kill_f (ent);
	else if (Q_stricmp (cmd, "teamtask") == 0)
		Cmd_TeamTask_f (ent);
	else if (Q_stricmp (cmd, "levelshot") == 0)
		Cmd_LevelShot_f (ent);
	else if (Q_stricmp (cmd, "follow") == 0)
		Cmd_Follow_f (ent);
	else if (Q_stricmp (cmd, "follownext") == 0)
		Cmd_FollowCycle_f (ent, 1);
	else if (Q_stricmp (cmd, "followprev") == 0)
		Cmd_FollowCycle_f (ent, -1);
	else if (Q_stricmp (cmd, "team") == 0)
		Cmd_Team_f (ent);
	else if (Q_stricmp (cmd, "where") == 0)
		Cmd_Where_f (ent);
	else if (Q_stricmp (cmd, "callvote") == 0)
		Cmd_CallVote_f (ent);
	else if (Q_stricmp (cmd, "vote") == 0)
		Cmd_Vote_f (ent);
	else if (Q_stricmp (cmd, "callteamvote") == 0)
		Cmd_CallTeamVote_f (ent);
	else if (Q_stricmp (cmd, "teamvote") == 0)
		Cmd_TeamVote_f (ent);
	else if (Q_stricmp (cmd, "gc") == 0)
		Cmd_GameCommand_f( ent );
	else if (Q_stricmp (cmd, "setviewpos") == 0)
		Cmd_SetViewpos_f( ent );
	else if (Q_stricmp (cmd, "stats") == 0)
		Cmd_Stats_f( ent );
	else
		trap_SendServerCommand( clientNum, va("print \"unknown cmd %s\n\"", cmd ) );
}