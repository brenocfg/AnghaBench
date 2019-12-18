#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_8__ {int lastreachnum; int lastareanum; int /*<<< orphan*/  avoidreachtries; int /*<<< orphan*/  avoidreachtimes; int /*<<< orphan*/  avoidreach; int /*<<< orphan*/  lastgoalareanum; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_9__ {int areanum; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ bot_goal_t ;
struct TYPE_10__ {int traveltype; int areanum; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_3__ aas_reachability_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ReachabilityFromNum (int,TYPE_3__*) ; 
 scalar_t__ BotAddToTarget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float*,int /*<<< orphan*/ ) ; 
 int BotGetReachabilityToGoal (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* BotMoveStateFromHandle (int) ; 
 int TRAVELTYPE_MASK ; 
 int TRAVEL_BFGJUMP ; 
 int TRAVEL_ELEVATOR ; 
 int TRAVEL_FUNCBOB ; 
 int TRAVEL_JUMPPAD ; 
 int TRAVEL_ROCKETJUMP ; 
 int TRAVEL_TELEPORT ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 

int BotMovementViewTarget(int movestate, bot_goal_t *goal, int travelflags, float lookahead, vec3_t target)
{
	aas_reachability_t reach;
	int reachnum, lastareanum;
	bot_movestate_t *ms;
	vec3_t end;
	float dist;

	ms = BotMoveStateFromHandle(movestate);
	if (!ms) return qfalse;
	reachnum = 0;
	//if the bot has no goal or no last reachability
	if (!ms->lastreachnum || !goal) return qfalse;

	reachnum = ms->lastreachnum;
	VectorCopy(ms->origin, end);
	lastareanum = ms->lastareanum;
	dist = 0;
	while(reachnum && dist < lookahead)
	{
		AAS_ReachabilityFromNum(reachnum, &reach);
		if (BotAddToTarget(end, reach.start, lookahead, &dist, target)) return qtrue;
		//never look beyond teleporters
		if ((reach.traveltype & TRAVELTYPE_MASK) == TRAVEL_TELEPORT) return qtrue;
		//never look beyond the weapon jump point
		if ((reach.traveltype & TRAVELTYPE_MASK) == TRAVEL_ROCKETJUMP) return qtrue;
		if ((reach.traveltype & TRAVELTYPE_MASK) == TRAVEL_BFGJUMP) return qtrue;
		//don't add jump pad distances
		if ((reach.traveltype & TRAVELTYPE_MASK) != TRAVEL_JUMPPAD &&
			(reach.traveltype & TRAVELTYPE_MASK) != TRAVEL_ELEVATOR &&
			(reach.traveltype & TRAVELTYPE_MASK) != TRAVEL_FUNCBOB)
		{
			if (BotAddToTarget(reach.start, reach.end, lookahead, &dist, target)) return qtrue;
		} //end if
		reachnum = BotGetReachabilityToGoal(reach.end, reach.areanum,
						ms->lastgoalareanum, lastareanum,
							ms->avoidreach, ms->avoidreachtimes, ms->avoidreachtries,
									goal, travelflags, travelflags, NULL, 0, NULL);
		VectorCopy(reach.end, end);
		lastareanum = reach.areanum;
		if (lastareanum == goal->areanum)
		{
			BotAddToTarget(reach.end, goal->origin, lookahead, &dist, target);
			return qtrue;
		} //end if
	} //end while
	//
	return qfalse;
}