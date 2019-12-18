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
struct statvfs {unsigned int f_bfree; unsigned int f_bavail; unsigned int f_ffree; unsigned int f_favail; int f_flag; int /*<<< orphan*/  f_namemax; int /*<<< orphan*/  f_fsid; void* f_files; void* f_blocks; int /*<<< orphan*/  f_frsize; int /*<<< orphan*/  f_bsize; } ;
struct _reent {int /*<<< orphan*/  _errno; } ;
struct TYPE_6__ {unsigned int numberFreeCluster; void* lastCluster; } ;
struct TYPE_7__ {scalar_t__ filesysType; int /*<<< orphan*/  lock; scalar_t__ readOnly; int /*<<< orphan*/  disc; TYPE_1__ fat; int /*<<< orphan*/  bytesPerCluster; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 void* CLUSTER_FIRST ; 
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ FS_FAT32 ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int ST_NOSUID ; 
 int ST_RDONLY ; 
 int /*<<< orphan*/  _FAT_disc_hostType (int /*<<< orphan*/ ) ; 
 unsigned int _FAT_fat_freeClusterCount (TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 TYPE_2__* _FAT_partition_getPartitionFromPath (char const*) ; 
 int /*<<< orphan*/  _FAT_partition_readFSinfo (TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 

int _FAT_statvfs_r (struct _reent *r, const char *path, struct statvfs *buf)
{
	PARTITION* partition = NULL;
	unsigned int freeClusterCount;

	// Get the partition of the requested path
	partition = _FAT_partition_getPartitionFromPath (path);
	if (partition == NULL) {
		r->_errno = ENODEV;
		return -1;
	}

	_FAT_lock(&partition->lock);

	if(partition->filesysType == FS_FAT32) {
		// Sync FSinfo block
		_FAT_partition_readFSinfo(partition);
		freeClusterCount = partition->fat.numberFreeCluster;
	} else {
		freeClusterCount = _FAT_fat_freeClusterCount (partition);
	}

	// FAT clusters = POSIX blocks
	buf->f_bsize = partition->bytesPerCluster;		// File system block size.
	buf->f_frsize = partition->bytesPerCluster;	// Fundamental file system block size.

	buf->f_blocks	= partition->fat.lastCluster - CLUSTER_FIRST + 1; // Total number of blocks on file system in units of f_frsize.
	buf->f_bfree = freeClusterCount;	// Total number of free blocks.
	buf->f_bavail	= freeClusterCount;	// Number of free blocks available to non-privileged process.

	// Treat requests for info on inodes as clusters
	buf->f_files = partition->fat.lastCluster - CLUSTER_FIRST + 1;	// Total number of file serial numbers.
	buf->f_ffree = freeClusterCount;	// Total number of free file serial numbers.
	buf->f_favail = freeClusterCount;	// Number of file serial numbers available to non-privileged process.

	// File system ID. 32bit ioType value
	buf->f_fsid = _FAT_disc_hostType(partition->disc);

	// Bit mask of f_flag values.
	buf->f_flag = ST_NOSUID /* No support for ST_ISUID and ST_ISGID file mode bits */
		| (partition->readOnly ? ST_RDONLY /* Read only file system */ : 0 ) ;
	// Maximum filename length.
	buf->f_namemax = NAME_MAX;

	_FAT_unlock(&partition->lock);
	return 0;
}