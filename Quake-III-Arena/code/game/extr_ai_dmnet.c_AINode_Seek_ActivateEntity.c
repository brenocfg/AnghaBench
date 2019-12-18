#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_13__ ;

/* Type definitions */
typedef  double* vec3_t ;
struct TYPE_44__ {double fraction; scalar_t__ ent; } ;
typedef  TYPE_3__ bsp_trace_t ;
struct TYPE_42__ {int weapon; } ;
struct TYPE_45__ {int tfl; int enemy; double* ideal_viewangles; double thinktime; int flags; int weaponnum; int /*<<< orphan*/  gs; int /*<<< orphan*/  ms; int /*<<< orphan*/  origin; TYPE_2__* activatestack; int /*<<< orphan*/  eye; int /*<<< orphan*/  client; int /*<<< orphan*/  viewangles; TYPE_1__ cur_ps; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_4__ bot_state_t ;
struct TYPE_46__ {int flags; double* ideal_viewangles; int weapon; double* movedir; scalar_t__ failure; } ;
typedef  TYPE_5__ bot_moveresult_t ;
struct TYPE_47__ {scalar_t__ entitynum; } ;
typedef  TYPE_6__ bot_goal_t ;
struct TYPE_48__ {int /*<<< orphan*/  origin; } ;
typedef  TYPE_7__ aas_entityinfo_t ;
struct TYPE_43__ {double* target; int weapon; scalar_t__ time; scalar_t__ shoot; int /*<<< orphan*/  origin; TYPE_6__ goal; } ;
struct TYPE_41__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIEnter_Battle_Fight (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Battle_NBG (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Intermission (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Observer (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Respawn (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Seek_NBG (TYPE_4__*,char*) ; 
 int BFL_IDEALVIEWSET ; 
 int /*<<< orphan*/  BotAIBlocked (TYPE_4__*,TYPE_5__*,int) ; 
 scalar_t__ BotAIPredictObstacles (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BotAI_Trace (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BotClearActivateGoalStack (TYPE_4__*) ; 
 int /*<<< orphan*/  BotClearPath (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  BotEntityInfo (scalar_t__,TYPE_7__*) ; 
 scalar_t__ BotFindEnemy (TYPE_4__*,int) ; 
 scalar_t__ BotInLavaOrSlime (TYPE_4__*) ; 
 scalar_t__ BotIntermission (TYPE_4__*) ; 
 scalar_t__ BotIsDead (TYPE_4__*) ; 
 scalar_t__ BotIsObserver (TYPE_4__*) ; 
 int /*<<< orphan*/  BotMapScripts (TYPE_4__*) ; 
 int /*<<< orphan*/  BotPopFromActivateGoalStack (TYPE_4__*) ; 
 int /*<<< orphan*/  BotRoamGoal (TYPE_4__*,double*) ; 
 int BotSelectActivateWeapon (TYPE_4__*) ; 
 int /*<<< orphan*/  BotSetupForMovement (TYPE_4__*) ; 
 scalar_t__ BotWantsToRetreat (TYPE_4__*) ; 
 scalar_t__ FloatTime () ; 
 scalar_t__ InFieldOfVision (int /*<<< orphan*/ ,int,double*) ; 
 int /*<<< orphan*/  MASK_SHOT ; 
 int MOVERESULT_MOVEMENTVIEW ; 
 int MOVERESULT_MOVEMENTVIEWSET ; 
 int MOVERESULT_MOVEMENTWEAPON ; 
 int MOVERESULT_SWIMVIEW ; 
 int MOVERESULT_WAITING ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int TFL_DEFAULT ; 
 int TFL_GRAPPLEHOOK ; 
 int TFL_LAVA ; 
 int TFL_SLIME ; 
 int /*<<< orphan*/  VectorCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (double*,double*) ; 
 int /*<<< orphan*/  VectorSubtract (double*,int /*<<< orphan*/ ,double*) ; 
 TYPE_13__ bot_grapple ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int qfalse ; 
 int qtrue ; 
 double random () ; 
 int /*<<< orphan*/  trap_BotEmptyGoalStack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMoveToGoal (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 scalar_t__ trap_BotMovementViewTarget (int /*<<< orphan*/ ,TYPE_6__*,int,int,double*) ; 
 int /*<<< orphan*/  trap_BotResetAvoidReach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotResetLastAvoidReach (int /*<<< orphan*/ ) ; 
 scalar_t__ trap_BotTouchingGoal (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  trap_EA_Attack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vectoangles (double*,double*) ; 

int AINode_Seek_ActivateEntity(bot_state_t *bs) {
	bot_goal_t *goal;
	vec3_t target, dir, ideal_viewangles;
	bot_moveresult_t moveresult;
	int targetvisible;
	bsp_trace_t bsptrace;
	aas_entityinfo_t entinfo;

	if (BotIsObserver(bs)) {
		BotClearActivateGoalStack(bs);
		AIEnter_Observer(bs, "active entity: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		BotClearActivateGoalStack(bs);
		AIEnter_Intermission(bs, "activate entity: intermission");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		BotClearActivateGoalStack(bs);
		AIEnter_Respawn(bs, "activate entity: bot dead");
		return qfalse;
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer) bs->tfl |= TFL_GRAPPLEHOOK;
	// if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs)) bs->tfl |= TFL_LAVA|TFL_SLIME;
	// map specific code
	BotMapScripts(bs);
	// no enemy
	bs->enemy = -1;
	// if the bot has no activate goal
	if (!bs->activatestack) {
		BotClearActivateGoalStack(bs);
		AIEnter_Seek_NBG(bs, "activate entity: no goal");
		return qfalse;
	}
	//
	goal = &bs->activatestack->goal;
	// initialize target being visible to false
	targetvisible = qfalse;
	// if the bot has to shoot at a target to activate something
	if (bs->activatestack->shoot) {
		//
		BotAI_Trace(&bsptrace, bs->eye, NULL, NULL, bs->activatestack->target, bs->entitynum, MASK_SHOT);
		// if the shootable entity is visible from the current position
		if (bsptrace.fraction >= 1.0 || bsptrace.ent == goal->entitynum) {
			targetvisible = qtrue;
			// if holding the right weapon
			if (bs->cur_ps.weapon == bs->activatestack->weapon) {
				VectorSubtract(bs->activatestack->target, bs->eye, dir);
				vectoangles(dir, ideal_viewangles);
				// if the bot is pretty close with it's aim
				if (InFieldOfVision(bs->viewangles, 20, ideal_viewangles)) {
					trap_EA_Attack(bs->client);
				}
			}
		}
	}
	// if the shoot target is visible
	if (targetvisible) {
		// get the entity info of the entity the bot is shooting at
		BotEntityInfo(goal->entitynum, &entinfo);
		// if the entity the bot shoots at moved
		if (!VectorCompare(bs->activatestack->origin, entinfo.origin)) {
#ifdef DEBUG
			BotAI_Print(PRT_MESSAGE, "hit shootable button or trigger\n");
#endif //DEBUG
			bs->activatestack->time = 0;
		}
		// if the activate goal has been activated or the bot takes too long
		if (bs->activatestack->time < FloatTime()) {
			BotPopFromActivateGoalStack(bs);
			// if there are more activate goals on the stack
			if (bs->activatestack) {
				bs->activatestack->time = FloatTime() + 10;
				return qfalse;
			}
			AIEnter_Seek_NBG(bs, "activate entity: time out");
			return qfalse;
		}
		memset(&moveresult, 0, sizeof(bot_moveresult_t));
	}
	else {
		// if the bot has no goal
		if (!goal) {
			bs->activatestack->time = 0;
		}
		// if the bot does not have a shoot goal
		else if (!bs->activatestack->shoot) {
			//if the bot touches the current goal
			if (trap_BotTouchingGoal(bs->origin, goal)) {
#ifdef DEBUG
				BotAI_Print(PRT_MESSAGE, "touched button or trigger\n");
#endif //DEBUG
				bs->activatestack->time = 0;
			}
		}
		// if the activate goal has been activated or the bot takes too long
		if (bs->activatestack->time < FloatTime()) {
			BotPopFromActivateGoalStack(bs);
			// if there are more activate goals on the stack
			if (bs->activatestack) {
				bs->activatestack->time = FloatTime() + 10;
				return qfalse;
			}
			AIEnter_Seek_NBG(bs, "activate entity: activated");
			return qfalse;
		}
		//predict obstacles
		if (BotAIPredictObstacles(bs, goal))
			return qfalse;
		//initialize the movement state
		BotSetupForMovement(bs);
		//move towards the goal
		trap_BotMoveToGoal(&moveresult, bs->ms, goal, bs->tfl);
		//if the movement failed
		if (moveresult.failure) {
			//reset the avoid reach, otherwise bot is stuck in current area
			trap_BotResetAvoidReach(bs->ms);
			//
			bs->activatestack->time = 0;
		}
		//check if the bot is blocked
		BotAIBlocked(bs, &moveresult, qtrue);
	}
	//
	BotClearPath(bs, &moveresult);
	// if the bot has to shoot to activate
	if (bs->activatestack->shoot) {
		// if the view angles aren't yet used for the movement
		if (!(moveresult.flags & MOVERESULT_MOVEMENTVIEW)) {
			VectorSubtract(bs->activatestack->target, bs->eye, dir);
			vectoangles(dir, moveresult.ideal_viewangles);
			moveresult.flags |= MOVERESULT_MOVEMENTVIEW;
		}
		// if there's no weapon yet used for the movement
		if (!(moveresult.flags & MOVERESULT_MOVEMENTWEAPON)) {
			moveresult.flags |= MOVERESULT_MOVEMENTWEAPON;
			//
			bs->activatestack->weapon = BotSelectActivateWeapon(bs);
			if (bs->activatestack->weapon == -1) {
				//FIXME: find a decent weapon first
				bs->activatestack->weapon = 0;
			}
			moveresult.weapon = bs->activatestack->weapon;
		}
	}
	// if the ideal view angles are set for movement
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEWSET|MOVERESULT_MOVEMENTVIEW|MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	}
	// if waiting for something
	else if (moveresult.flags & MOVERESULT_WAITING) {
		if (random() < bs->thinktime * 0.8) {
			BotRoamGoal(bs, target);
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
			bs->ideal_viewangles[2] *= 0.5;
		}
	}
	else if (!(bs->flags & BFL_IDEALVIEWSET)) {
		if (trap_BotMovementViewTarget(bs->ms, goal, bs->tfl, 300, target)) {
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
		}
		else {
			vectoangles(moveresult.movedir, bs->ideal_viewangles);
		}
		bs->ideal_viewangles[2] *= 0.5;
	}
	// if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON)
		bs->weaponnum = moveresult.weapon;
	// if there is an enemy
	if (BotFindEnemy(bs, -1)) {
		if (BotWantsToRetreat(bs)) {
			//keep the current long term goal and retreat
			AIEnter_Battle_NBG(bs, "activate entity: found enemy");
		}
		else {
			trap_BotResetLastAvoidReach(bs->ms);
			//empty the goal stack
			trap_BotEmptyGoalStack(bs->gs);
			//go fight
			AIEnter_Battle_Fight(bs, "activate entity: found enemy");
		}
		BotClearActivateGoalStack(bs);
	}
	return qtrue;
}