#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int svFlags; } ;
struct TYPE_14__ {TYPE_4__* client; TYPE_1__ r; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_16__ {int /*<<< orphan*/  integer; } ;
struct TYPE_15__ {int /*<<< orphan*/  time; } ;
struct TYPE_11__ {int /*<<< orphan*/  serverTime; } ;
struct TYPE_12__ {TYPE_2__ cmd; } ;
struct TYPE_13__ {TYPE_3__ pers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientThink_real (TYPE_5__*) ; 
 int SVF_BOT ; 
 TYPE_7__ g_synchronousClients ; 
 TYPE_6__ level ; 

void G_RunClient( gentity_t *ent ) {
	if ( !(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer ) {
		return;
	}
	ent->client->pers.cmd.serverTime = level.time;
	ClientThink_real( ent );
}