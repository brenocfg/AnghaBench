#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct _reent {void* _errno; } ;
struct TYPE_13__ {int byte; int sector; void* cluster; } ;
struct TYPE_12__ {int filesize; int currentPosition; TYPE_3__ rwPosition; int /*<<< orphan*/  startCluster; TYPE_1__* partition; } ;
struct TYPE_11__ {int bytesPerSector; int bytesPerCluster; unsigned int sectorsPerCluster; int /*<<< orphan*/ * cache; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ FILE_STRUCT ;
typedef  TYPE_3__ FILE_POSITION ;
typedef  int /*<<< orphan*/  CACHE ;

/* Variables and functions */
 void* ENOSPC ; 
 int /*<<< orphan*/  _FAT_cache_writePartialSector (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,void*,void*) ; 
 int /*<<< orphan*/  _FAT_cache_writeSectors (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_check_position_for_next_cluster (struct _reent*,TYPE_3__*,TYPE_1__*,void*,int /*<<< orphan*/ *) ; 
 unsigned int _FAT_fat_clusterToSector (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  _FAT_fat_isValidCluster (TYPE_1__*,void*) ; 
 void* _FAT_fat_lastCluster (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* _FAT_fat_linkFreeCluster (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool _FAT_file_extend_r (struct _reent *r, FILE_STRUCT* file) {
	PARTITION* partition = file->partition;
	CACHE* cache = file->partition->cache;
	FILE_POSITION position;
	uint8_t zeroBuffer [partition->bytesPerSector];
	memset(zeroBuffer, 0, partition->bytesPerSector);
	uint32_t remain;
	uint32_t tempNextCluster;
	unsigned int sector;

	position.byte = file->filesize % partition->bytesPerSector;
	position.sector = (file->filesize % partition->bytesPerCluster) / partition->bytesPerSector;
	// It is assumed that there is always a startCluster
	// This will be true when _FAT_file_extend_r is called from _FAT_write_r
	position.cluster = _FAT_fat_lastCluster (partition, file->startCluster);

	remain = file->currentPosition - file->filesize;

	if ((remain > 0) && (file->filesize > 0) && (position.sector == 0) && (position.byte  == 0)) {
		// Get a new cluster on the edge of a cluster boundary
		tempNextCluster = _FAT_fat_linkFreeCluster(partition, position.cluster);
		if (!_FAT_fat_isValidCluster(partition, tempNextCluster)) {
			// Couldn't get a cluster, so abort
			r->_errno = ENOSPC;
			return false;
		}
		position.cluster = tempNextCluster;
		position.sector = 0;
	}

	if (remain + position.byte < partition->bytesPerSector) {
		// Only need to clear to the end of the sector
		_FAT_cache_writePartialSector (cache, zeroBuffer,
			_FAT_fat_clusterToSector (partition, position.cluster) + position.sector, position.byte, remain);
		position.byte += remain;
	} else {
		if (position.byte > 0) {
			_FAT_cache_writePartialSector (cache, zeroBuffer,
				_FAT_fat_clusterToSector (partition, position.cluster) + position.sector, position.byte,
				partition->bytesPerSector - position.byte);
			remain -= (partition->bytesPerSector - position.byte);
			position.byte = 0;
			position.sector ++;
		}

		while (remain >= partition->bytesPerSector) {
			if (position.sector >= partition->sectorsPerCluster) {
				position.sector = 0;
				// Ran out of clusters so get a new one
				tempNextCluster = _FAT_fat_linkFreeCluster(partition, position.cluster);
				if (!_FAT_fat_isValidCluster(partition, tempNextCluster)) {
					// Couldn't get a cluster, so abort
					r->_errno = ENOSPC;
					return false;
				}
				position.cluster = tempNextCluster;
			}

			sector = _FAT_fat_clusterToSector (partition, position.cluster) + position.sector;
			_FAT_cache_writeSectors (cache, sector, 1, zeroBuffer);

			remain -= partition->bytesPerSector;
			position.sector ++;
		}

      // error already marked
		if (!_FAT_check_position_for_next_cluster(r, &position, partition, remain, NULL))
			return false;

		if (remain > 0)
      {
			_FAT_cache_writePartialSector (cache, zeroBuffer,
				_FAT_fat_clusterToSector (partition, position.cluster) + position.sector, 0, remain);
			position.byte = remain;
		}
	}

	file->rwPosition = position;
	file->filesize = file->currentPosition;
	return true;
}