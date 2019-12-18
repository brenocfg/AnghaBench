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
struct TYPE_11__ {int svFlags; } ;
struct TYPE_12__ {TYPE_3__ r; TYPE_2__* client; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_14__ {int /*<<< orphan*/  integer; } ;
struct TYPE_13__ {int /*<<< orphan*/  time; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_10__ {int /*<<< orphan*/  lastCmdTime; TYPE_1__ pers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientThink_real (TYPE_4__*) ; 
 int SVF_BOT ; 
 TYPE_4__* g_entities ; 
 TYPE_6__ g_synchronousClients ; 
 TYPE_5__ level ; 
 int /*<<< orphan*/  trap_GetUsercmd (int,int /*<<< orphan*/ *) ; 

void ClientThink( int clientNum ) {
	gentity_t *ent;

	ent = g_entities + clientNum;
	trap_GetUsercmd( clientNum, &ent->client->pers.cmd );

	// mark the time we got info, so we can display the
	// phone jack if they don't get any for a while
	ent->client->lastCmdTime = level.time;

	if ( !(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer ) {
		ClientThink_real( ent );
	}
}