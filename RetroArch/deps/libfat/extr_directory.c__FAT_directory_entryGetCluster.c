#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ filesysType; } ;
typedef  TYPE_1__ PARTITION ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_ENTRY_cluster ; 
 int /*<<< orphan*/  DIR_ENTRY_clusterHigh ; 
 scalar_t__ FS_FAT32 ; 
 int u8array_to_u16 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

uint32_t _FAT_directory_entryGetCluster (PARTITION* partition, const uint8_t* entryData)
{
   /* Only use high 16 bits of start cluster when we are certain they are correctly defined */
   if (partition->filesysType == FS_FAT32)
      return u8array_to_u16(entryData,DIR_ENTRY_cluster) | (u8array_to_u16(entryData, DIR_ENTRY_clusterHigh) << 16);
   return u8array_to_u16(entryData,DIR_ENTRY_cluster);
}