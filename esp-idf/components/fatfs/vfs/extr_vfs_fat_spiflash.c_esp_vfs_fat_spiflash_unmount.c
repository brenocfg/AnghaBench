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
typedef  int /*<<< orphan*/  wl_handle_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int BYTE ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ esp_vfs_fat_unregister_path (char const*) ; 
 int /*<<< orphan*/  f_mount (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_diskio_clear_pdrv_wl (int /*<<< orphan*/ ) ; 
 int ff_diskio_get_pdrv_wl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_diskio_unregister (int) ; 
 scalar_t__ wl_unmount (int /*<<< orphan*/ ) ; 

esp_err_t esp_vfs_fat_spiflash_unmount(const char *base_path, wl_handle_t wl_handle)
{
    BYTE pdrv = ff_diskio_get_pdrv_wl(wl_handle);
    if (pdrv == 0xff) {
        return ESP_ERR_INVALID_STATE;
    }
    char drv[3] = {(char)('0' + pdrv), ':', 0};

    f_mount(0, drv, 0);
    ff_diskio_unregister(pdrv);
    ff_diskio_clear_pdrv_wl(wl_handle);
    // release partition driver
    esp_err_t err_drv = wl_unmount(wl_handle);
    esp_err_t err = esp_vfs_fat_unregister_path(base_path);
    if (err == ESP_OK) err = err_drv;
    return err;
}