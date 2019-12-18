#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  remaining ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  netadr_t ;
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_4__ {int /*<<< orphan*/  string; } ;
struct TYPE_3__ {int /*<<< orphan*/  redirectAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 char* Cmd_Cmd () ; 
 int /*<<< orphan*/  Cmd_ExecuteString (char*) ; 
 int /*<<< orphan*/  Com_BeginRedirect (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_EndRedirect () ; 
 unsigned int Com_Milliseconds () ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  NET_AdrToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_strcat (char*,int,char*) ; 
 int /*<<< orphan*/  SV_FlushRedirect ; 
 int SV_OUTPUTBUF_LENGTH ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 TYPE_2__* sv_rconPassword ; 
 TYPE_1__ svs ; 

void SVC_RemoteCommand( netadr_t from, msg_t *msg ) {
	qboolean	valid;
	unsigned int time;
	char		remaining[1024];
	// TTimo - scaled down to accumulate, but not overflow anything network wise, print wise etc.
	// (OOB messages are the bottleneck here)
#define SV_OUTPUTBUF_LENGTH (1024 - 16)
	char		sv_outputbuf[SV_OUTPUTBUF_LENGTH];
	static unsigned int lasttime = 0;
	char *cmd_aux;

	// TTimo - https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=534
	time = Com_Milliseconds();
	if (time<(lasttime+500)) {
		return;
	}
	lasttime = time;

	if ( !strlen( sv_rconPassword->string ) ||
		strcmp (Cmd_Argv(1), sv_rconPassword->string) ) {
		valid = qfalse;
		Com_Printf ("Bad rcon from %s:\n%s\n", NET_AdrToString (from), Cmd_Argv(2) );
	} else {
		valid = qtrue;
		Com_Printf ("Rcon from %s:\n%s\n", NET_AdrToString (from), Cmd_Argv(2) );
	}

	// start redirecting all print outputs to the packet
	svs.redirectAddress = from;
	Com_BeginRedirect (sv_outputbuf, SV_OUTPUTBUF_LENGTH, SV_FlushRedirect);

	if ( !strlen( sv_rconPassword->string ) ) {
		Com_Printf ("No rconpassword set on the server.\n");
	} else if ( !valid ) {
		Com_Printf ("Bad rconpassword.\n");
	} else {
		remaining[0] = 0;
		
		// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=543
		// get the command directly, "rcon <pass> <command>" to avoid quoting issues
		// extract the command by walking
		// since the cmd formatting can fuckup (amount of spaces), using a dumb step by step parsing
		cmd_aux = Cmd_Cmd();
		cmd_aux+=4;
		while(cmd_aux[0]==' ')
			cmd_aux++;
		while(cmd_aux[0] && cmd_aux[0]!=' ') // password
			cmd_aux++;
		while(cmd_aux[0]==' ')
			cmd_aux++;
		
		Q_strcat( remaining, sizeof(remaining), cmd_aux);
		
		Cmd_ExecuteString (remaining);

	}

	Com_EndRedirect ();
}