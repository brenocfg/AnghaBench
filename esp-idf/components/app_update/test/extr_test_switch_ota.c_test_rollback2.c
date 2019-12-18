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
struct TYPE_5__ {int subtype; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int esp_ota_img_states_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OTA_IMG_NEW ; 
 int /*<<< orphan*/  ESP_OTA_IMG_PENDING_VERIFY ; 
 int /*<<< orphan*/  ESP_OTA_IMG_UNDEFINED ; 
 int /*<<< orphan*/  ESP_OTA_IMG_VALID ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_APP_FACTORY ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_APP_OTA_0 ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_APP_OTA_1 ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_FAIL_MESSAGE (char*) ; 
 TYPE_1__* app_update () ; 
 int boot_count ; 
 int /*<<< orphan*/  erase_ota_data () ; 
 int /*<<< orphan*/  esp_ota_get_last_invalid_partition () ; 
 int /*<<< orphan*/  esp_ota_get_state_partition (TYPE_1__ const*,int*) ; 
 int /*<<< orphan*/  esp_ota_mark_app_invalid_rollback_and_reboot () ; 
 int /*<<< orphan*/  esp_ota_mark_app_valid_cancel_rollback () ; 
 TYPE_1__* get_running_firmware () ; 
 int /*<<< orphan*/  reboot_as_deep_sleep () ; 

__attribute__((used)) static void test_rollback2(void)
{
    boot_count++;
    ESP_LOGI(TAG, "boot count %d", boot_count);
    const esp_partition_t *cur_app = get_running_firmware();
    esp_ota_img_states_t ota_state = 0x5555AAAA;
    const esp_partition_t* update_partition = NULL;
    switch (boot_count) {
        case 2:
            ESP_LOGI(TAG, "Factory");
            TEST_ASSERT_EQUAL(ESP_PARTITION_SUBTYPE_APP_FACTORY, cur_app->subtype);
            TEST_ASSERT_NULL(esp_ota_get_last_invalid_partition());
            TEST_ESP_ERR(ESP_ERR_NOT_SUPPORTED, esp_ota_get_state_partition(cur_app, &ota_state));
            update_partition = app_update();
            TEST_ESP_OK(esp_ota_get_state_partition(update_partition, &ota_state));
#ifndef CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE
            TEST_ASSERT_EQUAL(ESP_OTA_IMG_UNDEFINED, ota_state);
#else
            TEST_ASSERT_EQUAL(ESP_OTA_IMG_NEW, ota_state);
#endif
            reboot_as_deep_sleep();
            break;
        case 3:
            ESP_LOGI(TAG, "OTA0");
            TEST_ASSERT_EQUAL(ESP_PARTITION_SUBTYPE_APP_OTA_0, cur_app->subtype);
            TEST_ASSERT_NULL(esp_ota_get_last_invalid_partition());
            TEST_ESP_OK(esp_ota_get_state_partition(cur_app, &ota_state));
#ifndef CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE
            TEST_ASSERT_EQUAL(ESP_OTA_IMG_UNDEFINED, ota_state);
#else
            TEST_ASSERT_EQUAL(ESP_OTA_IMG_PENDING_VERIFY, ota_state);
#endif
            TEST_ESP_OK(esp_ota_mark_app_valid_cancel_rollback());
            TEST_ASSERT_NULL(esp_ota_get_last_invalid_partition());
            TEST_ESP_OK(esp_ota_get_state_partition(cur_app, &ota_state));
            TEST_ASSERT_EQUAL(ESP_OTA_IMG_VALID, ota_state);
            update_partition = app_update();
            TEST_ESP_OK(esp_ota_get_state_partition(update_partition, &ota_state));
#ifndef CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE
            TEST_ASSERT_EQUAL(ESP_OTA_IMG_UNDEFINED, ota_state);
#else
            TEST_ASSERT_EQUAL(ESP_OTA_IMG_NEW, ota_state);
#endif
            reboot_as_deep_sleep();
            break;
        case 4:
            ESP_LOGI(TAG, "OTA1");
            TEST_ASSERT_EQUAL(ESP_PARTITION_SUBTYPE_APP_OTA_1, cur_app->subtype);
            TEST_ASSERT_NULL(esp_ota_get_last_invalid_partition());
            TEST_ESP_OK(esp_ota_get_state_partition(cur_app, &ota_state));
#ifndef CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE
            TEST_ASSERT_EQUAL(ESP_OTA_IMG_UNDEFINED, ota_state);
            TEST_ESP_OK(esp_ota_mark_app_invalid_rollback_and_reboot());
#else
            TEST_ASSERT_EQUAL(ESP_OTA_IMG_PENDING_VERIFY, ota_state);
            reboot_as_deep_sleep();
#endif
            break;
        default:
            erase_ota_data();
            TEST_FAIL_MESSAGE("Unexpected stage");
            break;
    }
}