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
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_6__ {int /*<<< orphan*/  client; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ bot_movestate_t ;
typedef  int /*<<< orphan*/  bot_moveresult_t ;
struct TYPE_7__ {int /*<<< orphan*/ * end; } ;
typedef  TYPE_2__ aas_reachability_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotClearMoveResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MoverBottomCenter (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fabs (int /*<<< orphan*/ ) ; 

bot_moveresult_t BotFinishTravel_Elevator(bot_movestate_t *ms, aas_reachability_t *reach)
{
	vec3_t bottomcenter, bottomdir, topdir;
	bot_moveresult_t result;

	BotClearMoveResult(&result);
	//
	MoverBottomCenter(reach, bottomcenter);
	VectorSubtract(bottomcenter, ms->origin, bottomdir);
	//
	VectorSubtract(reach->end, ms->origin, topdir);
	//
	if (fabs(bottomdir[2]) < fabs(topdir[2]))
	{
		VectorNormalize(bottomdir);
		EA_Move(ms->client, bottomdir, 300);
	} //end if
	else
	{
		VectorNormalize(topdir);
		EA_Move(ms->client, topdir, 300);
	} //end else
	return result;
}