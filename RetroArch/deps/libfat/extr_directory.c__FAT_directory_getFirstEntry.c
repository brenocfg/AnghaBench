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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int offset; scalar_t__ sector; int /*<<< orphan*/  cluster; } ;
struct TYPE_6__ {TYPE_1__ dataStart; TYPE_1__ dataEnd; } ;
typedef  int /*<<< orphan*/  PARTITION ;
typedef  TYPE_2__ DIR_ENTRY ;

/* Variables and functions */
 int _FAT_directory_getNextEntry (int /*<<< orphan*/ *,TYPE_2__*) ; 

bool _FAT_directory_getFirstEntry (PARTITION* partition, DIR_ENTRY* entry, uint32_t dirCluster)
{
   entry->dataStart.cluster = dirCluster;
   entry->dataStart.sector  = 0;
   entry->dataStart.offset  = -1; /* Start before the beginning of the directory */

   entry->dataEnd = entry->dataStart;

   return _FAT_directory_getNextEntry (partition, entry);
}