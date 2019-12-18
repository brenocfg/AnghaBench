#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_8__ {scalar_t__ ent; int /*<<< orphan*/  startsolid; } ;
typedef  TYPE_1__ bsp_trace_t ;
struct TYPE_9__ {int /*<<< orphan*/  entitynum; int /*<<< orphan*/  origin; int /*<<< orphan*/  presencetype; int /*<<< orphan*/  areanum; } ;
typedef  TYPE_2__ bot_movestate_t ;
struct TYPE_10__ {scalar_t__ blockentity; int /*<<< orphan*/  flags; void* blocked; } ;
typedef  TYPE_3__ bot_moveresult_t ;
struct TYPE_11__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AreaReachability (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAS_PresenceTypeBoundingBox (int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_1__ AAS_Trace (int /*<<< orphan*/ ,int*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int CONTENTS_BODY ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SOLID ; 
 int /*<<< orphan*/  DotProduct (int*,int*) ; 
 scalar_t__ ENTITYNUM_NONE ; 
 scalar_t__ ENTITYNUM_WORLD ; 
 int /*<<< orphan*/  MOVERESULT_ONTOPOFOBSTACLE ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int*,int*) ; 
 double fabs (int /*<<< orphan*/ ) ; 
 void* qtrue ; 
 TYPE_4__* sv_maxstep ; 

void BotCheckBlocked(bot_movestate_t *ms, vec3_t dir, int checkbottom, bot_moveresult_t *result)
{
	vec3_t mins, maxs, end, up = {0, 0, 1};
	bsp_trace_t trace;

	//test for entities obstructing the bot's path
	AAS_PresenceTypeBoundingBox(ms->presencetype, mins, maxs);
	//
	if (fabs(DotProduct(dir, up)) < 0.7)
	{
		mins[2] += sv_maxstep->value; //if the bot can step on
		maxs[2] -= 10; //a little lower to avoid low ceiling
	} //end if
	VectorMA(ms->origin, 3, dir, end);
	trace = AAS_Trace(ms->origin, mins, maxs, end, ms->entitynum, CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_BODY);
	//if not started in solid and not hitting the world entity
	if (!trace.startsolid && (trace.ent != ENTITYNUM_WORLD && trace.ent != ENTITYNUM_NONE) )
	{
		result->blocked = qtrue;
		result->blockentity = trace.ent;
#ifdef DEBUG
		//botimport.Print(PRT_MESSAGE, "%d: BotCheckBlocked: I'm blocked\n", ms->client);
#endif //DEBUG
	} //end if
	//if not in an area with reachability
	else if (checkbottom && !AAS_AreaReachability(ms->areanum))
	{
		//check if the bot is standing on something
		AAS_PresenceTypeBoundingBox(ms->presencetype, mins, maxs);
		VectorMA(ms->origin, -3, up, end);
		trace = AAS_Trace(ms->origin, mins, maxs, end, ms->entitynum, CONTENTS_SOLID|CONTENTS_PLAYERCLIP);
		if (!trace.startsolid && (trace.ent != ENTITYNUM_WORLD && trace.ent != ENTITYNUM_NONE) )
		{
			result->blocked = qtrue;
			result->blockentity = trace.ent;
			result->flags |= MOVERESULT_ONTOPOFOBSTACLE;
#ifdef DEBUG
			//botimport.Print(PRT_MESSAGE, "%d: BotCheckBlocked: I'm blocked\n", ms->client);
#endif //DEBUG
		} //end if
	} //end else
}