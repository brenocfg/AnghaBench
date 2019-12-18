#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
typedef  int /*<<< orphan*/  midrangearea_t ;
struct TYPE_11__ {int areanum; int starttraveltime; int goaltraveltime; int extratraveltime; int /*<<< orphan*/  origin; } ;
typedef  TYPE_3__ aas_altroutegoal_t ;
struct TYPE_14__ {int numareas; TYPE_2__* areas; TYPE_1__* areasettings; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_12__ {int starttime; int goaltime; int /*<<< orphan*/  valid; } ;
struct TYPE_10__ {int /*<<< orphan*/  center; } ;
struct TYPE_9__ {int contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AltRoutingFloodCluster_r (int) ; 
 int /*<<< orphan*/  AAS_AreaReachability (int) ; 
 int AAS_AreaTravelTimeToGoalArea (int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  AAS_ShowAreaPolygons (int,int,int /*<<< orphan*/ ) ; 
 int ALTROUTEGOAL_ALL ; 
 int ALTROUTEGOAL_CLUSTERPORTALS ; 
 int ALTROUTEGOAL_VIEWPORTALS ; 
 int AREACONTENTS_CLUSTERPORTAL ; 
 int AREACONTENTS_VIEWPORTAL ; 
 int /*<<< orphan*/  Com_Memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Log_Write (char*,int,int) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int Sys_MilliSeconds () ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ *,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__ aasworld ; 
 TYPE_5__ botimport ; 
 size_t* clusterareas ; 
 TYPE_4__* midrangeareas ; 
 int numclusterareas ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

int AAS_AlternativeRouteGoals(vec3_t start, int startareanum, vec3_t goal, int goalareanum, int travelflags,
										 aas_altroutegoal_t *altroutegoals, int maxaltroutegoals,
										 int type)
{
#ifndef ENABLE_ALTROUTING
	return 0;
#else
	int i, j, bestareanum;
	int numaltroutegoals, nummidrangeareas;
	int starttime, goaltime, goaltraveltime;
	float dist, bestdist;
	vec3_t mid, dir;
#ifdef ALTROUTE_DEBUG
	int startmillisecs;

	startmillisecs = Sys_MilliSeconds();
#endif

	if (!startareanum || !goalareanum)
		return 0;
	//travel time towards the goal area
	goaltraveltime = AAS_AreaTravelTimeToGoalArea(startareanum, start, goalareanum, travelflags);
	//clear the midrange areas
	Com_Memset(midrangeareas, 0, aasworld.numareas * sizeof(midrangearea_t));
	numaltroutegoals = 0;
	//
	nummidrangeareas = 0;
	//
	for (i = 1; i < aasworld.numareas; i++)
	{
		//
		if (!(type & ALTROUTEGOAL_ALL))
		{
			if (!(type & ALTROUTEGOAL_CLUSTERPORTALS && (aasworld.areasettings[i].contents & AREACONTENTS_CLUSTERPORTAL)))
			{
				if (!(type & ALTROUTEGOAL_VIEWPORTALS && (aasworld.areasettings[i].contents & AREACONTENTS_VIEWPORTAL)))
				{
					continue;
				} //end if
			} //end if
		} //end if
		//if the area has no reachabilities
		if (!AAS_AreaReachability(i)) continue;
		//tavel time from the area to the start area
		starttime = AAS_AreaTravelTimeToGoalArea(startareanum, start, i, travelflags);
		if (!starttime) continue;
		//if the travel time from the start to the area is greater than the shortest goal travel time
		if (starttime > (float) 1.1 * goaltraveltime) continue;
		//travel time from the area to the goal area
		goaltime = AAS_AreaTravelTimeToGoalArea(i, NULL, goalareanum, travelflags);
		if (!goaltime) continue;
		//if the travel time from the area to the goal is greater than the shortest goal travel time
		if (goaltime > (float) 0.8 * goaltraveltime) continue;
		//this is a mid range area
		midrangeareas[i].valid = qtrue;
		midrangeareas[i].starttime = starttime;
		midrangeareas[i].goaltime = goaltime;
		Log_Write("%d midrange area %d", nummidrangeareas, i);
		nummidrangeareas++;
	} //end for
	//
	for (i = 1; i < aasworld.numareas; i++)
	{
		if (!midrangeareas[i].valid) continue;
		//get the areas in one cluster
		numclusterareas = 0;
		AAS_AltRoutingFloodCluster_r(i);
		//now we've got a cluster with areas through which an alternative route could go
		//get the 'center' of the cluster
		VectorClear(mid);
		for (j = 0; j < numclusterareas; j++)
		{
			VectorAdd(mid, aasworld.areas[clusterareas[j]].center, mid);
		} //end for
		VectorScale(mid, 1.0 / numclusterareas, mid);
		//get the area closest to the center of the cluster
		bestdist = 999999;
		bestareanum = 0;
		for (j = 0; j < numclusterareas; j++)
		{
			VectorSubtract(mid, aasworld.areas[clusterareas[j]].center, dir);
			dist = VectorLength(dir);
			if (dist < bestdist)
			{
				bestdist = dist;
				bestareanum = clusterareas[j];
			} //end if
		} //end for
		//now we've got an area for an alternative route
		//FIXME: add alternative goal origin
		VectorCopy(aasworld.areas[bestareanum].center, altroutegoals[numaltroutegoals].origin);
		altroutegoals[numaltroutegoals].areanum = bestareanum;
		altroutegoals[numaltroutegoals].starttraveltime = midrangeareas[bestareanum].starttime;
		altroutegoals[numaltroutegoals].goaltraveltime = midrangeareas[bestareanum].goaltime;
		altroutegoals[numaltroutegoals].extratraveltime =
					(midrangeareas[bestareanum].starttime + midrangeareas[bestareanum].goaltime) -
								goaltraveltime;
		numaltroutegoals++;
		//
#ifdef ALTROUTE_DEBUG
		AAS_ShowAreaPolygons(bestareanum, 1, qtrue);
#endif
		//don't return more than the maximum alternative route goals
		if (numaltroutegoals >= maxaltroutegoals) break;
	} //end for
#ifdef ALTROUTE_DEBUG
	botimport.Print(PRT_MESSAGE, "alternative route goals in %d msec\n", Sys_MilliSeconds() - startmillisecs);
#endif
	return numaltroutegoals;
#endif
}