#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {int type; int /*<<< orphan*/  origin; int /*<<< orphan*/  radius; } ;
typedef  TYPE_1__ bot_avoidspot_t ;
struct TYPE_6__ {int traveltype; int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
typedef  TYPE_2__ aas_reachability_t ;

/* Variables and functions */
 int AVOID_ALWAYS ; 
 int AVOID_CLEAR ; 
 float DistanceFromLineSquared (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float Square (int /*<<< orphan*/ ) ; 
 int TRAVELTYPE_MASK ; 
#define  TRAVEL_BARRIERJUMP 142 
#define  TRAVEL_BFGJUMP 141 
#define  TRAVEL_CROUCH 140 
#define  TRAVEL_ELEVATOR 139 
#define  TRAVEL_FUNCBOB 138 
#define  TRAVEL_GRAPPLEHOOK 137 
#define  TRAVEL_JUMP 136 
#define  TRAVEL_JUMPPAD 135 
#define  TRAVEL_LADDER 134 
#define  TRAVEL_ROCKETJUMP 133 
#define  TRAVEL_SWIM 132 
#define  TRAVEL_TELEPORT 131 
#define  TRAVEL_WALK 130 
#define  TRAVEL_WALKOFFLEDGE 129 
#define  TRAVEL_WATERJUMP 128 
 float VectorDistanceSquared (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 

int BotAvoidSpots(vec3_t origin, aas_reachability_t *reach, bot_avoidspot_t *avoidspots, int numavoidspots)
{
	int checkbetween, i, type;
	float squareddist, squaredradius;

	switch(reach->traveltype & TRAVELTYPE_MASK)
	{
		case TRAVEL_WALK: checkbetween = qtrue; break;
		case TRAVEL_CROUCH: checkbetween = qtrue; break;
		case TRAVEL_BARRIERJUMP: checkbetween = qtrue; break;
		case TRAVEL_LADDER: checkbetween = qtrue; break;
		case TRAVEL_WALKOFFLEDGE: checkbetween = qfalse; break;
		case TRAVEL_JUMP: checkbetween = qfalse; break;
		case TRAVEL_SWIM: checkbetween = qtrue; break;
		case TRAVEL_WATERJUMP: checkbetween = qtrue; break;
		case TRAVEL_TELEPORT: checkbetween = qfalse; break;
		case TRAVEL_ELEVATOR: checkbetween = qfalse; break;
		case TRAVEL_GRAPPLEHOOK: checkbetween = qfalse; break;
		case TRAVEL_ROCKETJUMP: checkbetween = qfalse; break;
		case TRAVEL_BFGJUMP: checkbetween = qfalse; break;
		case TRAVEL_JUMPPAD: checkbetween = qfalse; break;
		case TRAVEL_FUNCBOB: checkbetween = qfalse; break;
		default: checkbetween = qtrue; break;
	} //end switch

	type = AVOID_CLEAR;
	for (i = 0; i < numavoidspots; i++)
	{
		squaredradius = Square(avoidspots[i].radius);
		squareddist = DistanceFromLineSquared(avoidspots[i].origin, origin, reach->start);
		// if moving towards the avoid spot
		if (squareddist < squaredradius &&
			VectorDistanceSquared(avoidspots[i].origin, origin) > squareddist)
		{
			type = avoidspots[i].type;
		} //end if
		else if (checkbetween) {
			squareddist = DistanceFromLineSquared(avoidspots[i].origin, reach->start, reach->end);
			// if moving towards the avoid spot
			if (squareddist < squaredradius &&
				VectorDistanceSquared(avoidspots[i].origin, reach->start) > squareddist)
			{
				type = avoidspots[i].type;
			} //end if
		} //end if
		else
		{
			VectorDistanceSquared(avoidspots[i].origin, reach->end);
			// if the reachability leads closer to the avoid spot
			if (squareddist < squaredradius && 
				VectorDistanceSquared(avoidspots[i].origin, reach->start) > squareddist)
			{
				type = avoidspots[i].type;
			} //end if
		} //end else
		if (type == AVOID_ALWAYS)
			return type;
	} //end for
	return type;
}