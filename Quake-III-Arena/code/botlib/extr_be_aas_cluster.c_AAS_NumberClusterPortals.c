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
struct TYPE_4__ {int frontcluster; scalar_t__* clusterareanum; } ;
typedef  TYPE_1__ aas_portal_t ;
struct TYPE_5__ {int numportals; int firstportal; int /*<<< orphan*/  numareas; } ;
typedef  TYPE_2__ aas_cluster_t ;
struct TYPE_6__ {int* portalindex; TYPE_1__* portals; TYPE_2__* clusters; } ;

/* Variables and functions */
 TYPE_3__ aasworld ; 

void AAS_NumberClusterPortals(int clusternum)
{
	int i, portalnum;
	aas_cluster_t *cluster;
	aas_portal_t *portal;

	cluster = &aasworld.clusters[clusternum];
	for (i = 0; i < cluster->numportals; i++)
	{
		portalnum = aasworld.portalindex[cluster->firstportal + i];
		portal = &aasworld.portals[portalnum];
		if (portal->frontcluster == clusternum)
		{
			portal->clusterareanum[0] = cluster->numareas++;
		} //end if
		else
		{
			portal->clusterareanum[1] = cluster->numareas++;
		} //end else
	} //end for
}