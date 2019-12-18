#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ lastCluster; } ;
struct TYPE_6__ {TYPE_1__ fat; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 scalar_t__ CLUSTER_FIRST ; 
 scalar_t__ CLUSTER_FREE ; 
 scalar_t__ _FAT_fat_nextCluster (TYPE_2__*,scalar_t__) ; 

unsigned int _FAT_fat_freeClusterCount (PARTITION* partition)
{
	unsigned int count = 0;
	uint32_t curCluster;

	for (curCluster = CLUSTER_FIRST; curCluster <= partition->fat.lastCluster; curCluster++)
   {
		if (_FAT_fat_nextCluster(partition, curCluster) == CLUSTER_FREE)
			count++;
	}

	return count;
}