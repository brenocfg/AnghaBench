#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  esp_partition_t ;
typedef  int BYTE ;

/* Variables and functions */
 int FF_VOLUMES ; 
 int /*<<< orphan*/  const** ff_raw_handles ; 

BYTE ff_diskio_get_pdrv_raw(const esp_partition_t* part_handle)
{
    for (int i = 0; i < FF_VOLUMES; i++) {
        if (part_handle == ff_raw_handles[i]) {
            return i;
        }
    }
    return 0xff;
}