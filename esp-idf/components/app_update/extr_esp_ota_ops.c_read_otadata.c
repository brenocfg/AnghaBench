#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spi_flash_mmap_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_ota_select_entry_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_DATA_OTA ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_DATA ; 
 int /*<<< orphan*/  SPI_FLASH_MMAP_DATA ; 
 int SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* esp_partition_find_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_partition_mmap (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  spi_flash_munmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const esp_partition_t *read_otadata(esp_ota_select_entry_t *two_otadata)
{
    const esp_partition_t *otadata_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_OTA, NULL);

    if (otadata_partition == NULL) {
        ESP_LOGE(TAG, "not found otadata");
        return NULL;
    }

    spi_flash_mmap_handle_t ota_data_map;
    const void *result = NULL;
    esp_err_t err = esp_partition_mmap(otadata_partition, 0, otadata_partition->size, SPI_FLASH_MMAP_DATA, &result, &ota_data_map);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "mmap otadata filed. Err=0x%8x", err);
        return NULL;
    } else {
        memcpy(&two_otadata[0], result, sizeof(esp_ota_select_entry_t));
        memcpy(&two_otadata[1], result + SPI_FLASH_SEC_SIZE, sizeof(esp_ota_select_entry_t));
        spi_flash_munmap(ota_data_map);
    }
    return otadata_partition;
}