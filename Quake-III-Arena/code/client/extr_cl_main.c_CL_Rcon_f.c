#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ port; } ;
typedef  TYPE_2__ netadr_t ;
struct TYPE_9__ {TYPE_2__ remoteAddress; } ;
struct TYPE_14__ {TYPE_1__ netchan; } ;
struct TYPE_13__ {scalar_t__ state; } ;
struct TYPE_12__ {char* string; } ;
struct TYPE_11__ {char* string; } ;

/* Variables and functions */
 scalar_t__ BigShort (int /*<<< orphan*/ ) ; 
 scalar_t__ CA_CONNECTED ; 
 char* Cmd_Cmd () ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  NET_SendPacket (int /*<<< orphan*/ ,scalar_t__,char*,TYPE_2__) ; 
 int /*<<< orphan*/  NET_StringToAdr (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  NS_CLIENT ; 
 int /*<<< orphan*/  PORT_SERVER ; 
 TYPE_6__ clc ; 
 TYPE_5__ cls ; 
 TYPE_4__* rconAddress ; 
 TYPE_3__* rcon_client_password ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void CL_Rcon_f( void ) {
	char	message[1024];
	netadr_t	to;

	if ( !rcon_client_password->string ) {
		Com_Printf ("You must set 'rconpassword' before\n"
					"issuing an rcon command.\n");
		return;
	}

	message[0] = -1;
	message[1] = -1;
	message[2] = -1;
	message[3] = -1;
	message[4] = 0;

	strcat (message, "rcon ");

	strcat (message, rcon_client_password->string);
	strcat (message, " ");

	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=543
	strcat (message, Cmd_Cmd()+5);

	if ( cls.state >= CA_CONNECTED ) {
		to = clc.netchan.remoteAddress;
	} else {
		if (!strlen(rconAddress->string)) {
			Com_Printf ("You must either be connected,\n"
						"or set the 'rconAddress' cvar\n"
						"to issue rcon commands\n");

			return;
		}
		NET_StringToAdr (rconAddress->string, &to);
		if (to.port == 0) {
			to.port = BigShort (PORT_SERVER);
		}
	}
	
	NET_SendPacket (NS_CLIENT, strlen(message)+1, message, to);
}