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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ lastCluster; scalar_t__ firstFree; scalar_t__ numberLastAllocCluster; scalar_t__ numberFreeCluster; } ;
struct TYPE_7__ {TYPE_1__ fat; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 scalar_t__ CLUSTER_EOF ; 
 scalar_t__ CLUSTER_ERROR ; 
 scalar_t__ CLUSTER_FIRST ; 
 scalar_t__ CLUSTER_FREE ; 
 scalar_t__ _FAT_fat_nextCluster (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  _FAT_fat_writeFatEntry (TYPE_2__*,scalar_t__,scalar_t__) ; 

uint32_t _FAT_fat_linkFreeCluster(PARTITION* partition, uint32_t cluster) {
	uint32_t firstFree;
	uint32_t curLink;
	uint32_t lastCluster;
	bool loopedAroundFAT = false;

	lastCluster =  partition->fat.lastCluster;

	if (cluster > lastCluster) {
		return CLUSTER_ERROR;
	}

	// Check if the cluster already has a link, and return it if so
	curLink = _FAT_fat_nextCluster(partition, cluster);
	if ((curLink >= CLUSTER_FIRST) && (curLink <= lastCluster)) {
		return curLink;	// Return the current link - don't allocate a new one
	}

	// Get a free cluster
	firstFree = partition->fat.firstFree;
	// Start at first valid cluster
	if (firstFree < CLUSTER_FIRST) {
		firstFree = CLUSTER_FIRST;
	}

	// Search until a free cluster is found
	while (_FAT_fat_nextCluster(partition, firstFree) != CLUSTER_FREE) {
		firstFree++;
		if (firstFree > lastCluster) {
			if (loopedAroundFAT) {
				// If couldn't get a free cluster then return an error
				partition->fat.firstFree = firstFree;
				return CLUSTER_ERROR;
			} else {
				// Try looping back to the beginning of the FAT
				// This was suggested by loopy
				firstFree = CLUSTER_FIRST;
				loopedAroundFAT = true;
			}
		}
	}
	partition->fat.firstFree = firstFree;
	if(partition->fat.numberFreeCluster)
		partition->fat.numberFreeCluster--;
	partition->fat.numberLastAllocCluster = firstFree;

	if ((cluster >= CLUSTER_FIRST) && (cluster <= lastCluster))
	{
		// Update the linked from FAT entry
		_FAT_fat_writeFatEntry (partition, cluster, firstFree);
	}
	// Create the linked to FAT entry
	_FAT_fat_writeFatEntry (partition, firstFree, CLUSTER_EOF);

	return firstFree;
}