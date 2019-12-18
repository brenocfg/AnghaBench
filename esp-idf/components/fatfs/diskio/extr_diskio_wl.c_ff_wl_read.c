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
typedef  scalar_t__ esp_err_t ;
typedef  int UINT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DRESULT ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  RES_ERROR ; 
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__* ff_wl_handles ; 
 scalar_t__ wl_read (scalar_t__,int,size_t*,int) ; 
 int wl_sector_size (scalar_t__) ; 

DRESULT ff_wl_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
    ESP_LOGV(TAG, "ff_wl_read - pdrv=%i, sector=%i, count=%i\n", (unsigned int)pdrv, (unsigned int)sector, (unsigned int)count);
    wl_handle_t wl_handle = ff_wl_handles[pdrv];
    assert(wl_handle + 1);
    esp_err_t err = wl_read(wl_handle, sector * wl_sector_size(wl_handle), buff, count * wl_sector_size(wl_handle));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "wl_read failed (%d)", err);
        return RES_ERROR;
    }
    return RES_OK;
}