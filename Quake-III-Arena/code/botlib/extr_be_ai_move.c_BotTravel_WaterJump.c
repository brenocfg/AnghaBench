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
typedef  int* vec3_t ;
struct TYPE_8__ {int /*<<< orphan*/  client; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_9__ {int* movedir; int /*<<< orphan*/  flags; int /*<<< orphan*/  ideal_viewangles; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_10__ {int /*<<< orphan*/  end; } ;
typedef  TYPE_3__ aas_reachability_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotClearMoveResult (TYPE_2__*) ; 
 int /*<<< orphan*/  EA_MoveForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_MoveUp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOVERESULT_MOVEMENTVIEW ; 
 int /*<<< orphan*/  Vector2Angles (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 float VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int crandom () ; 

bot_moveresult_t BotTravel_WaterJump(bot_movestate_t *ms, aas_reachability_t *reach)
{
	vec3_t dir, hordir;
	float dist;
	bot_moveresult_t result;

	BotClearMoveResult(&result);
	//swim straight to reachability end
	VectorSubtract(reach->end, ms->origin, dir);
	VectorCopy(dir, hordir);
	hordir[2] = 0;
	dir[2] += 15 + crandom() * 40;
	//botimport.Print(PRT_MESSAGE, "BotTravel_WaterJump: dir[2] = %f\n", dir[2]);
	VectorNormalize(dir);
	dist = VectorNormalize(hordir);
	//elemantary actions
	//EA_Move(ms->client, dir, 400);
	EA_MoveForward(ms->client);
	//move up if close to the actual out of water jump spot
	if (dist < 40) EA_MoveUp(ms->client);
	//set the ideal view angles
	Vector2Angles(dir, result.ideal_viewangles);
	result.flags |= MOVERESULT_MOVEMENTVIEW;
	//
	VectorCopy(dir, result.movedir);
	//
	return result;
}