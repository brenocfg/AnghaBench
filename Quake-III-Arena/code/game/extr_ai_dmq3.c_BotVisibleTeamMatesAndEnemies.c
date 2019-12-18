#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {int client; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  eye; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_8__ {int /*<<< orphan*/  origin; int /*<<< orphan*/  valid; } ;
typedef  TYPE_2__ aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_2__*) ; 
 float BotEntityVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ BotSameTeam (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EntityCarriesFlag (TYPE_2__*) ; 
 int MAX_CLIENTS ; 
 scalar_t__ Square (float) ; 
 scalar_t__ VectorLengthSquared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int maxclients ; 

void BotVisibleTeamMatesAndEnemies(bot_state_t *bs, int *teammates, int *enemies, float range) {
	int i;
	float vis;
	aas_entityinfo_t entinfo;
	vec3_t dir;

	if (teammates)
		*teammates = 0;
	if (enemies)
		*enemies = 0;
	for (i = 0; i < maxclients && i < MAX_CLIENTS; i++) {
		if (i == bs->client)
			continue;
		//
		BotEntityInfo(i, &entinfo);
		//if this player is active
		if (!entinfo.valid)
			continue;
		//if this player is carrying a flag
		if (!EntityCarriesFlag(&entinfo))
			continue;
		//if not within range
		VectorSubtract(entinfo.origin, bs->origin, dir);
		if (VectorLengthSquared(dir) > Square(range))
			continue;
		//if the flag carrier is not visible
		vis = BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, i);
		if (vis <= 0)
			continue;
		//if the flag carrier is on the same team
		if (BotSameTeam(bs, i)) {
			if (teammates)
				(*teammates)++;
		}
		else {
			if (enemies)
				(*enemies)++;
		}
	}
}