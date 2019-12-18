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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_DATA_FAT ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_DATA ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * esp_partition_find_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  esp_vfs_fat_unregister_path (char const*) ; 
 int /*<<< orphan*/  f_mount (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ff_diskio_get_pdrv_raw (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ff_diskio_unregister (int) ; 

esp_err_t esp_vfs_fat_rawflash_unmount(const char *base_path, const char* partition_label)
{
    const esp_partition_t *data_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA,
            ESP_PARTITION_SUBTYPE_DATA_FAT, partition_label);

    if (data_partition == NULL) {
        ESP_LOGE(TAG, "Failed to find FATFS partition (type='data', subtype='fat', partition_label='%s'). Check the partition table.", partition_label);
        return ESP_ERR_NOT_FOUND;
    }

    BYTE pdrv = ff_diskio_get_pdrv_raw(data_partition);
    if (pdrv == 0xff) {
        return ESP_ERR_INVALID_STATE;
    }
    char drv[3] = {(char)('0' + pdrv), ':', 0};

    f_mount(0, drv, 0);
    ff_diskio_unregister(pdrv);
    esp_err_t err = esp_vfs_fat_unregister_path(base_path);
    return err;
}