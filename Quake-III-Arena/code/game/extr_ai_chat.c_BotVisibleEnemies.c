#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int client; scalar_t__ entitynum; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  eye; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_10__ {scalar_t__ number; int /*<<< orphan*/  valid; } ;
typedef  TYPE_2__ aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_2__*) ; 
 float BotEntityVisible (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ BotSameTeam (TYPE_1__*,int) ; 
 scalar_t__ EntityIsDead (TYPE_2__*) ; 
 scalar_t__ EntityIsInvisible (TYPE_2__*) ; 
 int /*<<< orphan*/  EntityIsShooting (TYPE_2__*) ; 
 int MAX_CLIENTS ; 
 int qfalse ; 
 int qtrue ; 

int BotVisibleEnemies(bot_state_t *bs) {
	float vis;
	int i;
	aas_entityinfo_t entinfo;

	for (i = 0; i < MAX_CLIENTS; i++) {

		if (i == bs->client) continue;
		//
		BotEntityInfo(i, &entinfo);
		//
		if (!entinfo.valid) continue;
		//if the enemy isn't dead and the enemy isn't the bot self
		if (EntityIsDead(&entinfo) || entinfo.number == bs->entitynum) continue;
		//if the enemy is invisible and not shooting
		if (EntityIsInvisible(&entinfo) && !EntityIsShooting(&entinfo)) {
			continue;
		}
		//if on the same team
		if (BotSameTeam(bs, i)) continue;
		//check if the enemy is visible
		vis = BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, i);
		if (vis > 0) return qtrue;
	}
	return qfalse;
}