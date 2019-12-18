#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_11__ {scalar_t__ cluster; int offset; scalar_t__ sector; } ;
struct TYPE_12__ {TYPE_2__ dataEnd; } ;
struct TYPE_10__ {scalar_t__ rootDirCluster; int /*<<< orphan*/  cache; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ DIR_ENTRY_POSITION ;
typedef  TYPE_3__ DIR_ENTRY ;

/* Variables and functions */
 char ATTRIB_VOL ; 
 int DIR_ENTRY_DATA_SIZE ; 
 char DIR_ENTRY_FREE ; 
 char DIR_ENTRY_LAST ; 
 size_t DIR_ENTRY_attributes ; 
 int DIR_ENTRY_name ; 
 scalar_t__ FAT16_ROOT_DIR_CLUSTER ; 
 int /*<<< orphan*/  _FAT_cache_readPartialSector (int /*<<< orphan*/ ,char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  _FAT_directory_getRootEntry (TYPE_1__*,TYPE_3__*) ; 
 int _FAT_directory_incrementDirEntryPosition (TYPE_1__*,TYPE_2__*,int) ; 
 scalar_t__ _FAT_fat_clusterToSector (TYPE_1__*,scalar_t__) ; 

bool _FAT_directory_getVolumeLabel (PARTITION* partition, char *label)
{
   DIR_ENTRY entry;
   DIR_ENTRY_POSITION entryEnd;
   uint8_t entryData[DIR_ENTRY_DATA_SIZE];
   int i;
   bool end;

   _FAT_directory_getRootEntry(partition, &entry);

   entryEnd = entry.dataEnd;

   /* Make sure we are using the correct root directory, in case of FAT32 */
   if (entryEnd.cluster == FAT16_ROOT_DIR_CLUSTER)
      entryEnd.cluster = partition->rootDirCluster;

   label[0]='\0';
   label[11]='\0';
   end = false;

   /* this entry should be among the first 3 entries in the root directory table, 
    * if not, then system can have trouble displaying the right volume label */

   while(!end)
   {
      /* error reading */
      if(!_FAT_cache_readPartialSector (partition->cache, entryData,
               _FAT_fat_clusterToSector(partition, entryEnd.cluster) + entryEnd.sector,
               entryEnd.offset * DIR_ENTRY_DATA_SIZE, DIR_ENTRY_DATA_SIZE))
         return false;

      if (entryData[DIR_ENTRY_attributes] == ATTRIB_VOL && entryData[0] != DIR_ENTRY_FREE)
      {
         for (i = 0; i < 11; i++)
            label[i] = entryData[DIR_ENTRY_name + i];
         return true;
      }
      else if (entryData[0] == DIR_ENTRY_LAST)
         end = true;

      if (_FAT_directory_incrementDirEntryPosition (partition, &entryEnd, false) == false)
         end = true;
   }
   return false;
}