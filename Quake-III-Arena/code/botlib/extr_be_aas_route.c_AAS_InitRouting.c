#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  AAS_CalculateAreaTravelTimes () ; 
 int /*<<< orphan*/  AAS_CreateReversedReachability () ; 
 int /*<<< orphan*/  AAS_InitAreaContentsTravelFlags () ; 
 int /*<<< orphan*/  AAS_InitClusterAreaCache () ; 
 int /*<<< orphan*/  AAS_InitPortalCache () ; 
 int /*<<< orphan*/  AAS_InitPortalMaxTravelTimes () ; 
 int /*<<< orphan*/  AAS_InitReachabilityAreas () ; 
 int /*<<< orphan*/  AAS_InitRoutingUpdate () ; 
 int /*<<< orphan*/  AAS_InitTravelFlagFromType () ; 
 int /*<<< orphan*/  AAS_ReadRouteCache () ; 
 scalar_t__ LibVarValue (char*,char*) ; 
 int max_routingcachesize ; 
 scalar_t__ numareacacheupdates ; 
 scalar_t__ numportalcacheupdates ; 
 scalar_t__ routingcachesize ; 

void AAS_InitRouting(void)
{
	AAS_InitTravelFlagFromType();
	//
	AAS_InitAreaContentsTravelFlags();
	//initialize the routing update fields
	AAS_InitRoutingUpdate();
	//create reversed reachability links used by the routing update algorithm
	AAS_CreateReversedReachability();
	//initialize the cluster cache
	AAS_InitClusterAreaCache();
	//initialize portal cache
	AAS_InitPortalCache();
	//initialize the area travel times
	AAS_CalculateAreaTravelTimes();
	//calculate the maximum travel times through portals
	AAS_InitPortalMaxTravelTimes();
	//get the areas reachabilities go through
	AAS_InitReachabilityAreas();
	//
#ifdef ROUTING_DEBUG
	numareacacheupdates = 0;
	numportalcacheupdates = 0;
#endif //ROUTING_DEBUG
	//
	routingcachesize = 0;
	max_routingcachesize = 1024 * (int) LibVarValue("max_routingcache", "4096");
	// read any routing cache if available
	AAS_ReadRouteCache();
}