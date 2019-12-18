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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int numberFreeCluster; int /*<<< orphan*/  firstFree; int /*<<< orphan*/  lastCluster; } ;
struct TYPE_7__ {int numberOfSectors; int sectorsPerCluster; TYPE_1__ fat; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_EOF ; 
 int /*<<< orphan*/  CLUSTER_ERROR ; 
 int /*<<< orphan*/  CLUSTER_FIRST ; 
 int /*<<< orphan*/  CLUSTER_FREE ; 
 int /*<<< orphan*/  _FAT_fat_nextCluster (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_fat_writeFatEntry (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool _FAT_fat_clearLinks (PARTITION* partition, uint32_t cluster)
{
	uint32_t nextCluster;

	if ((cluster < CLUSTER_FIRST) || (cluster > partition->fat.lastCluster /* This will catch CLUSTER_ERROR */))
		return false;

	/* If this clears up more space in the FAT before the current free pointer, move it backwards */
	if (cluster < partition->fat.firstFree)
		partition->fat.firstFree = cluster;

	while ((cluster != CLUSTER_EOF) && (cluster != CLUSTER_FREE) && (cluster != CLUSTER_ERROR))
   {
		/* Store next cluster before erasing the link */
		nextCluster = _FAT_fat_nextCluster (partition, cluster);

		/* Erase the link */
		_FAT_fat_writeFatEntry (partition, cluster, CLUSTER_FREE);

		if(partition->fat.numberFreeCluster < (partition->numberOfSectors/partition->sectorsPerCluster))
			partition->fat.numberFreeCluster++;
		/* Move onto next cluster */
		cluster = nextCluster;
	}

	return true;
}