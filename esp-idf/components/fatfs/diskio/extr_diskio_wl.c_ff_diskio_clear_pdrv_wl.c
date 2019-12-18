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
typedef  scalar_t__ wl_handle_t ;

/* Variables and functions */
 int FF_VOLUMES ; 
 scalar_t__ WL_INVALID_HANDLE ; 
 scalar_t__* ff_wl_handles ; 

void ff_diskio_clear_pdrv_wl(wl_handle_t flash_handle)
{
    for (int i = 0; i < FF_VOLUMES; i++) {
        if (flash_handle == ff_wl_handles[i]) {
            ff_wl_handles[i] = WL_INVALID_HANDLE;
        }
    }
}