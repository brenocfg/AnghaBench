#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numareas; TYPE_2__* areasettings; TYPE_1__* reachability; } ;
struct TYPE_5__ {int contents; int numreachableareas; int firstreachablearea; scalar_t__ cluster; } ;
struct TYPE_4__ {int areanum; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_FloodClusterAreas_r (int,int) ; 
 int AREACONTENTS_CLUSTERPORTAL ; 
 TYPE_3__ aasworld ; 
 int qfalse ; 
 int qtrue ; 

int AAS_FloodClusterAreasUsingReachabilities(int clusternum)
{
	int i, j, areanum;

	for (i = 1; i < aasworld.numareas; i++)
	{
		//if this area already has a cluster set
		if (aasworld.areasettings[i].cluster)
			continue;
		//if this area is a cluster portal
		if (aasworld.areasettings[i].contents & AREACONTENTS_CLUSTERPORTAL)
			continue;
		//loop over the reachable areas from this area
		for (j = 0; j < aasworld.areasettings[i].numreachableareas; j++)
		{
			//the reachable area
			areanum = aasworld.reachability[aasworld.areasettings[i].firstreachablearea + j].areanum;
			//if this area is a cluster portal
			if (aasworld.areasettings[areanum].contents & AREACONTENTS_CLUSTERPORTAL)
				continue;
			//if this area has a cluster set
			if (aasworld.areasettings[areanum].cluster)
			{
				if (!AAS_FloodClusterAreas_r(i, clusternum))
					return qfalse;
				i = 0;
				break;
			} //end if
		} //end for
	} //end for
	return qtrue;
}