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
struct TYPE_7__ {scalar_t__* origin; scalar_t__ areanum; int lastair_time; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  eye; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  gs; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_8__ {int flags; scalar_t__ areanum; scalar_t__* origin; scalar_t__* mins; scalar_t__* maxs; int /*<<< orphan*/  number; } ;
typedef  TYPE_2__ bot_goal_t ;

/* Variables and functions */
 int FloatTime () ; 
 int GFL_AIR ; 
 int GFL_DROPPED ; 
 int GFL_ITEM ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_AAS_Swimming (scalar_t__*) ; 
 scalar_t__ trap_BotItemGoalInVisButNotVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  trap_BotSetAvoidGoalTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ trap_BotTouchingGoal (scalar_t__*,TYPE_2__*) ; 

int BotReachedGoal(bot_state_t *bs, bot_goal_t *goal) {
	if (goal->flags & GFL_ITEM) {
		//if touching the goal
		if (trap_BotTouchingGoal(bs->origin, goal)) {
			if (!(goal->flags & GFL_DROPPED)) {
				trap_BotSetAvoidGoalTime(bs->gs, goal->number, -1);
			}
			return qtrue;
		}
		//if the goal isn't there
		if (trap_BotItemGoalInVisButNotVisible(bs->entitynum, bs->eye, bs->viewangles, goal)) {
			/*
			float avoidtime;
			int t;

			avoidtime = trap_BotAvoidGoalTime(bs->gs, goal->number);
			if (avoidtime > 0) {
				t = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, goal->areanum, bs->tfl);
				if ((float) t * 0.009 < avoidtime)
					return qtrue;
			}
			*/
			return qtrue;
		}
		//if in the goal area and below or above the goal and not swimming
		if (bs->areanum == goal->areanum) {
			if (bs->origin[0] > goal->origin[0] + goal->mins[0] && bs->origin[0] < goal->origin[0] + goal->maxs[0]) {
				if (bs->origin[1] > goal->origin[1] + goal->mins[1] && bs->origin[1] < goal->origin[1] + goal->maxs[1]) {
					if (!trap_AAS_Swimming(bs->origin)) {
						return qtrue;
					}
				}
			}
		}
	}
	else if (goal->flags & GFL_AIR) {
		//if touching the goal
		if (trap_BotTouchingGoal(bs->origin, goal)) return qtrue;
		//if the bot got air
		if (bs->lastair_time > FloatTime() - 1) return qtrue;
	}
	else {
		//if touching the goal
		if (trap_BotTouchingGoal(bs->origin, goal)) return qtrue;
	}
	return qfalse;
}