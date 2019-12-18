#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int size; } ;
typedef  TYPE_1__ esp_partition_t ;
struct TYPE_11__ {int ota_seq; scalar_t__ crc; } ;
typedef  TYPE_2__ esp_ota_select_entry_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ ESP_PARTITION_SUBTYPE_APP_OTA_MIN ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_APP ; 
 int SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 int UINT32_MAX ; 
 int bootloader_common_get_active_otadata (TYPE_2__*) ; 
 scalar_t__ bootloader_common_ota_select_crc (TYPE_2__*) ; 
 TYPE_1__* esp_ota_get_running_partition () ; 
 scalar_t__ esp_partition_erase_range (TYPE_1__ const*,int,int) ; 
 TYPE_1__* esp_partition_find_first (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int get_ota_partition_count () ; 
 TYPE_1__* read_otadata (TYPE_2__*) ; 

esp_err_t esp_ota_erase_last_boot_app_partition(void)
{
    esp_ota_select_entry_t otadata[2];
    const esp_partition_t* ota_data_partition = read_otadata(otadata);
    if (ota_data_partition == NULL) {
        return ESP_FAIL;
    }

    int active_otadata = bootloader_common_get_active_otadata(otadata);
    int ota_app_count = get_ota_partition_count();
    if (active_otadata == -1 || ota_app_count == 0) {
        return ESP_FAIL;
    }

    int inactive_otadata = (~active_otadata)&1;
    if (otadata[inactive_otadata].ota_seq == UINT32_MAX || otadata[inactive_otadata].crc != bootloader_common_ota_select_crc(&otadata[inactive_otadata])) {
        return ESP_FAIL;
    }

    int ota_slot = (otadata[inactive_otadata].ota_seq - 1) % ota_app_count; // Actual OTA partition selection
    ESP_LOGD(TAG, "finding last_boot_app_partition ota_%d app...", ESP_PARTITION_SUBTYPE_APP_OTA_MIN + ota_slot);

    const esp_partition_t* last_boot_app_partition_from_otadata = esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_MIN + ota_slot, NULL);
    if (last_boot_app_partition_from_otadata == NULL) {
        return ESP_FAIL;
    }

    const esp_partition_t* running_partition = esp_ota_get_running_partition();
    if (running_partition == NULL || last_boot_app_partition_from_otadata == running_partition) {
        return ESP_FAIL;
    }

    esp_err_t err = esp_partition_erase_range(last_boot_app_partition_from_otadata, 0, last_boot_app_partition_from_otadata->size);
    if (err != ESP_OK) {
        return err;
    }

    int sec_id = inactive_otadata;
    err = esp_partition_erase_range(ota_data_partition, sec_id * SPI_FLASH_SEC_SIZE, SPI_FLASH_SEC_SIZE);
    if (err != ESP_OK) {
        return err;
    }

    return ESP_OK;
}