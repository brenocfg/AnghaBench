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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ sec_t ;
struct TYPE_3__ {scalar_t__ dataStart; scalar_t__ rootDirStart; scalar_t__ sectorsPerCluster; } ;
typedef  TYPE_1__ PARTITION ;

/* Variables and functions */
 scalar_t__ CLUSTER_FIRST ; 

__attribute__((used)) static inline sec_t _FAT_fat_clusterToSector (PARTITION* partition, uint32_t cluster) {
	return (cluster >= CLUSTER_FIRST) ? 
		((cluster - CLUSTER_FIRST) * (sec_t)partition->sectorsPerCluster) + partition->dataStart : 
		partition->rootDirStart;
}