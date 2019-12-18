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
typedef  unsigned int sec_t ;
struct TYPE_7__ {unsigned int bytesPerSector; } ;
struct TYPE_6__ {unsigned int sector; int dirty; scalar_t__ cache; } ;
typedef  TYPE_1__ CACHE_ENTRY ;
typedef  TYPE_2__ CACHE ;

/* Variables and functions */
 TYPE_1__* _FAT_cache_getPage (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 

bool _FAT_cache_eraseWritePartialSector (CACHE* cache, const void* buffer, sec_t sector, unsigned int offset, size_t size)
{
	sec_t sec;
	CACHE_ENTRY *entry;

	if (offset + size > cache->bytesPerSector) return false;

	entry = _FAT_cache_getPage(cache,sector);
	if(entry==NULL) return false;

	sec = sector - entry->sector;
	memset(entry->cache + (sec*cache->bytesPerSector),0,cache->bytesPerSector);
	memcpy(entry->cache + ((sec*cache->bytesPerSector) + offset),buffer,size);

	entry->dirty = true;
	return true;
}