#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct _reent {void* _errno; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  len ;
struct TYPE_11__ {int cluster; int sector; int byte; } ;
struct TYPE_10__ {int filesize; scalar_t__ startCluster; int currentPosition; int modified; TYPE_3__ appendPosition; scalar_t__ append; TYPE_3__ rwPosition; TYPE_1__* partition; int /*<<< orphan*/  write; int /*<<< orphan*/  inUse; } ;
struct TYPE_9__ {int bytesPerCluster; int bytesPerSector; int sectorsPerCluster; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ FILE_STRUCT ;
typedef  TYPE_3__ FILE_POSITION ;

/* Variables and functions */
 scalar_t__ CLUSTER_FREE ; 
 void* EBADF ; 
 void* EFBIG ; 
 void* EINVAL ; 
 void* ENOSPC ; 
 scalar_t__ FILE_MAX_SIZE ; 
 int /*<<< orphan*/  _FAT_fat_clearLinks (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _FAT_fat_isValidCluster (TYPE_1__*,int) ; 
 int _FAT_fat_linkFreeCluster (TYPE_1__*,scalar_t__) ; 
 int _FAT_fat_trimChain (TYPE_1__*,int,unsigned int) ; 
 int /*<<< orphan*/  _FAT_file_extend_r (struct _reent*,TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 

int _FAT_ftruncate_r (struct _reent *r, void *fd, off_t len) {
	FILE_STRUCT* file = (FILE_STRUCT*)  fd;
	PARTITION* partition;
	int ret=0;
	uint32_t newSize = (uint32_t)len;

	if (len < 0) {
		// Trying to truncate to a negative size
		r->_errno = EINVAL;
		return -1;
	}

	if ((sizeof(len) > 4) && len > (off_t)FILE_MAX_SIZE) {
		// Trying to extend the file beyond what FAT supports
		r->_errno = EFBIG;
		return -1;
	}

	if (!file || !file->inUse) {
		// invalid file
		r->_errno = EBADF;
		return -1;
	}

	if (!file->write) {
		// Read-only file
		r->_errno = EINVAL;
		return -1;
	}

	partition = file->partition;
	_FAT_lock(&partition->lock);

	if (newSize > file->filesize) {
		// Expanding the file
		FILE_POSITION savedPosition;
		uint32_t savedOffset;
		// Get a new cluster for the start of the file if required
		if (file->startCluster == CLUSTER_FREE) {
			uint32_t tempNextCluster = _FAT_fat_linkFreeCluster (partition, CLUSTER_FREE);
			if (!_FAT_fat_isValidCluster(partition, tempNextCluster)) {
				// Couldn't get a cluster, so abort immediately
				_FAT_unlock(&partition->lock);
				r->_errno = ENOSPC;
				return -1;
			}
			file->startCluster = tempNextCluster;

			file->rwPosition.cluster = file->startCluster;
			file->rwPosition.sector =  0;
			file->rwPosition.byte = 0;
		}
		// Save the read/write pointer
		savedPosition = file->rwPosition;
		savedOffset = file->currentPosition;
		// Set the position to the new size
		file->currentPosition = newSize;
		// Extend the file to the new position
		if (!_FAT_file_extend_r (r, file)) {
			ret = -1;
		}
		// Set the append position to the new rwPointer
		if (file->append) {
			file->appendPosition = file->rwPosition;
		}
		// Restore the old rwPointer;
		file->rwPosition = savedPosition;
		file->currentPosition = savedOffset;
	} else if (newSize < file->filesize){
		// Shrinking the file
		if (len == 0) {
			// Cutting the file down to nothing, clear all clusters used
			_FAT_fat_clearLinks (partition, file->startCluster);
			file->startCluster = CLUSTER_FREE;

			file->appendPosition.cluster = CLUSTER_FREE;
			file->appendPosition.sector = 0;
			file->appendPosition.byte = 0;
		} else {
			// Trimming the file down to the required size
			unsigned int chainLength;
			uint32_t lastCluster;

			// Drop the unneeded end of the cluster chain.
			// If the end falls on a cluster boundary, drop that cluster too,
			// then set a flag to allocate a cluster as needed
			chainLength = ((newSize-1) / partition->bytesPerCluster) + 1;
			lastCluster = _FAT_fat_trimChain (partition, file->startCluster, chainLength);

			if (file->append) {
				file->appendPosition.byte = newSize % partition->bytesPerSector;
				// Does the end of the file fall on the edge of a cluster?
				if (newSize % partition->bytesPerCluster == 0) {
					// Set a flag to allocate a new cluster
					file->appendPosition.sector = partition->sectorsPerCluster;
				} else {
					file->appendPosition.sector = (newSize % partition->bytesPerCluster) / partition->bytesPerSector;
				}
				file->appendPosition.cluster = lastCluster;
			}
		}
	} else {
		// Truncating to same length, so don't do anything
	}

	file->filesize = newSize;
	file->modified = true;

	_FAT_unlock(&partition->lock);
	return ret;
}