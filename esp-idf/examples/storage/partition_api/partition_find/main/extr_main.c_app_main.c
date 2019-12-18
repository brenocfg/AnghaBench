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
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  address; int /*<<< orphan*/  label; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/ * esp_partition_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_ANY ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_APP_FACTORY ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_DATA_FAT ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_DATA_NVS ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_DATA_PHY ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_APP ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_DATA ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * esp_partition_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* esp_partition_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_partition_iterator_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * esp_partition_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_partition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void app_main(void)
{
    /* 
    * This example uses the partition table from ../partitions_example.csv. For reference, its contents are as follows:
    * 
    *  nvs,        data, nvs,      0x9000,  0x6000,
    *  phy_init,   data, phy,      0xf000,  0x1000,
    *  factory,    app,  factory,  0x10000, 1M,
    *  storage1,   data, fat,             , 0x40000,
    *  storage2,   data, fat,             , 0x40000,
    * 
    * Display the partition table to the user for reference.
    */
    extern const char csv_start[] asm("_binary_partitions_example_csv_start");
    extern const char csv_end[]   asm("_binary_partitions_example_csv_end");

    ESP_LOGI(TAG, "Printing partition table csv file contents for reference...\n\n%.*s", csv_end - csv_start + 1, csv_start);

    /* First Part - Finding partitions using esp_partition_find_first. */

    ESP_LOGI(TAG, "----------------Find partitions---------------");

    // Find partitions using esp_partition_find_first(). This returns the first partition matching the passed constraints.
    find_partition(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
    find_partition(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_PHY, NULL);
    find_partition(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_FACTORY, NULL);

    find_partition(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_FAT, NULL);

    ESP_LOGI(TAG, "Find second FAT partition by specifying the label");
    // In case of multiple matches, `esp_partition_find_first` returns the first match.
    find_partition(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_FAT, "storage2");

    /* Second Part - Iterating over partitions */

    ESP_LOGI(TAG, "----------------Iterate through partitions---------------");
    
    esp_partition_iterator_t it;

    ESP_LOGI(TAG, "Iterating through app partitions...");
    it = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, NULL);

    // Loop through all matching partitions, in this case, all with the type 'data' until partition with desired 
    // label is found. Verify if its the same instance as the one found before.
    for (; it != NULL; it = esp_partition_next(it)) {
        const esp_partition_t *part = esp_partition_get(it);
        ESP_LOGI(TAG, "\tfound partition '%s' at offset 0x%x with size 0x%x", part->label, part->address, part->size);
    }
    // Release the partition iterator to release memory allocated for it
    esp_partition_iterator_release(it);

    ESP_LOGI(TAG, "Iterating through data partitions...");
    it = esp_partition_find(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, NULL);

    // Loop through all matching partitions, in this case, all with the type 'data' until partition with desired 
    // label is found. Verify if its the same instance as the one found before.
    for (; it != NULL; it = esp_partition_next(it)) {
        const esp_partition_t *part = esp_partition_get(it);
        ESP_LOGI(TAG, "\tfound partition '%s' at offset 0x%x with size 0x%x", part->label, part->address, part->size);
    }

    // Release the partition iterator to release memory allocated for it
    esp_partition_iterator_release(it);

    ESP_LOGI(TAG, "Example end");
}