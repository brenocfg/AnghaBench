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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 char* esp_get_idf_version () ; 
 int /*<<< orphan*/  example_add_partition (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  example_get_fatfs_usage (size_t*,size_t*) ; 
 int /*<<< orphan*/ * example_init_ext_flash () ; 
 int /*<<< orphan*/  example_list_data_partitions () ; 
 int /*<<< orphan*/  example_mount_fatfs (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* strchr (char*,char) ; 

void app_main(void)
{
    // Set up SPI bus and initialize the external SPI Flash chip
    esp_flash_t* flash = example_init_ext_flash();
    if (flash == NULL) {
        return;
    }

    // Add the entire external flash chip as a partition
    const char *partition_label = "storage";
    example_add_partition(flash, partition_label);

    // List the available partitions
    example_list_data_partitions();

    // Initialize FAT FS in the partition
    if (!example_mount_fatfs(partition_label)) {
        return;
    }

    // Print FAT FS size information
    size_t bytes_total, bytes_free;
    example_get_fatfs_usage(&bytes_total, &bytes_free);
    ESP_LOGI(TAG, "FAT FS: %d kB total, %d kB free", bytes_total / 1024, bytes_free / 1024);

    // Create a file in FAT FS
    ESP_LOGI(TAG, "Opening file");
    FILE *f = fopen("/extflash/hello.txt", "wb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }
    fprintf(f, "Written using ESP-IDF %s\n", esp_get_idf_version());
    fclose(f);
    ESP_LOGI(TAG, "File written");

    // Open file for reading
    ESP_LOGI(TAG, "Reading file");
    f = fopen("/extflash/hello.txt", "rb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }
    char line[128];
    fgets(line, sizeof(line), f);
    fclose(f);
    // strip newline
    char *pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    ESP_LOGI(TAG, "Read from file: '%s'", line);
}