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
struct TYPE_10__ {size_t cluster; size_t areanum; unsigned short tmptraveltime; scalar_t__ inlist; struct TYPE_10__* next; struct TYPE_10__* prev; } ;
typedef  TYPE_2__ aas_routingupdate_t ;
struct TYPE_11__ {size_t cluster; size_t areanum; unsigned short starttraveltime; unsigned short* traveltimes; int /*<<< orphan*/  travelflags; } ;
typedef  TYPE_3__ aas_routingcache_t ;
struct TYPE_12__ {scalar_t__ areanum; size_t frontcluster; size_t backcluster; } ;
typedef  TYPE_4__ aas_portal_t ;
struct TYPE_13__ {int numportals; int firstportal; int numreachabilityareas; } ;
typedef  TYPE_5__ aas_cluster_t ;
struct TYPE_14__ {size_t numportals; int* portalindex; unsigned short* portalmaxtraveltimes; TYPE_2__* portalupdate; TYPE_4__* portals; TYPE_5__* clusters; TYPE_1__* areasettings; } ;
struct TYPE_9__ {int cluster; } ;

/* Variables and functions */
 int AAS_ClusterAreaNum (size_t,scalar_t__) ; 
 TYPE_3__* AAS_GetAreaRoutingCache (size_t,size_t,int /*<<< orphan*/ ) ; 
 TYPE_6__ aasworld ; 
 int /*<<< orphan*/  numportalcacheupdates ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

void AAS_UpdatePortalRoutingCache(aas_routingcache_t *portalcache)
{
	int i, portalnum, clusterareanum, clusternum;
	unsigned short int t;
	aas_portal_t *portal;
	aas_cluster_t *cluster;
	aas_routingcache_t *cache;
	aas_routingupdate_t *updateliststart, *updatelistend, *curupdate, *nextupdate;

#ifdef ROUTING_DEBUG
	numportalcacheupdates++;
#endif //ROUTING_DEBUG
	//clear the routing update fields
//	Com_Memset(aasworld.portalupdate, 0, (aasworld.numportals+1) * sizeof(aas_routingupdate_t));
	//
	curupdate = &aasworld.portalupdate[aasworld.numportals];
	curupdate->cluster = portalcache->cluster;
	curupdate->areanum = portalcache->areanum;
	curupdate->tmptraveltime = portalcache->starttraveltime;
	//if the start area is a cluster portal, store the travel time for that portal
	clusternum = aasworld.areasettings[portalcache->areanum].cluster;
	if (clusternum < 0)
	{
		portalcache->traveltimes[-clusternum] = portalcache->starttraveltime;
	} //end if
	//put the area to start with in the current read list
	curupdate->next = NULL;
	curupdate->prev = NULL;
	updateliststart = curupdate;
	updatelistend = curupdate;
	//while there are updates in the current list
	while (updateliststart)
	{
		curupdate = updateliststart;
		//remove the current update from the list
		if (curupdate->next) curupdate->next->prev = NULL;
		else updatelistend = NULL;
		updateliststart = curupdate->next;
		//current update is removed from the list
		curupdate->inlist = qfalse;
		//
		cluster = &aasworld.clusters[curupdate->cluster];
		//
		cache = AAS_GetAreaRoutingCache(curupdate->cluster,
								curupdate->areanum, portalcache->travelflags);
		//take all portals of the cluster
		for (i = 0; i < cluster->numportals; i++)
		{
			portalnum = aasworld.portalindex[cluster->firstportal + i];
			portal = &aasworld.portals[portalnum];
			//if this is the portal of the current update continue
			if (portal->areanum == curupdate->areanum) continue;
			//
			clusterareanum = AAS_ClusterAreaNum(curupdate->cluster, portal->areanum);
			if (clusterareanum >= cluster->numreachabilityareas) continue;
			//
			t = cache->traveltimes[clusterareanum];
			if (!t) continue;
			t += curupdate->tmptraveltime;
			//
			if (!portalcache->traveltimes[portalnum] ||
					portalcache->traveltimes[portalnum] > t)
			{
				portalcache->traveltimes[portalnum] = t;
				nextupdate = &aasworld.portalupdate[portalnum];
				if (portal->frontcluster == curupdate->cluster)
				{
					nextupdate->cluster = portal->backcluster;
				} //end if
				else
				{
					nextupdate->cluster = portal->frontcluster;
				} //end else
				nextupdate->areanum = portal->areanum;
				//add travel time through the actual portal area for the next update
				nextupdate->tmptraveltime = t + aasworld.portalmaxtraveltimes[portalnum];
				if (!nextupdate->inlist)
				{
					// we add the update to the end of the list
					// we could also use a B+ tree to have a real sorted list
					// on travel time which makes for faster routing updates
					nextupdate->next = NULL;
					nextupdate->prev = updatelistend;
					if (updatelistend) updatelistend->next = nextupdate;
					else updateliststart = nextupdate;
					updatelistend = nextupdate;
					nextupdate->inlist = qtrue;
				} //end if
			} //end if
		} //end for
	} //end while
}