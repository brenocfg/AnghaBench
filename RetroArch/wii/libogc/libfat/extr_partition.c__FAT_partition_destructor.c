#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* nextOpenFile; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cache; TYPE_2__* firstOpenFile; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ FILE_STRUCT ;

/* Variables and functions */
 int /*<<< orphan*/  _FAT_cache_destructor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_lock_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_mem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  _FAT_partition_writeFSinfo (TYPE_1__*) ; 
 int /*<<< orphan*/  _FAT_syncToDisc (TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 

void _FAT_partition_destructor (PARTITION* partition) {
	FILE_STRUCT* nextFile;

	_FAT_lock(&partition->lock);

	// Synchronize open files
	nextFile = partition->firstOpenFile;
	while (nextFile) {
		_FAT_syncToDisc (nextFile);
		nextFile = nextFile->nextOpenFile;
	}

	// Write out the fs info sector
	_FAT_partition_writeFSinfo(partition);

	// Free memory used by the cache, writing it to disc at the same time
	_FAT_cache_destructor (partition->cache);

	// Unlock the partition and destroy the lock
	_FAT_unlock(&partition->lock);
	_FAT_lock_deinit(&partition->lock);

	// Free memory used by the partition
	_FAT_mem_free (partition);
}