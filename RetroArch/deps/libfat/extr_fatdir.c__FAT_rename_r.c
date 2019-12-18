#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct _reent {void* _errno; } ;
struct TYPE_15__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  entryData; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cache; int /*<<< orphan*/  cwdCluster; scalar_t__ readOnly; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ DIR_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_SEPARATOR ; 
 void* EEXIST ; 
 void* EINVAL ; 
 void* EIO ; 
 void* ENODEV ; 
 void* ENOENT ; 
 void* ENOSPC ; 
 void* ENOTDIR ; 
 void* EROFS ; 
 void* EXDEV ; 
 scalar_t__ NAME_MAX ; 
 int /*<<< orphan*/  _FAT_cache_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_directory_addEntry (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _FAT_directory_entryFromPath (TYPE_1__*,TYPE_2__*,char const*,char const*) ; 
 int /*<<< orphan*/  _FAT_directory_entryGetCluster (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_directory_isDirectory (TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_directory_removeEntry (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 TYPE_1__* _FAT_partition_getPartitionFromPath (char const*) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 char* strrchr (char const*,int /*<<< orphan*/ ) ; 

int _FAT_rename_r (struct _reent *r, const char *oldName, const char *newName)
{
	DIR_ENTRY oldDirEntry;
	DIR_ENTRY newDirEntry;
	const char *pathEnd;
	uint32_t dirCluster;

	/* Get the partition this directory is on */
	PARTITION *partition = _FAT_partition_getPartitionFromPath (oldName);
	if (partition == NULL)
   {
		r->_errno = ENODEV;
		return -1;
	}

	_FAT_lock(&partition->lock);

	/* Make sure the same partition is used for the old and new names */
	if (partition != _FAT_partition_getPartitionFromPath (newName))
   {
		_FAT_unlock(&partition->lock);
		r->_errno = EXDEV;
		return -1;
	}

	/* Make sure we aren't trying to write to a read-only disc */
	if (partition->readOnly)
   {
		_FAT_unlock(&partition->lock);
		r->_errno = EROFS;
		return -1;
	}

	/* Move the path pointer to the start of the actual path */
	if (strchr (oldName, ':') != NULL)
		oldName = strchr (oldName, ':') + 1;
	if (strchr (oldName, ':') != NULL)
   {
		_FAT_unlock(&partition->lock);
		r->_errno = EINVAL;
		return -1;
	}
	if (strchr (newName, ':') != NULL)
		newName = strchr (newName, ':') + 1;
	if (strchr (newName, ':') != NULL)
   {
		_FAT_unlock(&partition->lock);
		r->_errno = EINVAL;
		return -1;
	}

	/* Search for the file on the disc */
	if (!_FAT_directory_entryFromPath (partition, &oldDirEntry, oldName, NULL))
   {
		_FAT_unlock(&partition->lock);
		r->_errno = ENOENT;
		return -1;
	}

	/* Make sure there is no existing file / directory with the new name */
	if (_FAT_directory_entryFromPath (partition, &newDirEntry, newName, NULL))
   {
		_FAT_unlock(&partition->lock);
		r->_errno = EEXIST;
		return -1;
	}

	/* Create the new file entry
	 * Get the directory it has to go in */
	pathEnd = strrchr (newName, DIR_SEPARATOR);
	if (pathEnd == NULL)
   {
		/* No path was specified */
		dirCluster = partition->cwdCluster;
		pathEnd = newName;
	}
   else
   {
		/* Path was specified -- get the right dirCluster
		 * Recycling newDirEntry, since it needs to be recreated anyway */
		if (!_FAT_directory_entryFromPath (partition, &newDirEntry, newName, pathEnd) ||
			!_FAT_directory_isDirectory(&newDirEntry))
      {
			_FAT_unlock(&partition->lock);
			r->_errno = ENOTDIR;
			return -1;
		}
		dirCluster = _FAT_directory_entryGetCluster (partition, newDirEntry.entryData);
		/* Move the pathEnd past the last DIR_SEPARATOR */
		pathEnd += 1;
	}

	/* Copy the entry data */
	memcpy (&newDirEntry, &oldDirEntry, sizeof(DIR_ENTRY));

	/* Set the new name */
	strncpy (newDirEntry.filename, pathEnd, NAME_MAX - 1);

	/* Write the new entry */
	if (!_FAT_directory_addEntry (partition, &newDirEntry, dirCluster))
   {
		_FAT_unlock(&partition->lock);
		r->_errno = ENOSPC;
		return -1;
	}

	/* Remove the old entry */
	if (!_FAT_directory_removeEntry (partition, &oldDirEntry))
   {
		_FAT_unlock(&partition->lock);
		r->_errno = EIO;
		return -1;
	}

	/* Flush any sectors in the disc cache */
	if (!_FAT_cache_flush (partition->cache))
   {
		_FAT_unlock(&partition->lock);
		r->_errno = EIO;
		return -1;
	}

	_FAT_unlock(&partition->lock);
	return 0;
}