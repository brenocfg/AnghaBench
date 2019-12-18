#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int sessionTeam; } ;
struct TYPE_9__ {size_t clientNum; } ;
struct TYPE_11__ {scalar_t__ connected; } ;
struct TYPE_13__ {TYPE_2__ sess; TYPE_1__ ps; TYPE_3__ pers; } ;
typedef  TYPE_5__ gclient_t ;
struct TYPE_12__ {int svFlags; } ;
struct TYPE_16__ {TYPE_4__ r; } ;
struct TYPE_15__ {int integer; } ;
struct TYPE_14__ {TYPE_5__* clients; } ;

/* Variables and functions */
 scalar_t__ CON_CONNECTED ; 
 int SVF_BOT ; 
 TYPE_8__* g_entities ; 
 TYPE_7__ g_maxclients ; 
 TYPE_6__ level ; 

int G_CountHumanPlayers( int team ) {
	int i, num;
	gclient_t	*cl;

	num = 0;
	for ( i=0 ; i< g_maxclients.integer ; i++ ) {
		cl = level.clients + i;
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( g_entities[cl->ps.clientNum].r.svFlags & SVF_BOT ) {
			continue;
		}
		if ( team >= 0 && cl->sess.sessionTeam != team ) {
			continue;
		}
		num++;
	}
	return num;
}