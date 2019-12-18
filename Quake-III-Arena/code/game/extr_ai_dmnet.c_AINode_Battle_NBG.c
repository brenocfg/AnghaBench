#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_31__ {scalar_t__ enemy; int tfl; int* lastenemyorigin; int lastenemyareanum; scalar_t__ nbg_time; int* ideal_viewangles; int flags; int /*<<< orphan*/  weaponnum; int /*<<< orphan*/  origin; int /*<<< orphan*/  ms; int /*<<< orphan*/  character; int /*<<< orphan*/  gs; scalar_t__ enemyvisible_time; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  eye; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_32__ {int flags; int* ideal_viewangles; int* movedir; int /*<<< orphan*/  weapon; scalar_t__ failure; } ;
typedef  TYPE_2__ bot_moveresult_t ;
typedef  int /*<<< orphan*/  bot_goal_t ;
struct TYPE_33__ {int* origin; } ;
typedef  TYPE_3__ aas_entityinfo_t ;
struct TYPE_36__ {scalar_t__ entitynum; } ;
struct TYPE_35__ {scalar_t__ integer; } ;
struct TYPE_34__ {scalar_t__ entitynum; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIEnter_Battle_Fight (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Battle_Retreat (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Intermission (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Observer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Respawn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Seek_NBG (TYPE_1__*,char*) ; 
 int BFL_IDEALVIEWSET ; 
 int /*<<< orphan*/  BotAIBlocked (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  BotAimAtEnemy (TYPE_1__*) ; 
 scalar_t__ BotCanAndWantsToRocketJump (TYPE_1__*) ; 
 int /*<<< orphan*/  BotCheckAttack (TYPE_1__*) ; 
 int /*<<< orphan*/  BotChooseWeapon (TYPE_1__*) ; 
 int /*<<< orphan*/  BotEntityInfo (scalar_t__,TYPE_3__*) ; 
 scalar_t__ BotEntityVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ BotInLavaOrSlime (TYPE_1__*) ; 
 scalar_t__ BotIntermission (TYPE_1__*) ; 
 scalar_t__ BotIsDead (TYPE_1__*) ; 
 scalar_t__ BotIsObserver (TYPE_1__*) ; 
 int /*<<< orphan*/  BotMapScripts (TYPE_1__*) ; 
 int BotPointAreaNum (int*) ; 
 scalar_t__ BotReachedGoal (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotSetupForMovement (TYPE_1__*) ; 
 int /*<<< orphan*/  BotUpdateBattleInventory (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  CHARACTERISTIC_ATTACK_SKILL ; 
 scalar_t__ EntityIsDead (TYPE_3__*) ; 
 scalar_t__ FloatTime () ; 
 scalar_t__ MAX_CLIENTS ; 
 int MOVERESULT_MOVEMENTVIEW ; 
 int MOVERESULT_MOVEMENTVIEWSET ; 
 int MOVERESULT_MOVEMENTWEAPON ; 
 int MOVERESULT_SWIMVIEW ; 
 int TFL_DEFAULT ; 
 int TFL_GRAPPLEHOOK ; 
 int TFL_LAVA ; 
 int TFL_ROCKETJUMP ; 
 int TFL_SLIME ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int /*<<< orphan*/ ,int*) ; 
 TYPE_7__ blueobelisk ; 
 TYPE_6__ bot_grapple ; 
 int qfalse ; 
 int qtrue ; 
 TYPE_5__ redobelisk ; 
 scalar_t__ trap_AAS_AreaReachability (int) ; 
 scalar_t__ trap_BotGetTopGoal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trap_BotMoveToGoal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ trap_BotMovementViewTarget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  trap_BotPopGoal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotResetAvoidReach (int /*<<< orphan*/ ) ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vectoangles (int*,int*) ; 

int AINode_Battle_NBG(bot_state_t *bs) {
	int areanum;
	bot_goal_t goal;
	aas_entityinfo_t entinfo;
	bot_moveresult_t moveresult;
	float attack_skill;
	vec3_t target, dir;

	if (BotIsObserver(bs)) {
		AIEnter_Observer(bs, "battle nbg: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		AIEnter_Intermission(bs, "battle nbg: intermission");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		AIEnter_Respawn(bs, "battle nbg: bot dead");
		return qfalse;
	}
	//if no enemy
	if (bs->enemy < 0) {
		AIEnter_Seek_NBG(bs, "battle nbg: no enemy");
		return qfalse;
	}
	//
	BotEntityInfo(bs->enemy, &entinfo);
	if (EntityIsDead(&entinfo)) {
		AIEnter_Seek_NBG(bs, "battle nbg: enemy dead");
		return qfalse;
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer) bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs)) bs->tfl |= TFL_LAVA|TFL_SLIME;
	//
	if (BotCanAndWantsToRocketJump(bs)) {
		bs->tfl |= TFL_ROCKETJUMP;
	}
	//map specific code
	BotMapScripts(bs);
	//update the last time the enemy was visible
	if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->enemy)) {
		bs->enemyvisible_time = FloatTime();
		VectorCopy(entinfo.origin, target);
		// if not a player enemy
		if (bs->enemy >= MAX_CLIENTS) {
#ifdef MISSIONPACK
			// if attacking an obelisk
			if ( bs->enemy == redobelisk.entitynum ||
				bs->enemy == blueobelisk.entitynum ) {
				target[2] += 16;
			}
#endif
		}
		//update the reachability area and origin if possible
		areanum = BotPointAreaNum(target);
		if (areanum && trap_AAS_AreaReachability(areanum)) {
			VectorCopy(target, bs->lastenemyorigin);
			bs->lastenemyareanum = areanum;
		}
	}
	//if the bot has no goal or touches the current goal
	if (!trap_BotGetTopGoal(bs->gs, &goal)) {
		bs->nbg_time = 0;
	}
	else if (BotReachedGoal(bs, &goal)) {
		bs->nbg_time = 0;
	}
	//
	if (bs->nbg_time < FloatTime()) {
		//pop the current goal from the stack
		trap_BotPopGoal(bs->gs);
		//if the bot still has a goal
		if (trap_BotGetTopGoal(bs->gs, &goal))
			AIEnter_Battle_Retreat(bs, "battle nbg: time out");
		else
			AIEnter_Battle_Fight(bs, "battle nbg: time out");
		//
		return qfalse;
	}
	//initialize the movement state
	BotSetupForMovement(bs);
	//move towards the goal
	trap_BotMoveToGoal(&moveresult, bs->ms, &goal, bs->tfl);
	//if the movement failed
	if (moveresult.failure) {
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		//BotAI_Print(PRT_MESSAGE, "movement failure %d\n", moveresult.traveltype);
		bs->nbg_time = 0;
	}
	//
	BotAIBlocked(bs, &moveresult, qfalse);
	//update the attack inventory values
	BotUpdateBattleInventory(bs, bs->enemy);
	//choose the best weapon to fight with
	BotChooseWeapon(bs);
	//if the view is fixed for the movement
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEW|MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	}
	else if (!(moveresult.flags & MOVERESULT_MOVEMENTVIEWSET)
				&& !(bs->flags & BFL_IDEALVIEWSET)) {
		attack_skill = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ATTACK_SKILL, 0, 1);
		//if the bot is skilled anough and the enemy is visible
		if (attack_skill > 0.3) {
			//&& BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->enemy)
			BotAimAtEnemy(bs);
		}
		else {
			if (trap_BotMovementViewTarget(bs->ms, &goal, bs->tfl, 300, target)) {
				VectorSubtract(target, bs->origin, dir);
				vectoangles(dir, bs->ideal_viewangles);
			}
			else {
				vectoangles(moveresult.movedir, bs->ideal_viewangles);
			}
			bs->ideal_viewangles[2] *= 0.5;
		}
	}
	//if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON) bs->weaponnum = moveresult.weapon;
	//attack the enemy if possible
	BotCheckAttack(bs);
	//
	return qtrue;
}