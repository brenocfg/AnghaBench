#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct _reent {void* _errno; } ;
struct TYPE_18__ {int /*<<< orphan*/  entryData; } ;
struct TYPE_17__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cache; scalar_t__ readOnly; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ DIR_ENTRY ;

/* Variables and functions */
 void* EINVAL ; 
 void* EIO ; 
 void* ENODEV ; 
 void* ENOENT ; 
 void* ENOTEMPTY ; 
 void* EROFS ; 
 int /*<<< orphan*/  _FAT_cache_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_directory_entryFromPath (TYPE_1__*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_directory_entryGetCluster (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int _FAT_directory_getFirstEntry (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int _FAT_directory_getNextEntry (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ _FAT_directory_isDirectory (TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_directory_isDot (TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_directory_removeEntry (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_fat_clearLinks (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _FAT_fat_isValidCluster (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 TYPE_1__* _FAT_partition_getPartitionFromPath (char const*) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 

int _FAT_unlink_r (struct _reent *r, const char *path)
{
   PARTITION* partition = NULL;
   DIR_ENTRY dirEntry;
   DIR_ENTRY dirContents;
   uint32_t cluster;
   bool nextEntry;
   bool errorOccured = false;

   /* Get the partition this directory is on */
   partition = _FAT_partition_getPartitionFromPath (path);
   if (partition == NULL)
   {
      r->_errno = ENODEV;
      return -1;
   }

   /* Make sure we aren't trying to write to a read-only disc */
   if (partition->readOnly)
   {
      r->_errno = EROFS;
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

   /* Search for the file on the disc */
   if (!_FAT_directory_entryFromPath (partition, &dirEntry, path, NULL))
   {
      _FAT_unlock(&partition->lock);
      r->_errno = ENOENT;
      return -1;
   }

   cluster = _FAT_directory_entryGetCluster (partition, dirEntry.entryData);

   /* If this is a directory, make sure it is empty */
   if (_FAT_directory_isDirectory (&dirEntry))
   {
      nextEntry = _FAT_directory_getFirstEntry (partition, &dirContents, cluster);

      while (nextEntry)
      {
         if (!_FAT_directory_isDot (&dirContents))
         {
            /* The directory had something in it that isn't a reference to itself or it's parent */
            _FAT_unlock(&partition->lock);
            r->_errno = ENOTEMPTY;
            return -1;
         }
         nextEntry = _FAT_directory_getNextEntry (partition, &dirContents);
      }
   }

   if (_FAT_fat_isValidCluster(partition, cluster))
   {
      /* Remove the cluster chain for this file */
      if (!_FAT_fat_clearLinks (partition, cluster))
      {
         r->_errno = EIO;
         errorOccured = true;
      }
   }

   /* Remove the directory entry for this file */
   if (!_FAT_directory_removeEntry (partition, &dirEntry))
   {
      r->_errno = EIO;
      errorOccured = true;
   }

   /* Flush any sectors in the disc cache */
   if (!_FAT_cache_flush(partition->cache))
   {
      r->_errno = EIO;
      errorOccured = true;
   }

   _FAT_unlock(&partition->lock);
   if (errorOccured)
      return -1;
   return 0;
}