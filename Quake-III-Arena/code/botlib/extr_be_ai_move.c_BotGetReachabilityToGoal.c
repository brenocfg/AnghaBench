#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct bot_avoidspot_s {int dummy; } ;
struct TYPE_8__ {int areanum; } ;
typedef  TYPE_1__ bot_goal_t ;
struct TYPE_9__ {int areanum; scalar_t__ traveltime; int /*<<< orphan*/  end; } ;
typedef  TYPE_2__ aas_reachability_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 scalar_t__ AAS_AreaDoNotEnter (int) ; 
 int AAS_AreaTravelTimeToGoalArea (int,int /*<<< orphan*/ ,int,int) ; 
 int AAS_NextAreaReachability (int,int) ; 
 int /*<<< orphan*/  AAS_ReachabilityFromNum (int,TYPE_2__*) ; 
 float AAS_Time () ; 
 int AVOIDREACH_TRIES ; 
 scalar_t__ BotAvoidSpots (int /*<<< orphan*/ ,TYPE_2__*,struct bot_avoidspot_s*,int) ; 
 int /*<<< orphan*/  BotValidTravel (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int MAX_AVOIDREACH ; 
 int MOVERESULT_BLOCKEDBYAVOIDSPOT ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int TFL_DONOTENTER ; 
 scalar_t__ bot_developer ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

int BotGetReachabilityToGoal(vec3_t origin, int areanum,
									  int lastgoalareanum, int lastareanum,
									  int *avoidreach, float *avoidreachtimes, int *avoidreachtries,
									  bot_goal_t *goal, int travelflags, int movetravelflags,
									  struct bot_avoidspot_s *avoidspots, int numavoidspots, int *flags)
{
	int i, t, besttime, bestreachnum, reachnum;
	aas_reachability_t reach;

	//if not in a valid area
	if (!areanum) return 0;
	//
	if (AAS_AreaDoNotEnter(areanum) || AAS_AreaDoNotEnter(goal->areanum))
	{
		travelflags |= TFL_DONOTENTER;
		movetravelflags |= TFL_DONOTENTER;
	} //end if
	//use the routing to find the next area to go to
	besttime = 0;
	bestreachnum = 0;
	//
	for (reachnum = AAS_NextAreaReachability(areanum, 0); reachnum;
		reachnum = AAS_NextAreaReachability(areanum, reachnum))
	{
#ifdef AVOIDREACH
		//check if it isn't an reachability to avoid
		for (i = 0; i < MAX_AVOIDREACH; i++)
		{
			if (avoidreach[i] == reachnum && avoidreachtimes[i] >= AAS_Time()) break;
		} //end for
		if (i != MAX_AVOIDREACH && avoidreachtries[i] > AVOIDREACH_TRIES)
		{
#ifdef DEBUG
			if (bot_developer)
			{
				botimport.Print(PRT_MESSAGE, "avoiding reachability %d\n", avoidreach[i]);
			} //end if
#endif //DEBUG
			continue;
		} //end if
#endif //AVOIDREACH
		//get the reachability from the number
		AAS_ReachabilityFromNum(reachnum, &reach);
		//NOTE: do not go back to the previous area if the goal didn't change
		//NOTE: is this actually avoidance of local routing minima between two areas???
		if (lastgoalareanum == goal->areanum && reach.areanum == lastareanum) continue;
		//if (AAS_AreaContentsTravelFlags(reach.areanum) & ~travelflags) continue;
		//if the travel isn't valid
		if (!BotValidTravel(origin, &reach, movetravelflags)) continue;
		//get the travel time
		t = AAS_AreaTravelTimeToGoalArea(reach.areanum, reach.end, goal->areanum, travelflags);
		//if the goal area isn't reachable from the reachable area
		if (!t) continue;
		//if the bot should not use this reachability to avoid bad spots
		if (BotAvoidSpots(origin, &reach, avoidspots, numavoidspots)) {
			if (flags) {
				*flags |= MOVERESULT_BLOCKEDBYAVOIDSPOT;
			}
			continue;
		}
		//add the travel time towards the area
		t += reach.traveltime;// + AAS_AreaTravelTime(areanum, origin, reach.start);
		//if the travel time is better than the ones already found
		if (!besttime || t < besttime)
		{
			besttime = t;
			bestreachnum = reachnum;
		} //end if
	} //end for
	//
	return bestreachnum;
}