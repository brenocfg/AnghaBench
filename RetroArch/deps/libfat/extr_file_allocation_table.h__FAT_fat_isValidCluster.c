#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ lastCluster; } ;
struct TYPE_5__ {TYPE_1__ fat; } ;
typedef  TYPE_2__ PARTITION ;

/* Variables and functions */
 scalar_t__ CLUSTER_FIRST ; 

__attribute__((used)) static inline bool _FAT_fat_isValidCluster (PARTITION* partition, uint32_t cluster) {
	return (cluster >= CLUSTER_FIRST) && (cluster <= partition->fat.lastCluster /* This will catch CLUSTER_ERROR */);
}