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
struct TYPE_6__ {unsigned int numberOfPages; TYPE_1__* cacheEntries; } ;
struct TYPE_5__ {int dirty; scalar_t__ count; scalar_t__ last_access; int /*<<< orphan*/  sector; } ;
typedef  TYPE_2__ CACHE ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_FREE ; 
 int /*<<< orphan*/  _FAT_cache_flush (TYPE_2__*) ; 

void _FAT_cache_invalidate (CACHE* cache)
{
	unsigned int i;
	_FAT_cache_flush(cache);
	for (i = 0; i < cache->numberOfPages; i++)
   {
		cache->cacheEntries[i].sector = CACHE_FREE;
		cache->cacheEntries[i].last_access = 0;
		cache->cacheEntries[i].count = 0;
		cache->cacheEntries[i].dirty = false;
	}
}