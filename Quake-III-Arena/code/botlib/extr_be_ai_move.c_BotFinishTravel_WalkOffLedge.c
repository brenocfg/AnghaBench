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
struct TYPE_10__ {int /*<<< orphan*/  client; int /*<<< orphan*/  velocity; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_11__ {scalar_t__* movedir; } ;
typedef  TYPE_2__ bot_moveresult_t ;
struct TYPE_12__ {scalar_t__* end; } ;
typedef  TYPE_3__ aas_reachability_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAirControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,float*) ; 
 int /*<<< orphan*/  BotCheckBlocked (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  BotClearMoveResult (TYPE_2__*) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,scalar_t__*,float) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorMA (scalar_t__*,int,scalar_t__*,scalar_t__*) ; 
 float VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  qtrue ; 

bot_moveresult_t BotFinishTravel_WalkOffLedge(bot_movestate_t *ms, aas_reachability_t *reach)
{
	vec3_t dir, hordir, end, v;
	float dist, speed;
	bot_moveresult_t result;

	BotClearMoveResult(&result);
	//
	VectorSubtract(reach->end, ms->origin, dir);
	BotCheckBlocked(ms, dir, qtrue, &result);
	//
	VectorSubtract(reach->end, ms->origin, v);
	v[2] = 0;
	dist = VectorNormalize(v);
	if (dist > 16) VectorMA(reach->end, 16, v, end);
	else VectorCopy(reach->end, end);
	//
	if (!BotAirControl(ms->origin, ms->velocity, end, hordir, &speed))
	{
		//go straight to the reachability end
		VectorCopy(dir, hordir);
		hordir[2] = 0;
		//
		dist = VectorNormalize(hordir);
		speed = 400;
	} //end if
	//
	EA_Move(ms->client, hordir, speed);
	VectorCopy(hordir, result.movedir);
	//
	return result;
}