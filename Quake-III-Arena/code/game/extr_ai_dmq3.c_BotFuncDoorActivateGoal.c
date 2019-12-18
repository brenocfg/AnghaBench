#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  model ;
struct TYPE_7__ {int /*<<< orphan*/  areanum; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ bot_state_t ;
struct TYPE_6__ {int entitynum; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  areanum; int /*<<< orphan*/  origin; scalar_t__ flags; scalar_t__ number; } ;
struct TYPE_8__ {int shoot; TYPE_1__ goal; int /*<<< orphan*/  target; } ;
typedef  TYPE_3__ bot_activategoal_t ;

/* Variables and functions */
 int BotModelMinsMaxs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_MOVER ; 
 int MAX_INFO_STRING ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int,int,int) ; 
 int atoi (char*) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_AAS_ValueForBSPEpairKey (int,char*,char*,int) ; 

int BotFuncDoorActivateGoal(bot_state_t *bs, int bspent, bot_activategoal_t *activategoal) {
	int modelindex, entitynum;
	char model[MAX_INFO_STRING];
	vec3_t mins, maxs, origin, angles;

	//shoot at the shootable door
	trap_AAS_ValueForBSPEpairKey(bspent, "model", model, sizeof(model));
	if (!*model)
		return qfalse;
	modelindex = atoi(model+1);
	if (!modelindex)
		return qfalse;
	VectorClear(angles);
	entitynum = BotModelMinsMaxs(modelindex, ET_MOVER, 0, mins, maxs);
	//door origin
	VectorAdd(mins, maxs, origin);
	VectorScale(origin, 0.5, origin);
	VectorCopy(origin, activategoal->target);
	activategoal->shoot = qtrue;
	//
	activategoal->goal.entitynum = entitynum; //NOTE: this is the entity number of the shootable door
	activategoal->goal.number = 0;
	activategoal->goal.flags = 0;
	VectorCopy(bs->origin, activategoal->goal.origin);
	activategoal->goal.areanum = bs->areanum;
	VectorSet(activategoal->goal.mins, -8, -8, -8);
	VectorSet(activategoal->goal.maxs, 8, 8, 8);
	return qtrue;
}