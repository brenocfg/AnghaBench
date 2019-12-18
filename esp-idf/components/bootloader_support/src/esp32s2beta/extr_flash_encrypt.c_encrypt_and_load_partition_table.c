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
typedef  int /*<<< orphan*/  esp_partition_info_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ESP_PARTITION_TABLE_MAX_LEN ; 
 int /*<<< orphan*/  ESP_PARTITION_TABLE_OFFSET ; 
 int /*<<< orphan*/  FLASH_SECTOR_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ bootloader_flash_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ esp_flash_encrypt_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_partition_table_verify (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static esp_err_t encrypt_and_load_partition_table(esp_partition_info_t *partition_table, int *num_partitions)
{
    esp_err_t err;
    /* Check for plaintext partition table */
    err = bootloader_flash_read(ESP_PARTITION_TABLE_OFFSET, partition_table, ESP_PARTITION_TABLE_MAX_LEN, false);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read partition table data");
        return err;
    }
    if (esp_partition_table_verify(partition_table, false, num_partitions) == ESP_OK) {
        ESP_LOGD(TAG, "partition table is plaintext. Encrypting...");
        esp_err_t err = esp_flash_encrypt_region(ESP_PARTITION_TABLE_OFFSET,
                                                 FLASH_SECTOR_SIZE);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to encrypt partition table in place. %x", err);
            return err;
        }
    }
    else {
        ESP_LOGE(TAG, "Failed to read partition table data - not plaintext?");
        return ESP_ERR_INVALID_STATE;
    }

    /* Valid partition table loded */
    return ESP_OK;
}