#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; size_t areanum; size_t cluster; TYPE_3__* prev; TYPE_2__* next; struct TYPE_10__* time_next; } ;
typedef  TYPE_4__ aas_routingcache_t ;
struct TYPE_11__ {TYPE_2__** portalcache; TYPE_2__*** clusterareacache; TYPE_1__* areasettings; TYPE_4__* oldestcache; } ;
struct TYPE_9__ {TYPE_2__* next; } ;
struct TYPE_8__ {TYPE_3__* prev; } ;
struct TYPE_7__ {scalar_t__ cluster; } ;

/* Variables and functions */
 int AAS_ClusterAreaNum (size_t,size_t) ; 
 int /*<<< orphan*/  AAS_FreeRoutingCache (TYPE_4__*) ; 
 scalar_t__ CACHETYPE_AREA ; 
 TYPE_5__ aasworld ; 
 int qfalse ; 
 int qtrue ; 

int AAS_FreeOldestCache(void)
{
	int clusterareanum;
	aas_routingcache_t *cache;

	for (cache = aasworld.oldestcache; cache; cache = cache->time_next) {
		// never free area cache leading towards a portal
		if (cache->type == CACHETYPE_AREA && aasworld.areasettings[cache->areanum].cluster < 0) {
			continue;
		}
		break;
	}
	if (cache) {
		// unlink the cache
		if (cache->type == CACHETYPE_AREA) {
			//number of the area in the cluster
			clusterareanum = AAS_ClusterAreaNum(cache->cluster, cache->areanum);
			// unlink from cluster area cache
			if (cache->prev) cache->prev->next = cache->next;
			else aasworld.clusterareacache[cache->cluster][clusterareanum] = cache->next;
			if (cache->next) cache->next->prev = cache->prev;
		}
		else {
			// unlink from portal cache
			if (cache->prev) cache->prev->next = cache->next;
			else aasworld.portalcache[cache->areanum] = cache->next;
			if (cache->next) cache->next->prev = cache->prev;
		}
		AAS_FreeRoutingCache(cache);
		return qtrue;
	}
	return qfalse;
}