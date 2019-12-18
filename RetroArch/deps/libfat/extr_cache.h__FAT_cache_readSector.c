#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sec_t ;
struct TYPE_4__ {int /*<<< orphan*/  bytesPerSector; } ;
typedef  TYPE_1__ CACHE ;

/* Variables and functions */
 int _FAT_cache_readPartialSector (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool _FAT_cache_readSector (CACHE* cache, void* buffer, sec_t sector) {
	return _FAT_cache_readPartialSector (cache, buffer, sector, 0, cache->bytesPerSector);
}