#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct _reent {void* _errno; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  newPosition ;
struct TYPE_5__ {scalar_t__ cluster; scalar_t__ byte; scalar_t__ sector; } ;
struct TYPE_7__ {int inUse; scalar_t__ currentPosition; scalar_t__ filesize; scalar_t__ startCluster; TYPE_1__ rwPosition; TYPE_2__* partition; } ;
struct TYPE_6__ {scalar_t__ bytesPerCluster; scalar_t__ bytesPerSector; int /*<<< orphan*/  lock; scalar_t__ sectorsPerCluster; } ;
typedef  TYPE_2__ PARTITION ;
typedef  TYPE_3__ FILE_STRUCT ;

/* Variables and functions */
 scalar_t__ CLUSTER_EOF ; 
 scalar_t__ CLUSTER_FREE ; 
 void* EBADF ; 
 void* EINVAL ; 
 void* EOVERFLOW ; 
 scalar_t__ FILE_MAX_SIZE ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 scalar_t__ _FAT_fat_nextCluster (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 

off_t _FAT_seek_r (struct _reent *r, void *fd, off_t pos, int dir) {
	FILE_STRUCT* file = (FILE_STRUCT*)  fd;
	PARTITION* partition;
	uint32_t cluster, nextCluster;
	int clusCount;
	off_t newPosition;
	uint32_t position;

	if ((file == NULL) || (file->inUse == false))	 {
		// invalid file
		r->_errno = EBADF;
		return -1;
	}

	partition = file->partition;
	_FAT_lock(&partition->lock);

	switch (dir) {
		case SEEK_SET:
			newPosition = pos;
			break;
		case SEEK_CUR:
			newPosition = (off_t)file->currentPosition + pos;
			break;
		case SEEK_END:
			newPosition = (off_t)file->filesize + pos;
			break;
		default:
			_FAT_unlock(&partition->lock);
			r->_errno = EINVAL;
			return -1;
	}

	if ((pos > 0) && (newPosition < 0)) {
		_FAT_unlock(&partition->lock);
		r->_errno = EOVERFLOW;
		return -1;
	}

	// newPosition can only be larger than the FILE_MAX_SIZE on platforms where
	// off_t is larger than 32 bits.
	if (newPosition < 0 || ((sizeof(newPosition) > 4) && newPosition > (off_t)FILE_MAX_SIZE)) {
		_FAT_unlock(&partition->lock);
		r->_errno = EINVAL;
		return -1;
	}

	position = (uint32_t)newPosition;

	// Only change the read/write position if it is within the bounds of the current filesize,
	// or at the very edge of the file
	if (position <= file->filesize && file->startCluster != CLUSTER_FREE) {
		// Calculate where the correct cluster is
		// how many clusters from start of file
		clusCount = position / partition->bytesPerCluster;
		cluster = file->startCluster;
		if (position >= file->currentPosition) {
			// start from current cluster
			int currentCount = file->currentPosition / partition->bytesPerCluster;
			if (file->rwPosition.sector == partition->sectorsPerCluster) {
				currentCount--;
			}
			clusCount -= currentCount;
			cluster = file->rwPosition.cluster;
		}
		// Calculate the sector and byte of the current position,
		// and store them
		file->rwPosition.sector = (position % partition->bytesPerCluster) / partition->bytesPerSector;
		file->rwPosition.byte = position % partition->bytesPerSector;

		nextCluster = _FAT_fat_nextCluster (partition, cluster);
		while ((clusCount > 0) && (nextCluster != CLUSTER_FREE) && (nextCluster != CLUSTER_EOF)) {
			clusCount--;
			cluster = nextCluster;
			nextCluster = _FAT_fat_nextCluster (partition, cluster);
		}

		// Check if ran out of clusters and it needs to allocate a new one
		if (clusCount > 0) {
			if ((clusCount == 1) && (file->filesize == position) && (file->rwPosition.sector == 0)) {
				// Set flag to allocate a new cluster
				file->rwPosition.sector = partition->sectorsPerCluster;
				file->rwPosition.byte = 0;
			} else {
				_FAT_unlock(&partition->lock);
				r->_errno = EINVAL;
				return -1;
			}
		}

		file->rwPosition.cluster = cluster;
	}

	// Save position
	file->currentPosition = position;

	_FAT_unlock(&partition->lock);
	return position;
}