#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_9__ {int /*<<< orphan*/  type; int /*<<< orphan*/  signbits; int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
struct TYPE_11__ {int /*<<< orphan*/  entityNum; int /*<<< orphan*/  surfaceFlags; TYPE_2__ plane; int /*<<< orphan*/  endpos; int /*<<< orphan*/  fraction; int /*<<< orphan*/  startsolid; int /*<<< orphan*/  allsolid; } ;
typedef  TYPE_4__ trace_t ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; int /*<<< orphan*/  signbits; int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
struct TYPE_12__ {scalar_t__ contents; scalar_t__ sidenum; scalar_t__ exp_dist; int /*<<< orphan*/  ent; TYPE_3__ surface; TYPE_1__ plane; int /*<<< orphan*/  endpos; int /*<<< orphan*/  fraction; int /*<<< orphan*/  startsolid; int /*<<< orphan*/  allsolid; } ;
typedef  TYPE_5__ bsp_trace_t ;

/* Variables and functions */
 int /*<<< orphan*/  SV_Trace (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 

void BotImport_Trace(bsp_trace_t *bsptrace, vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int passent, int contentmask) {
	trace_t trace;

	SV_Trace(&trace, start, mins, maxs, end, passent, contentmask, qfalse);
	//copy the trace information
	bsptrace->allsolid = trace.allsolid;
	bsptrace->startsolid = trace.startsolid;
	bsptrace->fraction = trace.fraction;
	VectorCopy(trace.endpos, bsptrace->endpos);
	bsptrace->plane.dist = trace.plane.dist;
	VectorCopy(trace.plane.normal, bsptrace->plane.normal);
	bsptrace->plane.signbits = trace.plane.signbits;
	bsptrace->plane.type = trace.plane.type;
	bsptrace->surface.value = trace.surfaceFlags;
	bsptrace->ent = trace.entityNum;
	bsptrace->exp_dist = 0;
	bsptrace->sidenum = 0;
	bsptrace->contents = 0;
}