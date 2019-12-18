#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int health; TYPE_3__* client; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_10__ {int* stats; } ;
struct TYPE_9__ {scalar_t__ sessionTeam; } ;
struct TYPE_11__ {TYPE_2__ ps; TYPE_1__ sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_GODMODE ; 
 int /*<<< orphan*/  MOD_SUICIDE ; 
 size_t STAT_HEALTH ; 
 scalar_t__ TEAM_SPECTATOR ; 
 int /*<<< orphan*/  player_die (TYPE_4__*,TYPE_4__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 

void Cmd_Kill_f( gentity_t *ent ) {
	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		return;
	}
	if (ent->health <= 0) {
		return;
	}
	ent->flags &= ~FL_GODMODE;
	ent->client->ps.stats[STAT_HEALTH] = ent->health = -999;
	player_die (ent, ent, ent, 100000, MOD_SUICIDE);
}