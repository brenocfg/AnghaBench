#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_13__ {char* filename; int* entryData; } ;
struct TYPE_12__ {scalar_t__ rootDirCluster; scalar_t__ cwdCluster; scalar_t__ filesysType; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ DIR_ENTRY ;

/* Variables and functions */
 int ATTRIB_DIR ; 
 scalar_t__ CLUSTER_ROOT ; 
 size_t DIR_ENTRY_attributes ; 
 char const DIR_SEPARATOR ; 
 scalar_t__ FS_FAT32 ; 
 int MAX_ALIAS_LENGTH ; 
 size_t NAME_MAX ; 
 int /*<<< orphan*/  _FAT_directory_entryGetAlias (int*,char*) ; 
 scalar_t__ _FAT_directory_entryGetCluster (TYPE_1__*,int*) ; 
 int _FAT_directory_getFirstEntry (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int _FAT_directory_getNextEntry (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_directory_getRootEntry (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ _FAT_directory_mbsncasecmp (char const*,char*,size_t) ; 
 char* strchr (char const*,char const) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,size_t) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 size_t strnlen (char*,int) ; 

bool _FAT_directory_entryFromPath (PARTITION* partition, DIR_ENTRY* entry, const char* path, const char* pathEnd)
{
   size_t dirnameLength;
   const char* nextPathPosition;
   uint32_t dirCluster;
   bool foundFile;
   char alias[MAX_ALIAS_LENGTH];
   const char *pathPosition = path;
   bool found = false;
   bool notFound = false;

   /* Set pathEnd to the end of the path string */
   if (pathEnd == NULL)
      pathEnd = strchr (path, '\0');

   if (pathPosition[0] == DIR_SEPARATOR)
   {
      /* Start at root directory */
      dirCluster = partition->rootDirCluster;
      /* Consume separator(s) */
      while (pathPosition[0] == DIR_SEPARATOR)
         pathPosition++;
      /* If the path is only specifying a directory in the form of "/" return it */
      if (pathPosition >= pathEnd)
      {
         _FAT_directory_getRootEntry (partition, entry);
         found = true;
      }
   }
   /* Start in current working directory */
   else
      dirCluster = partition->cwdCluster;

   while (!found && !notFound)
   {
      /* Get the name of the next required subdirectory within the path */
      nextPathPosition = strchr (pathPosition, DIR_SEPARATOR);
      if (nextPathPosition != NULL)
         dirnameLength = nextPathPosition - pathPosition;
      else
         dirnameLength = strlen(pathPosition);

      /* The path is too long to bother with */
      if (dirnameLength > NAME_MAX)
         return false;

      /* Check for "." or ".." when the dirCluster is root cluster
       * These entries do not exist, so we must fake it */
      if ((dirCluster == partition->rootDirCluster)
            &&  ((strncmp(".", pathPosition, dirnameLength) == 0)
               || (strncmp("..", pathPosition, dirnameLength) == 0)))
      {
         foundFile = true;
         _FAT_directory_getRootEntry(partition, entry);
      }
      else
      {
         /* Look for the directory within the path */
         foundFile = _FAT_directory_getFirstEntry (partition, entry, dirCluster);

         while (foundFile && !found && !notFound)
         {
            /* It hasn't already found the file
             * Check if the filename matches */
            if ((dirnameLength == strnlen(entry->filename, NAME_MAX))
                  && (_FAT_directory_mbsncasecmp(pathPosition, entry->filename, dirnameLength) == 0))
               found = true;

            /* Check if the alias matches */
            _FAT_directory_entryGetAlias (entry->entryData, alias);
            if ((dirnameLength == strnlen(alias, MAX_ALIAS_LENGTH))
                  && (strncasecmp(pathPosition, alias, dirnameLength) == 0))
               found = true;

            /* Make sure that we aren't trying to follow a file instead of a directory in the path */
            if (found && !(entry->entryData[DIR_ENTRY_attributes] & ATTRIB_DIR) && (nextPathPosition != NULL))
               found = false;

            if (!found)
               foundFile = _FAT_directory_getNextEntry (partition, entry);
         }
      }

      if (!foundFile)
      {
         /* Check that the search didn't get to the end of the directory */
         notFound = true;
         found = false;
      }
      /* Check that we reached the end of the path */
      else if ((nextPathPosition == NULL) || (nextPathPosition >= pathEnd))
         found = true;
      else if (entry->entryData[DIR_ENTRY_attributes] & ATTRIB_DIR)
      {
         dirCluster = _FAT_directory_entryGetCluster (partition, entry->entryData);
         if (dirCluster == CLUSTER_ROOT)
            dirCluster = partition->rootDirCluster;
         pathPosition = nextPathPosition;
         /* Consume separator(s) */
         while (pathPosition[0] == DIR_SEPARATOR)
            pathPosition++;
         /* The requested directory was found */
         if (pathPosition >= pathEnd) 
            found = true;
         else
            found = false;
      }
   }

   if (found && !notFound)
   {
      /* On FAT32 it should specify an actual cluster for the root entry,
       * not cluster 0 as on FAT16 */
      if (partition->filesysType == FS_FAT32 && (entry->entryData[DIR_ENTRY_attributes] & ATTRIB_DIR) &&
            _FAT_directory_entryGetCluster (partition, entry->entryData) == CLUSTER_ROOT)
         _FAT_directory_getRootEntry (partition, entry);
      return true;
   }

   return false;
}