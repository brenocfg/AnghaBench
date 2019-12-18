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
typedef  unsigned int sec_t ;
struct TYPE_6__ {unsigned int numberOfPages; unsigned int sectorsPerPage; unsigned int endOfPartition; int /*<<< orphan*/  disc; TYPE_1__* cacheEntries; } ;
struct TYPE_5__ {unsigned int sector; unsigned int count; unsigned int last_access; int dirty; int /*<<< orphan*/  cache; } ;
typedef  TYPE_1__ CACHE_ENTRY ;
typedef  TYPE_2__ CACHE ;

/* Variables and functions */
 unsigned int CACHE_FREE ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  _FAT_disc_readSectors (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_disc_writeSectors (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 void* accessTime () ; 

__attribute__((used)) static CACHE_ENTRY* _FAT_cache_getPage(CACHE *cache,sec_t sector)
{
	unsigned int i;
	CACHE_ENTRY* cacheEntries = cache->cacheEntries;
	unsigned int numberOfPages = cache->numberOfPages;
	unsigned int sectorsPerPage = cache->sectorsPerPage;

	bool foundFree = false;
	unsigned int oldUsed = 0;
	unsigned int oldAccess = UINT_MAX;

	for(i=0;i<numberOfPages;i++) {
		if(sector>=cacheEntries[i].sector && sector<(cacheEntries[i].sector + cacheEntries[i].count)) {
			cacheEntries[i].last_access = accessTime();
			return &(cacheEntries[i]);
		}

		if(foundFree==false && (cacheEntries[i].sector==CACHE_FREE || cacheEntries[i].last_access<oldAccess)) {
			if(cacheEntries[i].sector==CACHE_FREE) foundFree = true;
			oldUsed = i;
			oldAccess = cacheEntries[i].last_access;
		}
	}

	if(foundFree==false && cacheEntries[oldUsed].dirty==true) {
		if(!_FAT_disc_writeSectors(cache->disc,cacheEntries[oldUsed].sector,cacheEntries[oldUsed].count,cacheEntries[oldUsed].cache)) return NULL;
		cacheEntries[oldUsed].dirty = false;
	}

	sector = (sector/sectorsPerPage)*sectorsPerPage; // align base sector to page size
	sec_t next_page = sector + sectorsPerPage;
	if(next_page > cache->endOfPartition)	next_page = cache->endOfPartition;

	if(!_FAT_disc_readSectors(cache->disc,sector,next_page-sector,cacheEntries[oldUsed].cache)) return NULL;

	cacheEntries[oldUsed].sector = sector;
	cacheEntries[oldUsed].count = next_page-sector;
	cacheEntries[oldUsed].last_access = accessTime();

	return &(cacheEntries[oldUsed]);
}