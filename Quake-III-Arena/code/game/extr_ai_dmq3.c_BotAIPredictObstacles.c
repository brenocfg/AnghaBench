#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int predictobstacles_time; TYPE_1__* activatestack; int /*<<< orphan*/  tfl; int /*<<< orphan*/  origin; int /*<<< orphan*/  areanum; int /*<<< orphan*/  predictobstacles_goalareanum; } ;
typedef  TYPE_3__ bot_state_t ;
struct TYPE_20__ {int /*<<< orphan*/  areanum; } ;
typedef  TYPE_4__ bot_goal_t ;
struct TYPE_18__ {int /*<<< orphan*/  entitynum; } ;
struct TYPE_21__ {TYPE_2__ goal; } ;
typedef  TYPE_5__ bot_activategoal_t ;
struct TYPE_22__ {int stopevent; int endcontents; int endtravelflags; } ;
typedef  TYPE_6__ aas_predictroute_t ;
struct TYPE_23__ {int /*<<< orphan*/  integer; } ;
struct TYPE_17__ {int /*<<< orphan*/  inuse; } ;

/* Variables and functions */
 int AREACONTENTS_MODELNUM ; 
 int AREACONTENTS_MODELNUMSHIFT ; 
 int AREACONTENTS_MOVER ; 
 int /*<<< orphan*/  BotEnableActivateGoalAreas (TYPE_5__*,int) ; 
 int BotGetActivateGoal (TYPE_3__*,int,TYPE_5__*) ; 
 int /*<<< orphan*/  BotGoForActivateGoal (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  BotIsGoingToActivateEntity (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int BotModelMinsMaxs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ET_MOVER ; 
 int FloatTime () ; 
 int RSE_ENTERCONTENTS ; 
 int RSE_USETRAVELTYPE ; 
 int TFL_BRIDGE ; 
 TYPE_8__ bot_predictobstacles ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_AAS_PredictRoute (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ) ; 

int BotAIPredictObstacles(bot_state_t *bs, bot_goal_t *goal) {
	int modelnum, entitynum, bspent;
	bot_activategoal_t activategoal;
	aas_predictroute_t route;

	if (!bot_predictobstacles.integer)
		return qfalse;

	// always predict when the goal change or at regular intervals
	if (bs->predictobstacles_goalareanum == goal->areanum &&
		bs->predictobstacles_time > FloatTime() - 6) {
		return qfalse;
	}
	bs->predictobstacles_goalareanum = goal->areanum;
	bs->predictobstacles_time = FloatTime();

	// predict at most 100 areas or 10 seconds ahead
	trap_AAS_PredictRoute(&route, bs->areanum, bs->origin,
							goal->areanum, bs->tfl, 100, 1000,
							RSE_USETRAVELTYPE|RSE_ENTERCONTENTS,
							AREACONTENTS_MOVER, TFL_BRIDGE, 0);
	// if bot has to travel through an area with a mover
	if (route.stopevent & RSE_ENTERCONTENTS) {
		// if the bot will run into a mover
		if (route.endcontents & AREACONTENTS_MOVER) {
			//NOTE: this only works with bspc 2.1 or higher
			modelnum = (route.endcontents & AREACONTENTS_MODELNUM) >> AREACONTENTS_MODELNUMSHIFT;
			if (modelnum) {
				//
				entitynum = BotModelMinsMaxs(modelnum, ET_MOVER, 0, NULL, NULL);
				if (entitynum) {
					//NOTE: BotGetActivateGoal already checks if the door is open or not
					bspent = BotGetActivateGoal(bs, entitynum, &activategoal);
					if (bspent) {
						//
						if (bs->activatestack && !bs->activatestack->inuse)
							bs->activatestack = NULL;
						// if not already trying to activate this entity
						if (!BotIsGoingToActivateEntity(bs, activategoal.goal.entitynum)) {
							//
							//BotAI_Print(PRT_MESSAGE, "blocked by mover model %d, entity %d ?\n", modelnum, entitynum);
							//
							BotGoForActivateGoal(bs, &activategoal);
							return qtrue;
						}
						else {
							// enable any routing areas that were disabled
							BotEnableActivateGoalAreas(&activategoal, qtrue);
						}
					}
				}
			}
		}
	}
	else if (route.stopevent & RSE_USETRAVELTYPE) {
		if (route.endtravelflags & TFL_BRIDGE) {
			//FIXME: check if the bridge is available to travel over
		}
	}
	return qfalse;
}