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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ sec_t ;
struct TYPE_4__ {scalar_t__ fatStart; } ;
struct TYPE_5__ {int filesysType; scalar_t__ bytesPerSector; int /*<<< orphan*/  cache; TYPE_1__ fat; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 scalar_t__ CLUSTER_EOF ; 
 scalar_t__ CLUSTER_ERROR ; 
 scalar_t__ CLUSTER_FREE ; 
#define  FS_FAT12 131 
#define  FS_FAT16 130 
#define  FS_FAT32 129 
#define  FS_UNKNOWN 128 
 int /*<<< orphan*/  _FAT_cache_readLittleEndianValue (int /*<<< orphan*/ ,...) ; 

uint32_t _FAT_fat_nextCluster(PARTITION* partition, uint32_t cluster)
{
	uint32_t nextCluster = CLUSTER_FREE;
	sec_t sector;
	int offset;

	if (cluster == CLUSTER_FREE) {
		return CLUSTER_FREE;
	}

	switch (partition->filesysType)
	{
		case FS_UNKNOWN:
			return CLUSTER_ERROR;
			break;

		case FS_FAT12:
		{
			u32 nextCluster_h;
			sector = partition->fat.fatStart + (((cluster * 3) / 2) / partition->bytesPerSector);
			offset = ((cluster * 3) / 2) % partition->bytesPerSector;

			_FAT_cache_readLittleEndianValue (partition->cache, &nextCluster, sector, offset, sizeof(u8));

			offset++;

			if (offset >= partition->bytesPerSector) {
				offset = 0;
				sector++;
			}
			nextCluster_h = 0;

			_FAT_cache_readLittleEndianValue (partition->cache, &nextCluster_h, sector, offset, sizeof(u8));
			nextCluster |= (nextCluster_h << 8);

			if (cluster & 0x01) {
				nextCluster = nextCluster >> 4;
			} else 	{
				nextCluster &= 0x0FFF;
			}

			if (nextCluster >= 0x0FF7)
			{
				nextCluster = CLUSTER_EOF;
			}

			break;
		}
		case FS_FAT16:
			sector = partition->fat.fatStart + ((cluster << 1) / partition->bytesPerSector);
			offset = (cluster % (partition->bytesPerSector >> 1)) << 1;

			_FAT_cache_readLittleEndianValue (partition->cache, &nextCluster, sector, offset, sizeof(u16));

			if (nextCluster >= 0xFFF7) {
				nextCluster = CLUSTER_EOF;
			}
			break;

		case FS_FAT32:
			sector = partition->fat.fatStart + ((cluster << 2) / partition->bytesPerSector);
			offset = (cluster % (partition->bytesPerSector >> 2)) << 2;

			_FAT_cache_readLittleEndianValue (partition->cache, &nextCluster, sector, offset, sizeof(u32));

			if (nextCluster >= 0x0FFFFFF7) {
				nextCluster = CLUSTER_EOF;
			}
			break;

		default:
			return CLUSTER_ERROR;
			break;
	}

	return nextCluster;
}