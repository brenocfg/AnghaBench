#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_10__ {int moveflags; int /*<<< orphan*/  lastorigin; scalar_t__* origin; int /*<<< orphan*/  lastgoalareanum; scalar_t__ lastareanum; scalar_t__ lastreachnum; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  ideal_viewangles; int /*<<< orphan*/  movedir; int /*<<< orphan*/  traveltype; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_12__ {int /*<<< orphan*/  areanum; scalar_t__* origin; } ;
typedef  TYPE_3__ bot_goal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotCheckBlocked (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  BotClearMoveResult (TYPE_2__*) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,scalar_t__*,float) ; 
 int MFL_SWIMMING ; 
 int /*<<< orphan*/  MOVERESULT_SWIMVIEW ; 
 int /*<<< orphan*/  TRAVEL_SWIM ; 
 int /*<<< orphan*/  TRAVEL_WALK ; 
 int /*<<< orphan*/  Vector2Angles (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 float VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  qtrue ; 

bot_moveresult_t BotMoveInGoalArea(bot_movestate_t *ms, bot_goal_t *goal)
{
	bot_moveresult_t result;
	vec3_t dir;
	float dist, speed;

#ifdef DEBUG
	//botimport.Print(PRT_MESSAGE, "%s: moving straight to goal\n", ClientName(ms->entitynum-1));
	//AAS_ClearShownDebugLines();
	//AAS_DebugLine(ms->origin, goal->origin, LINECOLOR_RED);
#endif //DEBUG
	BotClearMoveResult(&result);
	//walk straight to the goal origin
	dir[0] = goal->origin[0] - ms->origin[0];
	dir[1] = goal->origin[1] - ms->origin[1];
	if (ms->moveflags & MFL_SWIMMING)
	{
		dir[2] = goal->origin[2] - ms->origin[2];
		result.traveltype = TRAVEL_SWIM;
	} //end if
	else
	{
		dir[2] = 0;
		result.traveltype = TRAVEL_WALK;
	} //endif
	//
	dist = VectorNormalize(dir);
	if (dist > 100) dist = 100;
	speed = 400 - (400 - 4 * dist);
	if (speed < 10) speed = 0;
	//
	BotCheckBlocked(ms, dir, qtrue, &result);
	//elemantary action move in direction
	EA_Move(ms->client, dir, speed);
	VectorCopy(dir, result.movedir);
	//
	if (ms->moveflags & MFL_SWIMMING)
	{
		Vector2Angles(dir, result.ideal_viewangles);
		result.flags |= MOVERESULT_SWIMVIEW;
	} //end if
	//if (!debugline) debugline = botimport.DebugLineCreate();
	//botimport.DebugLineShow(debugline, ms->origin, goal->origin, LINECOLOR_BLUE);
	//
	ms->lastreachnum = 0;
	ms->lastareanum = 0;
	ms->lastgoalareanum = goal->areanum;
	VectorCopy(ms->origin, ms->lastorigin);
	//
	return result;
}