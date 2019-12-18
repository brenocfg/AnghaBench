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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ sectorsPerCluster; int /*<<< orphan*/  cache; int /*<<< orphan*/  bytesPerSector; } ;
typedef  TYPE_1__ PARTITION ;

/* Variables and functions */
 scalar_t__ CLUSTER_ERROR ; 
 scalar_t__ CLUSTER_FREE ; 
 int /*<<< orphan*/  _FAT_cache_writeSectors (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ _FAT_fat_clusterToSector (TYPE_1__*,scalar_t__) ; 
 scalar_t__ _FAT_fat_linkFreeCluster (TYPE_1__*,scalar_t__) ; 
 scalar_t__ _FAT_mem_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_mem_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t _FAT_fat_linkFreeClusterCleared (PARTITION* partition, uint32_t cluster)
{
	uint32_t i;
	uint8_t *emptySector;

	/* Link the cluster */
	uint32_t newCluster = _FAT_fat_linkFreeCluster(partition, cluster);

	if (newCluster == CLUSTER_FREE || newCluster == CLUSTER_ERROR)
		return CLUSTER_ERROR;

	emptySector = (uint8_t*) _FAT_mem_allocate(partition->bytesPerSector);

	/* Clear all the sectors within the cluster */
	memset (emptySector, 0, partition->bytesPerSector);
	for (i = 0; i < partition->sectorsPerCluster; i++)
   {
		_FAT_cache_writeSectors (partition->cache,
			_FAT_fat_clusterToSector (partition, newCluster) + i,
			1, emptySector);
	}

	_FAT_mem_free(emptySector);

	return newCluster;
}