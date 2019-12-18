#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* entryData; } ;
struct TYPE_7__ {int /*<<< orphan*/  cwdCluster; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ DIR_ENTRY ;

/* Variables and functions */
 int ATTRIB_DIR ; 
 size_t DIR_ENTRY_attributes ; 
 int /*<<< orphan*/  _FAT_directory_entryFromPath (TYPE_1__*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_directory_entryGetCluster (TYPE_1__*,int*) ; 

bool _FAT_directory_chdir (PARTITION* partition, const char* path)
{
   DIR_ENTRY entry;

   if (!_FAT_directory_entryFromPath (partition, &entry, path, NULL))
      return false;

   if (!(entry.entryData[DIR_ENTRY_attributes] & ATTRIB_DIR))
      return false;

   partition->cwdCluster = _FAT_directory_entryGetCluster (partition, entry.entryData);

   return true;
}