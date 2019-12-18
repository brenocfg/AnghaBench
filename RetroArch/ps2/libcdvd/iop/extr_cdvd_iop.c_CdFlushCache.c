#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cache_size; scalar_t__ cache_offset; scalar_t__ sector_num; scalar_t__ sector_start; scalar_t__ path_depth; int /*<<< orphan*/  valid; int /*<<< orphan*/  pathname; } ;

/* Variables and functions */
 TYPE_1__ CachedDirInfo ; 
 int /*<<< orphan*/  FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int CdFlushCache(void)
{
    strcpy(CachedDirInfo.pathname, "");  // The pathname of the cached directory
    CachedDirInfo.valid = FALSE;         // Cache is not valid
    CachedDirInfo.path_depth = 0;        // 0 = root)
    CachedDirInfo.sector_start = 0;      // The start sector (LBA) of the cached directory
    CachedDirInfo.sector_num = 0;        // The total size of the directory (in sectors)
    CachedDirInfo.cache_offset = 0;      // The offset from sector_start of the cached area
    CachedDirInfo.cache_size = 0;        // The size of the cached directory area (in sectors)

    return TRUE;
}