#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  store_data ;
typedef  int /*<<< orphan*/  spi_flash_mmap_handle_t ;
typedef  int /*<<< orphan*/  read_data ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ esp_partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_ANY ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_DATA ; 
 int /*<<< orphan*/  SPI_FLASH_MMAP_DATA ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  esp_partition_erase_range (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* esp_partition_find_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esp_partition_mmap (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_partition_write (TYPE_1__ const*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  spi_flash_munmap (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void app_main(void)
{
    /*
    * This example uses the partition table from ../partitions_example.csv. For reference, its contents are as follows:
    *
    *  nvs,        data, nvs,      0x9000,  0x6000,
    *  phy_init,   data, phy,      0xf000,  0x1000,
    *  factory,    app,  factory,  0x10000, 1M,
    *  storage,    data, ,             , 0x40000,
    */

    // Find the partition map in the partition table
    const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "storage");
    assert(partition != NULL);

    static const char store_data[] = "ESP-IDF Partition Memory Map Example";

    // Prepare data to be read later using the mapped address
    ESP_ERROR_CHECK(esp_partition_erase_range(partition, 0, partition->size));
    ESP_ERROR_CHECK(esp_partition_write(partition, 0, store_data, sizeof(store_data)));
    ESP_LOGI(TAG, "Written sample data to partition: %s", store_data);

    const void *map_ptr;
    spi_flash_mmap_handle_t map_handle;

    // Map the partition to data memory
    ESP_ERROR_CHECK(esp_partition_mmap(partition, 0, partition->size, SPI_FLASH_MMAP_DATA, &map_ptr, &map_handle));
    ESP_LOGI(TAG, "Mapped partition to data memory address %p", map_ptr);

    // Read back the written verification data using the mapped memory pointer
    char read_data[sizeof(store_data)];
    memcpy(read_data, map_ptr, sizeof(read_data));
    ESP_LOGI(TAG, "Read sample data from partition using mapped memory: %s", (char*) read_data);

    assert(strcmp(store_data, read_data) == 0);
    ESP_LOGI(TAG, "Data matches");

    // Unmap mapped memory
    spi_flash_munmap(map_handle);
    ESP_LOGI(TAG, "Unmapped partition from data memory");

    ESP_LOGI(TAG, "Example end");
}