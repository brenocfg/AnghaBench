#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  numberLastAllocCluster; int /*<<< orphan*/  numberFreeCluster; } ;
struct TYPE_5__ {scalar_t__ filesysType; int /*<<< orphan*/  fsInfoSector; int /*<<< orphan*/  disc; TYPE_1__ fat; int /*<<< orphan*/  bytesPerSector; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 int FSIB_SIG1 ; 
 int FSIB_SIG2 ; 
 int /*<<< orphan*/  FSIB_numberLastAllocCluster ; 
 int /*<<< orphan*/  FSIB_numberOfFreeCluster ; 
 scalar_t__ FS_FAT32 ; 
 int /*<<< orphan*/  FS_INFO_SIG1 ; 
 int /*<<< orphan*/  FS_INFO_SIG2 ; 
 int /*<<< orphan*/  _FAT_disc_readSectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_disc_writeSectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ _FAT_mem_align (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_mem_free (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32_to_u8array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _FAT_partition_writeFSinfo(PARTITION * partition)
{
   uint8_t *sectorBuffer = NULL;
	if(partition->filesysType != FS_FAT32)
		return;

	sectorBuffer = (uint8_t*) _FAT_mem_align(partition->bytesPerSector);
	if (!sectorBuffer)
      return;
	memset(sectorBuffer, 0, partition->bytesPerSector);
	/* Read first sector of disc */
	if (!_FAT_disc_readSectors (partition->disc, partition->fsInfoSector, 1, sectorBuffer))
   {
		_FAT_mem_free(sectorBuffer);
		return;
	}

	if(memcmp(sectorBuffer+FSIB_SIG1, FS_INFO_SIG1, 4) || memcmp(sectorBuffer+FSIB_SIG2, FS_INFO_SIG2, 4))
   {
		_FAT_mem_free(sectorBuffer);
		return;
	}

	u32_to_u8array(sectorBuffer, FSIB_numberOfFreeCluster, partition->fat.numberFreeCluster);
	u32_to_u8array(sectorBuffer, FSIB_numberLastAllocCluster, partition->fat.numberLastAllocCluster);

	/* Write first sector of disc */
	_FAT_disc_writeSectors (partition->disc, partition->fsInfoSector, 1, sectorBuffer);
	_FAT_mem_free(sectorBuffer);
}