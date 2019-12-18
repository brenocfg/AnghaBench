#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_3__ {float* endpos; int fraction; int startsolid; scalar_t__ lastarea; scalar_t__ area; scalar_t__ planenum; scalar_t__ ent; } ;
typedef  TYPE_1__ aas_trace_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_PresenceTypeBoundingBox (int,float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 int qfalse ; 
 int qtrue ; 

int AAS_ClipToBBox(aas_trace_t *trace, vec3_t start, vec3_t end, int presencetype, vec3_t mins, vec3_t maxs)
{
	int i, j, side;
	float front, back, frac, planedist;
	vec3_t bboxmins, bboxmaxs, absmins, absmaxs, dir, mid;

	AAS_PresenceTypeBoundingBox(presencetype, bboxmins, bboxmaxs);
	VectorSubtract(mins, bboxmaxs, absmins);
	VectorSubtract(maxs, bboxmins, absmaxs);
	//
	VectorCopy(end, trace->endpos);
	trace->fraction = 1;
	for (i = 0; i < 3; i++)
	{
		if (start[i] < absmins[i] && end[i] < absmins[i]) return qfalse;
		if (start[i] > absmaxs[i] && end[i] > absmaxs[i]) return qfalse;
	} //end for
	//check bounding box collision
	VectorSubtract(end, start, dir);
	frac = 1;
	for (i = 0; i < 3; i++)
	{
		//get plane to test collision with for the current axis direction
		if (dir[i] > 0) planedist = absmins[i];
		else planedist = absmaxs[i];
		//calculate collision fraction
		front = start[i] - planedist;
		back = end[i] - planedist;
		frac = front / (front-back);
		//check if between bounding planes of next axis
		side = i + 1;
		if (side > 2) side = 0;
		mid[side] = start[side] + dir[side] * frac;
		if (mid[side] > absmins[side] && mid[side] < absmaxs[side])
		{
			//check if between bounding planes of next axis
			side++;
			if (side > 2) side = 0;
			mid[side] = start[side] + dir[side] * frac;
			if (mid[side] > absmins[side] && mid[side] < absmaxs[side])
			{
				mid[i] = planedist;
				break;
			} //end if
		} //end if
	} //end for
	//if there was a collision
	if (i != 3)
	{
		trace->startsolid = qfalse;
		trace->fraction = frac;
		trace->ent = 0;
		trace->planenum = 0;
		trace->area = 0;
		trace->lastarea = 0;
		//trace endpos
		for (j = 0; j < 3; j++) trace->endpos[j] = start[j] + dir[j] * frac;
		return qtrue;
	} //end if
	return qfalse;
}