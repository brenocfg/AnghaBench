#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  svFlags; } ;
struct TYPE_11__ {TYPE_4__* client; TYPE_1__ r; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_8__ {TYPE_5__* clientNum; int /*<<< orphan*/  pm_flags; void** persistant; } ;
struct TYPE_9__ {int /*<<< orphan*/  spectatorState; void* sessionTeam; } ;
struct TYPE_10__ {TYPE_2__ ps; TYPE_3__ sess; } ;

/* Variables and functions */
 size_t PERS_TEAM ; 
 int /*<<< orphan*/  PMF_FOLLOW ; 
 int /*<<< orphan*/  SPECTATOR_FREE ; 
 int /*<<< orphan*/  SVF_BOT ; 
 void* TEAM_SPECTATOR ; 
 int g_entities ; 

void StopFollowing( gentity_t *ent ) {
	ent->client->ps.persistant[ PERS_TEAM ] = TEAM_SPECTATOR;	
	ent->client->sess.sessionTeam = TEAM_SPECTATOR;	
	ent->client->sess.spectatorState = SPECTATOR_FREE;
	ent->client->ps.pm_flags &= ~PMF_FOLLOW;
	ent->r.svFlags &= ~SVF_BOT;
	ent->client->ps.clientNum = ent - g_entities;
}