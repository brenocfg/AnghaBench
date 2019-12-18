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
typedef  int /*<<< orphan*/  esp_ota_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OTA_SIZE_UNKNOWN ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_app_partition (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  esp_ota_begin (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ota_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * esp_ota_get_next_update_partition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ota_set_boot_partition (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * get_running_firmware () ; 

__attribute__((used)) static const esp_partition_t* app_update(void)
{
    const esp_partition_t *cur_app = get_running_firmware();
    const esp_partition_t* update_partition = esp_ota_get_next_update_partition(NULL);
    TEST_ASSERT_NOT_NULL(update_partition);
    esp_ota_handle_t update_handle = 0;
    TEST_ESP_OK(esp_ota_begin(update_partition, OTA_SIZE_UNKNOWN, &update_handle));
    copy_app_partition(update_handle, cur_app);
    TEST_ESP_OK(esp_ota_end(update_handle));
    TEST_ESP_OK(esp_ota_set_boot_partition(update_partition));
    return update_partition;
}