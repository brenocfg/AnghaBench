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
struct zoneref {scalar_t__ zone; } ;
struct zone {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  enum zone_type { ____Placeholder_zone_type } zone_type ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct zone* zonelist_zone (struct zoneref*) ; 
 int zonelist_zone_idx (struct zoneref*) ; 
 int /*<<< orphan*/  zref_in_nodemask (struct zoneref*,int /*<<< orphan*/ *) ; 

struct zoneref *next_zones_zonelist(struct zoneref *z,
					enum zone_type highest_zoneidx,
					nodemask_t *nodes,
					struct zone **zone)
{
	/*
	 * Find the next suitable zone to use for the allocation.
	 * Only filter based on nodemask if it's set
	 */
	if (likely(nodes == NULL))
		while (zonelist_zone_idx(z) > highest_zoneidx)
			z++;
	else
		while (zonelist_zone_idx(z) > highest_zoneidx ||
				(z->zone && !zref_in_nodemask(z, nodes)))
			z++;

	*zone = zonelist_zone(z);
	return z;
}