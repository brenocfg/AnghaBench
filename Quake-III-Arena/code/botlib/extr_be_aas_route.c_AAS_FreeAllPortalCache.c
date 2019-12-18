#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ aas_routingcache_t ;
struct TYPE_6__ {int numareas; TYPE_1__** portalcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_FreeRoutingCache (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeMemory (TYPE_1__**) ; 
 TYPE_2__ aasworld ; 

void AAS_FreeAllPortalCache(void)
{
	int i;
	aas_routingcache_t *cache, *nextcache;

	//free all portal cache if existing
	if (!aasworld.portalcache) return;
	//free portal caches
	for (i = 0; i < aasworld.numareas; i++)
	{
		for (cache = aasworld.portalcache[i]; cache; cache = nextcache)
		{
			nextcache = cache->next;
			AAS_FreeRoutingCache(cache);
		} //end for
		aasworld.portalcache[i] = NULL;
	} //end for
	FreeMemory(aasworld.portalcache);
	aasworld.portalcache = NULL;
}