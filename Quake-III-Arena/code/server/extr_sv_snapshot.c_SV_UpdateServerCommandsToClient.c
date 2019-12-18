#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_3__ {int reliableAcknowledge; int reliableSequence; int reliableSent; int /*<<< orphan*/ * reliableCommands; } ;
typedef  TYPE_1__ client_t ;

/* Variables and functions */
 int MAX_RELIABLE_COMMANDS ; 
 int /*<<< orphan*/  MSG_WriteByte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_WriteLong (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSG_WriteString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_serverCommand ; 

void SV_UpdateServerCommandsToClient( client_t *client, msg_t *msg ) {
	int		i;

	// write any unacknowledged serverCommands
	for ( i = client->reliableAcknowledge + 1 ; i <= client->reliableSequence ; i++ ) {
		MSG_WriteByte( msg, svc_serverCommand );
		MSG_WriteLong( msg, i );
		MSG_WriteString( msg, client->reliableCommands[ i & (MAX_RELIABLE_COMMANDS-1) ] );
	}
	client->reliableSent = client->reliableSequence;
}