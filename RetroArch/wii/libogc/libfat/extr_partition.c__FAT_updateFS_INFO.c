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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  numberLastAllocCluster; int /*<<< orphan*/  numberFreeCluster; } ;
struct TYPE_6__ {int /*<<< orphan*/  fsInfoSector; int /*<<< orphan*/  disc; TYPE_1__ fat; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 int /*<<< orphan*/  FSIB_numberLastAllocCluster ; 
 int /*<<< orphan*/  FSIB_numberOfFreeCluster ; 
 int /*<<< orphan*/  _FAT_disc_writeSectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_fat_freeClusterCount (TYPE_2__*) ; 
 int /*<<< orphan*/  u32_to_u8array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _FAT_updateFS_INFO(PARTITION * partition, uint8_t *sectorBuffer) {
	partition->fat.numberFreeCluster = _FAT_fat_freeClusterCount(partition);
	u32_to_u8array(sectorBuffer, FSIB_numberOfFreeCluster, partition->fat.numberFreeCluster);
	u32_to_u8array(sectorBuffer, FSIB_numberLastAllocCluster, partition->fat.numberLastAllocCluster);
	_FAT_disc_writeSectors (partition->disc, partition->fsInfoSector, 1, sectorBuffer);
}