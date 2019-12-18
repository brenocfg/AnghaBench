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

/* Variables and functions */
#define  BOTAI_START_FRAME 138 
 int BotAIStartFrame (int) ; 
 int /*<<< orphan*/  ClientBegin (int) ; 
 int /*<<< orphan*/  ClientCommand (int) ; 
 scalar_t__ ClientConnect (int,int,int) ; 
 int /*<<< orphan*/  ClientDisconnect (int) ; 
 int /*<<< orphan*/  ClientThink (int) ; 
 int /*<<< orphan*/  ClientUserinfoChanged (int) ; 
 int ConsoleCommand () ; 
#define  GAME_CLIENT_BEGIN 137 
#define  GAME_CLIENT_COMMAND 136 
#define  GAME_CLIENT_CONNECT 135 
#define  GAME_CLIENT_DISCONNECT 134 
#define  GAME_CLIENT_THINK 133 
#define  GAME_CLIENT_USERINFO_CHANGED 132 
#define  GAME_CONSOLE_COMMAND 131 
#define  GAME_INIT 130 
#define  GAME_RUN_FRAME 129 
#define  GAME_SHUTDOWN 128 
 int /*<<< orphan*/  G_InitGame (int,int,int) ; 
 int /*<<< orphan*/  G_RunFrame (int) ; 
 int /*<<< orphan*/  G_ShutdownGame (int) ; 

int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11  ) {
	switch ( command ) {
	case GAME_INIT:
		G_InitGame( arg0, arg1, arg2 );
		return 0;
	case GAME_SHUTDOWN:
		G_ShutdownGame( arg0 );
		return 0;
	case GAME_CLIENT_CONNECT:
		return (int)ClientConnect( arg0, arg1, arg2 );
	case GAME_CLIENT_THINK:
		ClientThink( arg0 );
		return 0;
	case GAME_CLIENT_USERINFO_CHANGED:
		ClientUserinfoChanged( arg0 );
		return 0;
	case GAME_CLIENT_DISCONNECT:
		ClientDisconnect( arg0 );
		return 0;
	case GAME_CLIENT_BEGIN:
		ClientBegin( arg0 );
		return 0;
	case GAME_CLIENT_COMMAND:
		ClientCommand( arg0 );
		return 0;
	case GAME_RUN_FRAME:
		G_RunFrame( arg0 );
		return 0;
	case GAME_CONSOLE_COMMAND:
		return ConsoleCommand();
	case BOTAI_START_FRAME:
		return BotAIStartFrame( arg0 );
	}

	return -1;
}