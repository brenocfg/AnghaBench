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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ sec_t ;
struct TYPE_4__ {scalar_t__ lastCluster; scalar_t__ fatStart; } ;
struct TYPE_5__ {int filesysType; scalar_t__ bytesPerSector; int /*<<< orphan*/  cache; TYPE_1__ fat; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 scalar_t__ CLUSTER_FIRST ; 
#define  FS_FAT12 131 
#define  FS_FAT16 130 
#define  FS_FAT32 129 
#define  FS_UNKNOWN 128 
 int /*<<< orphan*/  _FAT_cache_readLittleEndianValue (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  _FAT_cache_writeLittleEndianValue (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 

__attribute__((used)) static bool _FAT_fat_writeFatEntry (PARTITION* partition, uint32_t cluster, uint32_t value) {
	sec_t sector;
	int offset;
	uint32_t oldValue;

	if ((cluster < CLUSTER_FIRST) || (cluster > partition->fat.lastCluster /* This will catch CLUSTER_ERROR */))
	{
		return false;
	}

	switch (partition->filesysType)
	{
		case FS_UNKNOWN:
			return false;
			break;

		case FS_FAT12:
			sector = partition->fat.fatStart + (((cluster * 3) / 2) / partition->bytesPerSector);
			offset = ((cluster * 3) / 2) % partition->bytesPerSector;

			if (cluster & 0x01) {

				_FAT_cache_readLittleEndianValue (partition->cache, &oldValue, sector, offset, sizeof(u8));

				value = (value << 4) | (oldValue & 0x0F);

				_FAT_cache_writeLittleEndianValue (partition->cache, value & 0xFF, sector, offset, sizeof(u8));

				offset++;
				if (offset >= partition->bytesPerSector) {
					offset = 0;
					sector++;
				}

				_FAT_cache_writeLittleEndianValue (partition->cache, (value >> 8) & 0xFF, sector, offset, sizeof(u8));

			} else {

				_FAT_cache_writeLittleEndianValue (partition->cache, value, sector, offset, sizeof(u8));

				offset++;
				if (offset >= partition->bytesPerSector) {
					offset = 0;
					sector++;
				}

				_FAT_cache_readLittleEndianValue (partition->cache, &oldValue, sector, offset, sizeof(u8));

				value = ((value >> 8) & 0x0F) | (oldValue & 0xF0);

				_FAT_cache_writeLittleEndianValue (partition->cache, value, sector, offset, sizeof(u8));
			}

			break;

		case FS_FAT16:
			sector = partition->fat.fatStart + ((cluster << 1) / partition->bytesPerSector);
			offset = (cluster % (partition->bytesPerSector >> 1)) << 1;

			_FAT_cache_writeLittleEndianValue (partition->cache, value, sector, offset, sizeof(u16));

			break;

		case FS_FAT32:
			sector = partition->fat.fatStart + ((cluster << 2) / partition->bytesPerSector);
			offset = (cluster % (partition->bytesPerSector >> 2)) << 2;

			_FAT_cache_writeLittleEndianValue (partition->cache, value, sector, offset, sizeof(u32));

			break;

		default:
			return false;
			break;
	}

	return true;
}