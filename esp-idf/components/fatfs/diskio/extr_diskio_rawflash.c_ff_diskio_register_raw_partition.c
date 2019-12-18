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
struct TYPE_3__ {int /*<<< orphan*/ * ioctl; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; int /*<<< orphan*/ * status; int /*<<< orphan*/ * init; } ;
typedef  TYPE_1__ ff_diskio_impl_t ;
typedef  int /*<<< orphan*/  esp_partition_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 size_t FF_VOLUMES ; 
 int /*<<< orphan*/  ff_diskio_register (size_t,TYPE_1__ const*) ; 
 int /*<<< orphan*/  const** ff_raw_handles ; 
 int /*<<< orphan*/  ff_raw_initialize ; 
 int /*<<< orphan*/  ff_raw_ioctl ; 
 int /*<<< orphan*/  ff_raw_read ; 
 int /*<<< orphan*/  ff_raw_status ; 
 int /*<<< orphan*/  ff_raw_write ; 

esp_err_t ff_diskio_register_raw_partition(BYTE pdrv, const esp_partition_t* part_handle)
{
    if (pdrv >= FF_VOLUMES) {
        return ESP_ERR_INVALID_ARG;
    }
    static const ff_diskio_impl_t raw_impl = {
        .init = &ff_raw_initialize,
        .status = &ff_raw_status,
        .read = &ff_raw_read,
        .write = &ff_raw_write,
        .ioctl = &ff_raw_ioctl
    };
    ff_diskio_register(pdrv, &raw_impl);
    ff_raw_handles[pdrv] = part_handle;
    return ESP_OK;

}