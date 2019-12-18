#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int numberOfPages; struct TYPE_5__* cacheEntries; struct TYPE_5__* cache; } ;
typedef  TYPE_1__ CACHE ;

/* Variables and functions */
 int /*<<< orphan*/  _FAT_cache_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  _FAT_mem_free (TYPE_1__*) ; 

void _FAT_cache_destructor (CACHE* cache)
{
	unsigned int i;
	/* Clear out cache before destroying it */
	_FAT_cache_flush(cache);

	/* Free memory in reverse allocation order */
	for (i = 0; i < cache->numberOfPages; i++)
		_FAT_mem_free (cache->cacheEntries[i].cache);
	_FAT_mem_free (cache->cacheEntries);
	_FAT_mem_free (cache);
}