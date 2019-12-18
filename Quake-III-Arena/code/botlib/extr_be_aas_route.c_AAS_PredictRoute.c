#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct aas_predictroute_s {int stopevent; int endarea; int endcontents; int endtravelflags; int time; int /*<<< orphan*/  endpos; } ;
struct TYPE_6__ {int numareas; int firstarea; } ;
typedef  TYPE_2__ aas_reachabilityareas_t ;
struct TYPE_7__ {size_t areanum; int /*<<< orphan*/  end; int /*<<< orphan*/  traveltype; scalar_t__ traveltime; int /*<<< orphan*/  start; } ;
typedef  TYPE_3__ aas_reachability_t ;
struct TYPE_8__ {int numareas; int* reachabilityareaindex; TYPE_1__* areasettings; TYPE_2__* reachabilityareas; TYPE_3__* reachability; } ;
struct TYPE_5__ {int contents; } ;

/* Variables and functions */
 int AAS_AreaContentsTravelFlags_inline (size_t) ; 
 int AAS_AreaReachabilityToGoalArea (int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ AAS_AreaTravelTime (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int AAS_TravelFlagForType_inline (int /*<<< orphan*/ ) ; 
 int RSE_ENTERAREA ; 
 int RSE_ENTERCONTENTS ; 
 int RSE_NONE ; 
 int RSE_NOROUTE ; 
 int RSE_USETRAVELTYPE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ aasworld ; 
 int qfalse ; 
 int qtrue ; 

int AAS_PredictRoute(struct aas_predictroute_s *route, int areanum, vec3_t origin,
							int goalareanum, int travelflags, int maxareas, int maxtime,
							int stopevent, int stopcontents, int stoptfl, int stopareanum)
{
	int curareanum, reachnum, i, j, testareanum;
	vec3_t curorigin;
	aas_reachability_t *reach;
	aas_reachabilityareas_t *reachareas;

	//init output
	route->stopevent = RSE_NONE;
	route->endarea = goalareanum;
	route->endcontents = 0;
	route->endtravelflags = 0;
	VectorCopy(origin, route->endpos);
	route->time = 0;

	curareanum = areanum;
	VectorCopy(origin, curorigin);

	for (i = 0; curareanum != goalareanum && (!maxareas || i < maxareas) && i < aasworld.numareas; i++)
	{
		reachnum = AAS_AreaReachabilityToGoalArea(curareanum, curorigin, goalareanum, travelflags);
		if (!reachnum)
		{
			route->stopevent = RSE_NOROUTE;
			return qfalse;
		} //end if
		reach = &aasworld.reachability[reachnum];
		//
		if (stopevent & RSE_USETRAVELTYPE)
		{
			if (AAS_TravelFlagForType_inline(reach->traveltype) & stoptfl)
			{
				route->stopevent = RSE_USETRAVELTYPE;
				route->endarea = curareanum;
				route->endcontents = aasworld.areasettings[curareanum].contents;
				route->endtravelflags = AAS_TravelFlagForType_inline(reach->traveltype);
				VectorCopy(reach->start, route->endpos);
				return qtrue;
			} //end if
			if (AAS_AreaContentsTravelFlags_inline(reach->areanum) & stoptfl)
			{
				route->stopevent = RSE_USETRAVELTYPE;
				route->endarea = reach->areanum;
				route->endcontents = aasworld.areasettings[reach->areanum].contents;
				route->endtravelflags = AAS_AreaContentsTravelFlags_inline(reach->areanum);
				VectorCopy(reach->end, route->endpos);
				route->time += AAS_AreaTravelTime(areanum, origin, reach->start);
				route->time += reach->traveltime;
				return qtrue;
			} //end if
		} //end if
		reachareas = &aasworld.reachabilityareas[reachnum];
		for (j = 0; j < reachareas->numareas + 1; j++)
		{
			if (j >= reachareas->numareas)
				testareanum = reach->areanum;
			else
				testareanum = aasworld.reachabilityareaindex[reachareas->firstarea + j];
			if (stopevent & RSE_ENTERCONTENTS)
			{
				if (aasworld.areasettings[testareanum].contents & stopcontents)
				{
					route->stopevent = RSE_ENTERCONTENTS;
					route->endarea = testareanum;
					route->endcontents = aasworld.areasettings[testareanum].contents;
					VectorCopy(reach->end, route->endpos);
					route->time += AAS_AreaTravelTime(areanum, origin, reach->start);
					route->time += reach->traveltime;
					return qtrue;
				} //end if
			} //end if
			if (stopevent & RSE_ENTERAREA)
			{
				if (testareanum == stopareanum)
				{
					route->stopevent = RSE_ENTERAREA;
					route->endarea = testareanum;
					route->endcontents = aasworld.areasettings[testareanum].contents;
					VectorCopy(reach->start, route->endpos);
					return qtrue;
				} //end if
			} //end if
		} //end for

		route->time += AAS_AreaTravelTime(areanum, origin, reach->start);
		route->time += reach->traveltime;
		route->endarea = reach->areanum;
		route->endcontents = aasworld.areasettings[reach->areanum].contents;
		route->endtravelflags = AAS_TravelFlagForType_inline(reach->traveltype);
		VectorCopy(reach->end, route->endpos);
		//
		curareanum = reach->areanum;
		VectorCopy(reach->end, curorigin);
		//
		if (maxtime && route->time > maxtime)
			break;
	} //end while
	if (curareanum != goalareanum)
		return qfalse;
	return qtrue;
}