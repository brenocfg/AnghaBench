#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  address; int /*<<< orphan*/  subtype; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_ota_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTA_SIZE_UNKNOWN ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_app_partition (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  esp_ota_begin (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ota_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ota_get_next_update_partition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ota_set_boot_partition (TYPE_1__ const*) ; 

__attribute__((used)) static void copy_current_app_to_next_part(const esp_partition_t *cur_app_partition, const esp_partition_t *next_app_partition)
{
    esp_ota_get_next_update_partition(NULL);
    TEST_ASSERT_NOT_EQUAL(NULL, next_app_partition);
    ESP_LOGI(TAG, "Writing to partition subtype %d at offset 0x%x", next_app_partition->subtype, next_app_partition->address);

    esp_ota_handle_t update_handle = 0;
    TEST_ESP_OK(esp_ota_begin(next_app_partition, OTA_SIZE_UNKNOWN, &update_handle));

    copy_app_partition(update_handle, cur_app_partition);

    TEST_ESP_OK(esp_ota_end(update_handle));
    TEST_ESP_OK(esp_ota_set_boot_partition(next_app_partition));
}