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
struct TYPE_3__ {scalar_t__ deviceData; } ;
typedef  TYPE_1__ devoptab_t ;
typedef  int /*<<< orphan*/  PARTITION ;

/* Variables and functions */
 TYPE_1__* GetDeviceOpTab (char const*) ; 

PARTITION* _FAT_partition_getPartitionFromPath (const char* path)
{
   const devoptab_t *devops = GetDeviceOpTab (path);

   if (!devops)
      return NULL;

   return (PARTITION*)devops->deviceData;
}