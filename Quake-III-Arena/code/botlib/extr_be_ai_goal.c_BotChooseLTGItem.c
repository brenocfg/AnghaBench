#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_13__ {int flags; size_t iteminfo; float weight; int /*<<< orphan*/  number; scalar_t__ timeout; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  goalareanum; int /*<<< orphan*/  goalorigin; struct TYPE_13__* next; } ;
typedef  TYPE_1__ levelitem_t ;
struct TYPE_14__ {size_t number; float respawntime; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_2__ iteminfo_t ;
struct TYPE_15__ {TYPE_2__* iteminfo; } ;
typedef  TYPE_3__ itemconfig_t ;
struct TYPE_16__ {int lastreachabilityarea; int* itemweightindex; int /*<<< orphan*/  itemweightconfig; int /*<<< orphan*/  client; } ;
typedef  TYPE_4__ bot_goalstate_t ;
struct TYPE_17__ {int /*<<< orphan*/  iteminfo; int /*<<< orphan*/  flags; int /*<<< orphan*/  number; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  areanum; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  origin; } ;
typedef  TYPE_5__ bot_goal_t ;
struct TYPE_18__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AreaReachability (int) ; 
 int AAS_AreaTravelTimeToGoalArea (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 float AVOID_DEFAULT_TIME ; 
 float AVOID_DROPPED_TIME ; 
 float AVOID_MINIMUM_TIME ; 
 int /*<<< orphan*/  BotAddToAvoidGoals (TYPE_4__*,int /*<<< orphan*/ ,float) ; 
 float BotAvoidGoalTime (int,int /*<<< orphan*/ ) ; 
 TYPE_4__* BotGoalStateFromHandle (int) ; 
 int /*<<< orphan*/  BotPushGoal (int,TYPE_5__*) ; 
 int BotReachabilityArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 float FuzzyWeight (int*,int /*<<< orphan*/ ,int) ; 
 float FuzzyWeightUndecided (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFL_DROPPED ; 
 int /*<<< orphan*/  GFL_ITEM ; 
 int /*<<< orphan*/  GFL_ROAM ; 
 scalar_t__ GT_SINGLE_PLAYER ; 
 scalar_t__ GT_TEAM ; 
 int IFL_NOTBOT ; 
 int IFL_NOTFREE ; 
 int IFL_NOTSINGLE ; 
 int IFL_NOTTEAM ; 
 int IFL_ROAM ; 
 float TRAVELTIME_SCALE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* droppedweight ; 
 scalar_t__ g_gametype ; 
 TYPE_3__* itemconfig ; 
 TYPE_1__* levelitems ; 
 int qfalse ; 
 int qtrue ; 

int BotChooseLTGItem(int goalstate, vec3_t origin, int *inventory, int travelflags)
{
	int areanum, t, weightnum;
	float weight, bestweight, avoidtime;
	iteminfo_t *iteminfo;
	itemconfig_t *ic;
	levelitem_t *li, *bestitem;
	bot_goal_t goal;
	bot_goalstate_t *gs;

	gs = BotGoalStateFromHandle(goalstate);
	if (!gs)
		return qfalse;
	if (!gs->itemweightconfig)
		return qfalse;
	//get the area the bot is in
	areanum = BotReachabilityArea(origin, gs->client);
	//if the bot is in solid or if the area the bot is in has no reachability links
	if (!areanum || !AAS_AreaReachability(areanum))
	{
		//use the last valid area the bot was in
		areanum = gs->lastreachabilityarea;
	} //end if
	//remember the last area with reachabilities the bot was in
	gs->lastreachabilityarea = areanum;
	//if still in solid
	if (!areanum)
		return qfalse;
	//the item configuration
	ic = itemconfig;
	if (!itemconfig)
		return qfalse;
	//best weight and item so far
	bestweight = 0;
	bestitem = NULL;
	Com_Memset(&goal, 0, sizeof(bot_goal_t));
	//go through the items in the level
	for (li = levelitems; li; li = li->next)
	{
		if (g_gametype == GT_SINGLE_PLAYER) {
			if (li->flags & IFL_NOTSINGLE)
				continue;
		}
		else if (g_gametype >= GT_TEAM) {
			if (li->flags & IFL_NOTTEAM)
				continue;
		}
		else {
			if (li->flags & IFL_NOTFREE)
				continue;
		}
		if (li->flags & IFL_NOTBOT)
			continue;
		//if the item is not in a possible goal area
		if (!li->goalareanum)
			continue;
		//FIXME: is this a good thing? added this for items that never spawned into the game (f.i. CTF flags in obelisk)
		if (!li->entitynum && !(li->flags & IFL_ROAM))
			continue;
		//get the fuzzy weight function for this item
		iteminfo = &ic->iteminfo[li->iteminfo];
		weightnum = gs->itemweightindex[iteminfo->number];
		if (weightnum < 0)
			continue;

#ifdef UNDECIDEDFUZZY
		weight = FuzzyWeightUndecided(inventory, gs->itemweightconfig, weightnum);
#else
		weight = FuzzyWeight(inventory, gs->itemweightconfig, weightnum);
#endif //UNDECIDEDFUZZY
#ifdef DROPPEDWEIGHT
		//HACK: to make dropped items more attractive
		if (li->timeout)
			weight += droppedweight->value;
#endif //DROPPEDWEIGHT
		//use weight scale for item_botroam
		if (li->flags & IFL_ROAM) weight *= li->weight;
		//
		if (weight > 0)
		{
			//get the travel time towards the goal area
			t = AAS_AreaTravelTimeToGoalArea(areanum, origin, li->goalareanum, travelflags);
			//if the goal is reachable
			if (t > 0)
			{
				//if this item won't respawn before we get there
				avoidtime = BotAvoidGoalTime(goalstate, li->number);
				if (avoidtime - t * 0.009 > 0)
					continue;
				//
				weight /= (float) t * TRAVELTIME_SCALE;
				//
				if (weight > bestweight)
				{
					bestweight = weight;
					bestitem = li;
				} //end if
			} //end if
		} //end if
	} //end for
	//if no goal item found
	if (!bestitem)
	{
		/*
		//if not in lava or slime
		if (!AAS_AreaLava(areanum) && !AAS_AreaSlime(areanum))
		{
			if (AAS_RandomGoalArea(areanum, travelflags, &goal.areanum, goal.origin))
			{
				VectorSet(goal.mins, -15, -15, -15);
				VectorSet(goal.maxs, 15, 15, 15);
				goal.entitynum = 0;
				goal.number = 0;
				goal.flags = GFL_ROAM;
				goal.iteminfo = 0;
				//push the goal on the stack
				BotPushGoal(goalstate, &goal);
				//
#ifdef DEBUG
				botimport.Print(PRT_MESSAGE, "chosen roam goal area %d\n", goal.areanum);
#endif //DEBUG
				return qtrue;
			} //end if
		} //end if
		*/
		return qfalse;
	} //end if
	//create a bot goal for this item
	iteminfo = &ic->iteminfo[bestitem->iteminfo];
	VectorCopy(bestitem->goalorigin, goal.origin);
	VectorCopy(iteminfo->mins, goal.mins);
	VectorCopy(iteminfo->maxs, goal.maxs);
	goal.areanum = bestitem->goalareanum;
	goal.entitynum = bestitem->entitynum;
	goal.number = bestitem->number;
	goal.flags = GFL_ITEM;
	if (bestitem->timeout)
		goal.flags |= GFL_DROPPED;
	if (bestitem->flags & IFL_ROAM)
		goal.flags |= GFL_ROAM;
	goal.iteminfo = bestitem->iteminfo;
	//if it's a dropped item
	if (bestitem->timeout)
	{
		avoidtime = AVOID_DROPPED_TIME;
	} //end if
	else
	{
		avoidtime = iteminfo->respawntime;
		if (!avoidtime)
			avoidtime = AVOID_DEFAULT_TIME;
		if (avoidtime < AVOID_MINIMUM_TIME)
			avoidtime = AVOID_MINIMUM_TIME;
	} //end else
	//add the chosen goal to the goals to avoid for a while
	BotAddToAvoidGoals(gs, bestitem->number, avoidtime);
	//push the goal on the stack
	BotPushGoal(goalstate, &goal);
	//
	return qtrue;
}