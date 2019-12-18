#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint32_t ;
struct _reent {void* _errno; } ;
struct TYPE_14__ {char* entryData; int /*<<< orphan*/  filename; } ;
struct TYPE_13__ {int cwdCluster; int rootDirCluster; int /*<<< orphan*/  lock; int /*<<< orphan*/  cache; scalar_t__ readOnly; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ DIR_ENTRY ;

/* Variables and functions */
 void* ATTRIB_DIR ; 
 int /*<<< orphan*/  CLUSTER_FREE ; 
 int DIR_ENTRY_DATA_SIZE ; 
 int /*<<< orphan*/  DIR_ENTRY_aDate ; 
 size_t DIR_ENTRY_attributes ; 
 int /*<<< orphan*/  DIR_ENTRY_cDate ; 
 int /*<<< orphan*/  DIR_ENTRY_cTime ; 
 size_t DIR_ENTRY_cTime_ms ; 
 int /*<<< orphan*/  DIR_ENTRY_cluster ; 
 int /*<<< orphan*/  DIR_ENTRY_clusterHigh ; 
 int /*<<< orphan*/  DIR_ENTRY_mDate ; 
 int /*<<< orphan*/  DIR_ENTRY_mTime ; 
 size_t DIR_ENTRY_name ; 
 int /*<<< orphan*/  DIR_SEPARATOR ; 
 void* EEXIST ; 
 void* EINVAL ; 
 void* EIO ; 
 void* ENODEV ; 
 void* ENOSPC ; 
 void* ENOTDIR ; 
 void* EROFS ; 
 int FAT16_ROOT_DIR_CLUSTER ; 
 scalar_t__ NAME_MAX ; 
 int /*<<< orphan*/  _FAT_cache_eraseWritePartialSector (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _FAT_cache_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_cache_writePartialSector (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _FAT_directory_addEntry (TYPE_1__*,TYPE_2__*,int) ; 
 int _FAT_directory_entryFromPath (TYPE_1__*,TYPE_2__*,char const*,char const*) ; 
 int _FAT_directory_entryGetCluster (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  _FAT_directory_isDirectory (TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_fat_clusterToSector (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _FAT_fat_isValidCluster (TYPE_1__*,int) ; 
 int _FAT_fat_linkFreeClusterCleared (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int _FAT_filetime_getDateFromRTC () ; 
 int _FAT_filetime_getTimeFromRTC () ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 TYPE_1__* _FAT_partition_getPartitionFromPath (char const*) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 char* strrchr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16_to_u8array (char*,int /*<<< orphan*/ ,int) ; 

int _FAT_mkdir_r (struct _reent *r, const char *path, int mode)
{
	PARTITION* partition = NULL;
	bool fileExists;
	DIR_ENTRY dirEntry;
	const char* pathEnd;
	uint32_t parentCluster, dirCluster;
	uint8_t newEntryData[DIR_ENTRY_DATA_SIZE];

	partition = _FAT_partition_getPartitionFromPath (path);
	if (partition == NULL)
   {
		r->_errno = ENODEV;
		return -1;
	}

	/* Move the path pointer to the start of the actual path */
	if (strchr (path, ':') != NULL)
		path = strchr (path, ':') + 1;
	if (strchr (path, ':') != NULL)
   {
		r->_errno = EINVAL;
		return -1;
	}

	_FAT_lock(&partition->lock);

	/* Search for the file/directory on the disc */
	fileExists = _FAT_directory_entryFromPath (partition, &dirEntry, path, NULL);

	/* Make sure it doesn't exist */
	if (fileExists)
   {
		_FAT_unlock(&partition->lock);
		r->_errno = EEXIST;
		return -1;
	}

	if (partition->readOnly)
   {
		/* We can't write to a read-only partition */
		_FAT_unlock(&partition->lock);
		r->_errno = EROFS;
		return -1;
	}

	/* Get the directory it has to go in */
	pathEnd = strrchr (path, DIR_SEPARATOR);
	if (pathEnd == NULL)
   {
		/* No path was specified */
		parentCluster = partition->cwdCluster;
		pathEnd = path;
	}
   else
   {
		/* Path was specified -- get the right parentCluster
		 * Recycling dirEntry, since it needs to be recreated anyway */
		if (!_FAT_directory_entryFromPath (partition, &dirEntry, path, pathEnd) ||
			!_FAT_directory_isDirectory(&dirEntry))
      {
			_FAT_unlock(&partition->lock);
			r->_errno = ENOTDIR;
			return -1;
		}
		parentCluster = _FAT_directory_entryGetCluster (partition, dirEntry.entryData);
		/* Move the pathEnd past the last DIR_SEPARATOR */
		pathEnd += 1;
	}
	/* Create the entry data */
	strncpy (dirEntry.filename, pathEnd, NAME_MAX - 1);
	memset (dirEntry.entryData, 0, DIR_ENTRY_DATA_SIZE);

	/* Set the creation time and date */
	dirEntry.entryData[DIR_ENTRY_cTime_ms] = 0;
	u16_to_u8array (dirEntry.entryData, DIR_ENTRY_cTime, _FAT_filetime_getTimeFromRTC());
	u16_to_u8array (dirEntry.entryData, DIR_ENTRY_cDate, _FAT_filetime_getDateFromRTC());
	u16_to_u8array (dirEntry.entryData, DIR_ENTRY_mTime, _FAT_filetime_getTimeFromRTC());
	u16_to_u8array (dirEntry.entryData, DIR_ENTRY_mDate, _FAT_filetime_getDateFromRTC());
	u16_to_u8array (dirEntry.entryData, DIR_ENTRY_aDate, _FAT_filetime_getDateFromRTC());

	/* Set the directory attribute */
	dirEntry.entryData[DIR_ENTRY_attributes] = ATTRIB_DIR;

	/* Get a cluster for the new directory */
	dirCluster = _FAT_fat_linkFreeClusterCleared (partition, CLUSTER_FREE);
	if (!_FAT_fat_isValidCluster(partition, dirCluster))
   {
		/* No space left on disc for the cluster */
		_FAT_unlock(&partition->lock);
		r->_errno = ENOSPC;
		return -1;
	}
	u16_to_u8array (dirEntry.entryData, DIR_ENTRY_cluster, dirCluster);
	u16_to_u8array (dirEntry.entryData, DIR_ENTRY_clusterHigh, dirCluster >> 16);

	/* Write the new directory's entry to it's parent */
	if (!_FAT_directory_addEntry (partition, &dirEntry, parentCluster))
   {
		_FAT_unlock(&partition->lock);
		r->_errno = ENOSPC;
		return -1;
	}

	/* Create the dot entry within the directory */
	memset (newEntryData, 0, DIR_ENTRY_DATA_SIZE);
	memset (newEntryData, ' ', 11);
	newEntryData[DIR_ENTRY_name] = '.';
	newEntryData[DIR_ENTRY_attributes] = ATTRIB_DIR;
	u16_to_u8array (newEntryData, DIR_ENTRY_cluster, dirCluster);
	u16_to_u8array (newEntryData, DIR_ENTRY_clusterHigh, dirCluster >> 16);

	/* Write it to the directory, erasing that sector in the process */
	_FAT_cache_eraseWritePartialSector ( partition->cache, newEntryData,
		_FAT_fat_clusterToSector (partition, dirCluster), 0, DIR_ENTRY_DATA_SIZE);


	/* Create the double dot entry within the directory */

	/* if ParentDir == Rootdir then ".."" always link to Cluster 0 */
	if(parentCluster == partition->rootDirCluster)
		parentCluster = FAT16_ROOT_DIR_CLUSTER;

	newEntryData[DIR_ENTRY_name + 1] = '.';
	u16_to_u8array (newEntryData, DIR_ENTRY_cluster, parentCluster);
	u16_to_u8array (newEntryData, DIR_ENTRY_clusterHigh, parentCluster >> 16);

	/* Write it to the directory */
	_FAT_cache_writePartialSector ( partition->cache, newEntryData,
		_FAT_fat_clusterToSector (partition, dirCluster), DIR_ENTRY_DATA_SIZE, DIR_ENTRY_DATA_SIZE);

	/* Flush any sectors in the disc cache */
	if (!_FAT_cache_flush(partition->cache))
   {
		_FAT_unlock(&partition->lock);
		r->_errno = EIO;
		return -1;
	}

	_FAT_unlock(&partition->lock);
	return 0;
}