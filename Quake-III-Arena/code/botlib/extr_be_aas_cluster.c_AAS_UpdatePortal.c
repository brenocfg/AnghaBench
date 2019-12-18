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
struct TYPE_6__ {int areanum; int frontcluster; int backcluster; } ;
typedef  TYPE_2__ aas_portal_t ;
struct TYPE_7__ {size_t firstportal; size_t numportals; } ;
typedef  TYPE_3__ aas_cluster_t ;
struct TYPE_8__ {int numportals; scalar_t__ portalindexsize; int* portalindex; TYPE_3__* clusters; TYPE_1__* areasettings; TYPE_2__* portals; } ;
struct TYPE_5__ {int cluster; int /*<<< orphan*/  contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_Error (char*,...) ; 
 scalar_t__ AAS_MAX_PORTALINDEXSIZE ; 
 int /*<<< orphan*/  AREACONTENTS_CLUSTERPORTAL ; 
 int /*<<< orphan*/  Log_Write (char*,int) ; 
 TYPE_4__ aasworld ; 
 int qfalse ; 
 int qtrue ; 

int AAS_UpdatePortal(int areanum, int clusternum)
{
	int portalnum;
	aas_portal_t *portal;
	aas_cluster_t *cluster;

	//find the portal of the area
	for (portalnum = 1; portalnum < aasworld.numportals; portalnum++)
	{
		if (aasworld.portals[portalnum].areanum == areanum) break;
	} //end for
	//
	if (portalnum == aasworld.numportals)
	{
		AAS_Error("no portal of area %d", areanum);
		return qtrue;
	} //end if
	//
	portal = &aasworld.portals[portalnum];
	//if the portal is already fully updated
	if (portal->frontcluster == clusternum) return qtrue;
	if (portal->backcluster == clusternum) return qtrue;
	//if the portal has no front cluster yet
	if (!portal->frontcluster)
	{
		portal->frontcluster = clusternum;
	} //end if
	//if the portal has no back cluster yet
	else if (!portal->backcluster)
	{
		portal->backcluster = clusternum;
	} //end else if
	else
	{
		//remove the cluster portal flag contents
		aasworld.areasettings[areanum].contents &= ~AREACONTENTS_CLUSTERPORTAL;
		Log_Write("portal area %d is seperating more than two clusters\r\n", areanum);
		return qfalse;
	} //end else
	if (aasworld.portalindexsize >= AAS_MAX_PORTALINDEXSIZE)
	{
		AAS_Error("AAS_MAX_PORTALINDEXSIZE");
		return qtrue;
	} //end if
	//set the area cluster number to the negative portal number
	aasworld.areasettings[areanum].cluster = -portalnum;
	//add the portal to the cluster using the portal index
	cluster = &aasworld.clusters[clusternum];
	aasworld.portalindex[cluster->firstportal + cluster->numportals] = portalnum;
	aasworld.portalindexsize++;
	cluster->numportals++;
	return qtrue;
}