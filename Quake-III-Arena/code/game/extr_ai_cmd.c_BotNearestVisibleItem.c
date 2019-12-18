#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_10__ {double fraction; } ;
typedef  TYPE_1__ bsp_trace_t ;
struct TYPE_11__ {int /*<<< orphan*/  client; int /*<<< orphan*/  eye; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ bot_state_t ;
struct TYPE_12__ {int /*<<< orphan*/  origin; int /*<<< orphan*/  number; } ;
typedef  TYPE_3__ bot_goal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Trace (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SOLID ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int trap_BotGetLevelItemGoal (int,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  trap_BotGoalName (int /*<<< orphan*/ ,char*,int) ; 

float BotNearestVisibleItem(bot_state_t *bs, char *itemname, bot_goal_t *goal) {
	int i;
	char name[64];
	bot_goal_t tmpgoal;
	float dist, bestdist;
	vec3_t dir;
	bsp_trace_t trace;

	bestdist = 999999;
	i = -1;
	do {
		i = trap_BotGetLevelItemGoal(i, itemname, &tmpgoal);
		trap_BotGoalName(tmpgoal.number, name, sizeof(name));
		if (Q_stricmp(itemname, name) != 0)
			continue;
		VectorSubtract(tmpgoal.origin, bs->origin, dir);
		dist = VectorLength(dir);
		if (dist < bestdist) {
			//trace from start to end
			BotAI_Trace(&trace, bs->eye, NULL, NULL, tmpgoal.origin, bs->client, CONTENTS_SOLID|CONTENTS_PLAYERCLIP);
			if (trace.fraction >= 1.0) {
				bestdist = dist;
				memcpy(goal, &tmpgoal, sizeof(bot_goal_t));
			}
		}
	} while(i > 0);
	return bestdist;
}