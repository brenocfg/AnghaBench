#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_7__ {scalar_t__* origin; float thinktime; int /*<<< orphan*/  moveflags; int /*<<< orphan*/  client; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_8__ {scalar_t__* endpos; double fraction; scalar_t__ startsolid; } ;
typedef  TYPE_2__ aas_trace_t ;
struct TYPE_10__ {scalar_t__ value; } ;
struct TYPE_9__ {scalar_t__ value; } ;

/* Variables and functions */
 TYPE_2__ AAS_TraceClientBBox (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,scalar_t__*,float) ; 
 int /*<<< orphan*/  MFL_BARRIERJUMP ; 
 int /*<<< orphan*/  PRESENCE_NORMAL ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorMA (scalar_t__*,float,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorNormalize (scalar_t__*) ; 
 int qfalse ; 
 int qtrue ; 
 TYPE_4__* sv_maxbarrier ; 
 TYPE_3__* sv_maxstep ; 

int BotCheckBarrierJump(bot_movestate_t *ms, vec3_t dir, float speed)
{
	vec3_t start, hordir, end;
	aas_trace_t trace;

	VectorCopy(ms->origin, end);
	end[2] += sv_maxbarrier->value;
	//trace right up
	trace = AAS_TraceClientBBox(ms->origin, end, PRESENCE_NORMAL, ms->entitynum);
	//this shouldn't happen... but we check anyway
	if (trace.startsolid) return qfalse;
	//if very low ceiling it isn't possible to jump up to a barrier
	if (trace.endpos[2] - ms->origin[2] < sv_maxstep->value) return qfalse;
	//
	hordir[0] = dir[0];
	hordir[1] = dir[1];
	hordir[2] = 0;
	VectorNormalize(hordir);
	VectorMA(ms->origin, ms->thinktime * speed * 0.5, hordir, end);
	VectorCopy(trace.endpos, start);
	end[2] = trace.endpos[2];
	//trace from previous trace end pos horizontally in the move direction
	trace = AAS_TraceClientBBox(start, end, PRESENCE_NORMAL, ms->entitynum);
	//again this shouldn't happen
	if (trace.startsolid) return qfalse;
	//
	VectorCopy(trace.endpos, start);
	VectorCopy(trace.endpos, end);
	end[2] = ms->origin[2];
	//trace down from the previous trace end pos
	trace = AAS_TraceClientBBox(start, end, PRESENCE_NORMAL, ms->entitynum);
	//if solid
	if (trace.startsolid) return qfalse;
	//if no obstacle at all
	if (trace.fraction >= 1.0) return qfalse;
	//if less than the maximum step height
	if (trace.endpos[2] - ms->origin[2] < sv_maxstep->value) return qfalse;
	//
	EA_Jump(ms->client);
	EA_Move(ms->client, hordir, speed);
	ms->moveflags |= MFL_BARRIERJUMP;
	//there is a barrier
	return qtrue;
}