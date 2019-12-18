#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ sec_t ;
struct TYPE_7__ {scalar_t__ bytesPerSector; } ;
struct TYPE_6__ {scalar_t__ sector; scalar_t__ count; scalar_t__ cache; } ;
typedef  TYPE_1__ CACHE_ENTRY ;
typedef  TYPE_2__ CACHE ;

/* Variables and functions */
 TYPE_1__* _FAT_cache_getPage (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

bool _FAT_cache_readSectors(CACHE *cache,sec_t sector,sec_t numSectors,void *buffer)
{
	sec_t sec;
	sec_t secs_to_read;
	CACHE_ENTRY *entry;
	uint8_t *dest = (uint8_t *)buffer;

	while(numSectors>0)
   {
		entry = _FAT_cache_getPage(cache,sector);
		if(entry==NULL) return false;

		sec = sector - entry->sector;
		secs_to_read = entry->count - sec;
		if(secs_to_read>numSectors) secs_to_read = numSectors;

		memcpy(dest,entry->cache + (sec*cache->bytesPerSector),(secs_to_read*cache->bytesPerSector));

		dest += (secs_to_read*cache->bytesPerSector);
		sector += secs_to_read;
		numSectors -= secs_to_read;
	}

	return true;
}