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
struct TYPE_6__ {TYPE_2__* portals; TYPE_1__* areasettings; } ;
struct TYPE_5__ {int frontcluster; int* clusterareanum; } ;
struct TYPE_4__ {int cluster; int clusterareanum; } ;

/* Variables and functions */
 TYPE_3__ aasworld ; 

__inline int AAS_ClusterAreaNum(int cluster, int areanum)
{
	int side, areacluster;

	areacluster = aasworld.areasettings[areanum].cluster;
	if (areacluster > 0) return aasworld.areasettings[areanum].clusterareanum;
	else
	{
/*#ifdef ROUTING_DEBUG
		if (aasworld.portals[-areacluster].frontcluster != cluster &&
				aasworld.portals[-areacluster].backcluster != cluster)
		{
			botimport.Print(PRT_ERROR, "portal %d: does not belong to cluster %d\n"
											, -areacluster, cluster);
		} //end if
#endif //ROUTING_DEBUG*/
		side = aasworld.portals[-areacluster].frontcluster != cluster;
		return aasworld.portals[-areacluster].clusterareanum[side];
	} //end else
}