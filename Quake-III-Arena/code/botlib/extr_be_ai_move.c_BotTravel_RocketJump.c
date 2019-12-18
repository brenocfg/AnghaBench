#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_9__ {int /*<<< orphan*/  client; int /*<<< orphan*/  lastreachnum; int /*<<< orphan*/  jumpreach; scalar_t__* origin; int /*<<< orphan*/ * viewangles; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_10__ {int* ideal_viewangles; int weapon; int /*<<< orphan*/  movedir; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_11__ {scalar_t__* end; scalar_t__* start; } ;
typedef  TYPE_3__ aas_reachability_t ;
struct TYPE_12__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  AngleDiff (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BotClearMoveResult (TYPE_2__*) ; 
 int /*<<< orphan*/  EA_Attack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,scalar_t__*,float) ; 
 int /*<<< orphan*/  EA_SelectWeapon (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EA_View (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  MOVERESULT_MOVEMENTVIEWSET ; 
 int /*<<< orphan*/  MOVERESULT_MOVEMENTWEAPON ; 
 size_t PITCH ; 
 int /*<<< orphan*/  Vector2Angles (scalar_t__*,int*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 float VectorNormalize (scalar_t__*) ; 
 int fabs (int /*<<< orphan*/ ) ; 
 TYPE_4__* weapindex_rocketlauncher ; 

bot_moveresult_t BotTravel_RocketJump(bot_movestate_t *ms, aas_reachability_t *reach)
{
	vec3_t hordir;
	float dist, speed;
	bot_moveresult_t result;

	//botimport.Print(PRT_MESSAGE, "BotTravel_RocketJump: bah\n");
	BotClearMoveResult(&result);
	//
	hordir[0] = reach->start[0] - ms->origin[0];
	hordir[1] = reach->start[1] - ms->origin[1];
	hordir[2] = 0;
	//
	dist = VectorNormalize(hordir);
	//look in the movement direction
	Vector2Angles(hordir, result.ideal_viewangles);
	//look straight down
	result.ideal_viewangles[PITCH] = 90;
	//
	if (dist < 5 &&
			fabs(AngleDiff(result.ideal_viewangles[0], ms->viewangles[0])) < 5 &&
			fabs(AngleDiff(result.ideal_viewangles[1], ms->viewangles[1])) < 5)
	{
		//botimport.Print(PRT_MESSAGE, "between jump start and run start point\n");
		hordir[0] = reach->end[0] - ms->origin[0];
		hordir[1] = reach->end[1] - ms->origin[1];
		hordir[2] = 0;
		VectorNormalize(hordir);
		//elemantary action jump
		EA_Jump(ms->client);
		EA_Attack(ms->client);
		EA_Move(ms->client, hordir, 800);
		//
		ms->jumpreach = ms->lastreachnum;
	} //end if
	else
	{
		if (dist > 80) dist = 80;
		speed = 400 - (400 - 5 * dist);
		EA_Move(ms->client, hordir, speed);
	} //end else
	//look in the movement direction
	Vector2Angles(hordir, result.ideal_viewangles);
	//look straight down
	result.ideal_viewangles[PITCH] = 90;
	//set the view angles directly
	EA_View(ms->client, result.ideal_viewangles);
	//view is important for the movment
	result.flags |= MOVERESULT_MOVEMENTVIEWSET;
	//select the rocket launcher
	EA_SelectWeapon(ms->client, (int) weapindex_rocketlauncher->value);
	//weapon is used for movement
	result.weapon = (int) weapindex_rocketlauncher->value;
	result.flags |= MOVERESULT_MOVEMENTWEAPON;
	//
	VectorCopy(hordir, result.movedir);
	//
	return result;
}