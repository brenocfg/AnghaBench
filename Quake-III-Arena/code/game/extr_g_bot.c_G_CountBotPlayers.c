#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int sessionTeam; } ;
struct TYPE_12__ {size_t clientNum; } ;
struct TYPE_10__ {scalar_t__ connected; } ;
struct TYPE_14__ {TYPE_4__ sess; TYPE_3__ ps; TYPE_1__ pers; } ;
typedef  TYPE_5__ gclient_t ;
struct TYPE_18__ {scalar_t__ spawnTime; } ;
struct TYPE_11__ {int svFlags; } ;
struct TYPE_17__ {TYPE_2__ r; } ;
struct TYPE_16__ {int integer; } ;
struct TYPE_15__ {scalar_t__ time; TYPE_5__* clients; } ;

/* Variables and functions */
 int BOT_SPAWN_QUEUE_DEPTH ; 
 scalar_t__ CON_CONNECTED ; 
 int SVF_BOT ; 
 TYPE_9__* botSpawnQueue ; 
 TYPE_8__* g_entities ; 
 TYPE_7__ g_maxclients ; 
 TYPE_6__ level ; 

int G_CountBotPlayers( int team ) {
	int i, n, num;
	gclient_t	*cl;

	num = 0;
	for ( i=0 ; i< g_maxclients.integer ; i++ ) {
		cl = level.clients + i;
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( !(g_entities[cl->ps.clientNum].r.svFlags & SVF_BOT) ) {
			continue;
		}
		if ( team >= 0 && cl->sess.sessionTeam != team ) {
			continue;
		}
		num++;
	}
	for( n = 0; n < BOT_SPAWN_QUEUE_DEPTH; n++ ) {
		if( !botSpawnQueue[n].spawnTime ) {
			continue;
		}
		if ( botSpawnQueue[n].spawnTime > level.time ) {
			continue;
		}
		num++;
	}
	return num;
}