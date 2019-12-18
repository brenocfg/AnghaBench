#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct _reent {void* _errno; } ;
struct TYPE_18__ {int /*<<< orphan*/  dataEnd; int /*<<< orphan*/  dataStart; scalar_t__* entryData; int /*<<< orphan*/  filename; } ;
struct TYPE_15__ {scalar_t__ cluster; int sector; int byte; } ;
struct TYPE_17__ {int read; int write; int append; int modified; int filesize; scalar_t__ startCluster; int inUse; struct TYPE_17__* prevOpenFile; struct TYPE_17__* nextOpenFile; TYPE_1__ rwPosition; TYPE_1__ appendPosition; scalar_t__ currentPosition; int /*<<< orphan*/  dirEntryEnd; int /*<<< orphan*/  dirEntryStart; TYPE_2__* partition; } ;
struct TYPE_16__ {int bytesPerCluster; int bytesPerSector; int sectorsPerCluster; int openFileCount; int /*<<< orphan*/  lock; TYPE_3__* firstOpenFile; void* cwdCluster; scalar_t__ readOnly; } ;
typedef  TYPE_2__ PARTITION ;
typedef  TYPE_3__ FILE_STRUCT ;
typedef  TYPE_4__ DIR_ENTRY ;

/* Variables and functions */
 scalar_t__ CLUSTER_FREE ; 
 int /*<<< orphan*/  DIR_ENTRY_DATA_SIZE ; 
 int /*<<< orphan*/  DIR_ENTRY_cDate ; 
 int /*<<< orphan*/  DIR_ENTRY_cTime ; 
 size_t DIR_ENTRY_cTime_ms ; 
 int /*<<< orphan*/  DIR_ENTRY_fileSize ; 
 int /*<<< orphan*/  DIR_SEPARATOR ; 
 void* EACCES ; 
 void* EEXIST ; 
 void* EINVAL ; 
 void* EISDIR ; 
 void* ENODEV ; 
 void* ENOENT ; 
 void* ENOSPC ; 
 void* ENOTDIR ; 
 void* EROFS ; 
 scalar_t__ NAME_MAX ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  _FAT_directory_addEntry (TYPE_2__*,TYPE_4__*,void*) ; 
 int _FAT_directory_entryFromPath (TYPE_2__*,TYPE_4__*,char const*,char const*) ; 
 void* _FAT_directory_entryGetCluster (TYPE_2__*,scalar_t__*) ; 
 scalar_t__ _FAT_directory_isDirectory (TYPE_4__*) ; 
 int /*<<< orphan*/  _FAT_directory_isWritable (TYPE_4__*) ; 
 int /*<<< orphan*/  _FAT_fat_clearLinks (TYPE_2__*,scalar_t__) ; 
 scalar_t__ _FAT_fat_lastCluster (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  _FAT_filetime_getDateFromRTC () ; 
 int /*<<< orphan*/  _FAT_filetime_getTimeFromRTC () ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 TYPE_2__* _FAT_partition_getPartitionFromPath (char const*) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 char* strrchr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16_to_u8array (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int u8array_to_u32 (scalar_t__*,int /*<<< orphan*/ ) ; 

int _FAT_open_r (struct _reent *r, void *fileStruct, const char *path, int flags, int mode) {
	PARTITION* partition = NULL;
	bool fileExists;
	DIR_ENTRY dirEntry;
	const char* pathEnd;
	uint32_t dirCluster;
	FILE_STRUCT* file = (FILE_STRUCT*) fileStruct;
	partition = _FAT_partition_getPartitionFromPath (path);

	if (partition == NULL) {
		r->_errno = ENODEV;
		return -1;
	}

	// Move the path pointer to the start of the actual path
	if (strchr (path, ':') != NULL) {
		path = strchr (path, ':') + 1;
	}
	if (strchr (path, ':') != NULL) {
		r->_errno = EINVAL;
		return -1;
	}

	// Determine which mode the file is openned for
	if ((flags & 0x03) == O_RDONLY) {
		// Open the file for read-only access
		file->read = true;
		file->write = false;
		file->append = false;
	} else if ((flags & 0x03) == O_WRONLY) {
		// Open file for write only access
		file->read = false;
		file->write = true;
		file->append = false;
	} else if ((flags & 0x03) == O_RDWR) {
		// Open file for read/write access
		file->read = true;
		file->write = true;
		file->append = false;
	} else {
		r->_errno = EACCES;
		return -1;
	}

	// Make sure we aren't trying to write to a read-only disc
	if (file->write && partition->readOnly) {
		r->_errno = EROFS;
		return -1;
	}

	// Search for the file on the disc
	_FAT_lock(&partition->lock);
	fileExists = _FAT_directory_entryFromPath (partition, &dirEntry, path, NULL);

	// The file shouldn't exist if we are trying to create it
	if ((flags & O_CREAT) && (flags & O_EXCL) && fileExists) {
		_FAT_unlock(&partition->lock);
		r->_errno = EEXIST;
		return -1;
	}

	// It should not be a directory if we're openning a file,
	if (fileExists && _FAT_directory_isDirectory(&dirEntry)) {
		_FAT_unlock(&partition->lock);
		r->_errno = EISDIR;
		return -1;
	}

	// We haven't modified the file yet
	file->modified = false;

	// If the file doesn't exist, create it if we're allowed to
	if (!fileExists) {
		if (flags & O_CREAT) {
			if (partition->readOnly) {
				// We can't write to a read-only partition
				_FAT_unlock(&partition->lock);
				r->_errno = EROFS;
				return -1;
			}
			// Create the file
			// Get the directory it has to go in
			pathEnd = strrchr (path, DIR_SEPARATOR);
			if (pathEnd == NULL) {
				// No path was specified
				dirCluster = partition->cwdCluster;
				pathEnd = path;
			} else {
				// Path was specified -- get the right dirCluster
				// Recycling dirEntry, since it needs to be recreated anyway
				if (!_FAT_directory_entryFromPath (partition, &dirEntry, path, pathEnd) ||
					!_FAT_directory_isDirectory(&dirEntry)) {
					_FAT_unlock(&partition->lock);
					r->_errno = ENOTDIR;
					return -1;
				}
				dirCluster = _FAT_directory_entryGetCluster (partition, dirEntry.entryData);
				// Move the pathEnd past the last DIR_SEPARATOR
				pathEnd += 1;
			}
			// Create the entry data
			strncpy (dirEntry.filename, pathEnd, NAME_MAX - 1);
			memset (dirEntry.entryData, 0, DIR_ENTRY_DATA_SIZE);

			// Set the creation time and date
			dirEntry.entryData[DIR_ENTRY_cTime_ms] = 0;
			u16_to_u8array (dirEntry.entryData, DIR_ENTRY_cTime, _FAT_filetime_getTimeFromRTC());
			u16_to_u8array (dirEntry.entryData, DIR_ENTRY_cDate, _FAT_filetime_getDateFromRTC());

			if (!_FAT_directory_addEntry (partition, &dirEntry, dirCluster)) {
				_FAT_unlock(&partition->lock);
				r->_errno = ENOSPC;
				return -1;
			}

			// File entry is modified
			file->modified = true;
		} else {
			// file doesn't exist, and we aren't creating it
			_FAT_unlock(&partition->lock);
			r->_errno = ENOENT;
			return -1;
		}
	}

	file->filesize = u8array_to_u32 (dirEntry.entryData, DIR_ENTRY_fileSize);

	/* Allow LARGEFILEs with undefined results
	// Make sure that the file size can fit in the available space
	if (!(flags & O_LARGEFILE) && (file->filesize >= (1<<31))) {
		r->_errno = EFBIG;
		return -1;
	}
	*/

	// Make sure we aren't trying to write to a read-only file
	if (file->write && !_FAT_directory_isWritable(&dirEntry)) {
		_FAT_unlock(&partition->lock);
		r->_errno = EROFS;
		return -1;
	}

	// Associate this file with a particular partition
	file->partition = partition;

	file->startCluster = _FAT_directory_entryGetCluster (partition, dirEntry.entryData);

	// Truncate the file if requested
	if ((flags & O_TRUNC) && file->write && (file->startCluster != 0)) {
		_FAT_fat_clearLinks (partition, file->startCluster);
		file->startCluster = CLUSTER_FREE;
		file->filesize = 0;
		// File is modified since we just cut it all off
		file->modified = true;
	}

	// Remember the position of this file's directory entry
	file->dirEntryStart = dirEntry.dataStart;		// Points to the start of the LFN entries of a file, or the alias for no LFN
	file->dirEntryEnd = dirEntry.dataEnd;

	// Reset read/write pointer
	file->currentPosition = 0;
	file->rwPosition.cluster = file->startCluster;
	file->rwPosition.sector =  0;
	file->rwPosition.byte = 0;

	if (flags & O_APPEND) {
		file->append = true;

		// Set append pointer to the end of the file
		file->appendPosition.cluster = _FAT_fat_lastCluster (partition, file->startCluster);
		file->appendPosition.sector = (file->filesize % partition->bytesPerCluster) / partition->bytesPerSector;
		file->appendPosition.byte = file->filesize % partition->bytesPerSector;

		// Check if the end of the file is on the end of a cluster
		if ( (file->filesize > 0) && ((file->filesize % partition->bytesPerCluster)==0) ){
			// Set flag to allocate a new cluster
			file->appendPosition.sector = partition->sectorsPerCluster;
			file->appendPosition.byte = 0;
		}
	} else {
		file->append = false;
		// Use something sane for the append pointer, so the whole file struct contains known values
		file->appendPosition = file->rwPosition;
	}

	file->inUse = true;

	// Insert this file into the double-linked list of open files
	partition->openFileCount += 1;
	if (partition->firstOpenFile) {
		file->nextOpenFile = partition->firstOpenFile;
		partition->firstOpenFile->prevOpenFile = file;
	} else {
		file->nextOpenFile = NULL;
	}
	file->prevOpenFile = NULL;
	partition->firstOpenFile = file;

	_FAT_unlock(&partition->lock);

	return (int) file;
}