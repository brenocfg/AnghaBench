#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  areanum; } ;
struct TYPE_7__ {int /*<<< orphan*/  inventory; int /*<<< orphan*/  origin; int /*<<< orphan*/  gs; TYPE_1__ teamgoal; int /*<<< orphan*/  areanum; } ;
typedef  TYPE_2__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_goal_t ;

/* Variables and functions */
 scalar_t__ BotCTFCarryingFlag (TYPE_2__*) ; 
 scalar_t__ BotGoForAir (TYPE_2__*,int,int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  TFL_DEFAULT ; 
 int qtrue ; 
 int trap_AAS_AreaTravelTimeToGoalArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int trap_BotChooseNBGItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,float) ; 

int BotNearbyGoal(bot_state_t *bs, int tfl, bot_goal_t *ltg, float range) {
	int ret;

	//check if the bot should go for air
	if (BotGoForAir(bs, tfl, ltg, range)) return qtrue;
	//if the bot is carrying the enemy flag
	if (BotCTFCarryingFlag(bs)) {
		//if the bot is just a few secs away from the base 
		if (trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin,
				bs->teamgoal.areanum, TFL_DEFAULT) < 300) {
			//make the range really small
			range = 50;
		}
	}
	//
	ret = trap_BotChooseNBGItem(bs->gs, bs->origin, bs->inventory, tfl, ltg, range);
	/*
	if (ret)
	{
		char buf[128];
		//get the goal at the top of the stack
		trap_BotGetTopGoal(bs->gs, &goal);
		trap_BotGoalName(goal.number, buf, sizeof(buf));
		BotAI_Print(PRT_MESSAGE, "%1.1f: new nearby goal %s\n", FloatTime(), buf);
	}
    */
	return ret;
}