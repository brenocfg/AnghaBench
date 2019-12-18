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
struct TYPE_3__ {int reliableAcknowledge; int reliableSequence; int /*<<< orphan*/ ** reliableCommands; int /*<<< orphan*/  lastPacketTime; } ;
typedef  TYPE_1__ client_t ;
struct TYPE_4__ {int /*<<< orphan*/  time; TYPE_1__* clients; } ;

/* Variables and functions */
 int MAX_RELIABLE_COMMANDS ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ *,int) ; 
 int qfalse ; 
 int qtrue ; 
 TYPE_2__ svs ; 

int SV_BotGetConsoleMessage( int client, char *buf, int size )
{
	client_t	*cl;
	int			index;

	cl = &svs.clients[client];
	cl->lastPacketTime = svs.time;

	if ( cl->reliableAcknowledge == cl->reliableSequence ) {
		return qfalse;
	}

	cl->reliableAcknowledge++;
	index = cl->reliableAcknowledge & ( MAX_RELIABLE_COMMANDS - 1 );

	if ( !cl->reliableCommands[index][0] ) {
		return qfalse;
	}

	Q_strncpyz( buf, cl->reliableCommands[index], size );
	return qtrue;
}