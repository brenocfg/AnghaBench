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
struct TYPE_3__ {int /*<<< orphan*/  subtype; } ;
typedef  TYPE_1__ esp_partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_APP_FACTORY ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_APP_OTA_0 ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_APP_OTA_1 ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_FAIL_MESSAGE (char*) ; 
 int /*<<< orphan*/  app_update () ; 
 int boot_count ; 
 int /*<<< orphan*/  erase_ota_data () ; 
 int /*<<< orphan*/  esp_ota_erase_last_boot_app_partition () ; 
 int /*<<< orphan*/  esp_ota_mark_app_invalid_rollback_and_reboot () ; 
 TYPE_1__* get_running_firmware () ; 
 int /*<<< orphan*/  mark_app_valid () ; 
 int /*<<< orphan*/  reboot_as_deep_sleep () ; 

__attribute__((used)) static void test_erase_last_app_flow(void)
{
    boot_count++;
    ESP_LOGI(TAG, "boot count %d", boot_count);
    const esp_partition_t *cur_app = get_running_firmware();
    switch (boot_count) {
        case 2:
            ESP_LOGI(TAG, "Factory");
            TEST_ASSERT_EQUAL(ESP_PARTITION_SUBTYPE_APP_FACTORY, cur_app->subtype);
            app_update();
            reboot_as_deep_sleep();
            break;
        case 3:
            ESP_LOGI(TAG, "OTA0");
            TEST_ASSERT_EQUAL(ESP_PARTITION_SUBTYPE_APP_OTA_0, cur_app->subtype);
            mark_app_valid();
            app_update();
            reboot_as_deep_sleep();
            break;
        case 4:
            ESP_LOGI(TAG, "OTA1");
            TEST_ASSERT_EQUAL(ESP_PARTITION_SUBTYPE_APP_OTA_1, cur_app->subtype);
            TEST_ESP_OK(esp_ota_erase_last_boot_app_partition());
            TEST_ESP_OK(esp_ota_mark_app_invalid_rollback_and_reboot());
            reboot_as_deep_sleep();
            break;
        default:
            erase_ota_data();
            TEST_FAIL_MESSAGE("Unexpected stage");
            break;
    }
}