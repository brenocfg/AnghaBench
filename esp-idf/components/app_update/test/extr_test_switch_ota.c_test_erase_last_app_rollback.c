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
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_APP_FACTORY ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int boot_count ; 
 int /*<<< orphan*/  erase_ota_data () ; 
 int /*<<< orphan*/  esp_ota_erase_last_boot_app_partition () ; 
 TYPE_1__* get_running_firmware () ; 

__attribute__((used)) static void test_erase_last_app_rollback(void)
{
    boot_count = 5;
    ESP_LOGI(TAG, "boot count %d", boot_count);
    const esp_partition_t *cur_app = get_running_firmware();
    ESP_LOGI(TAG, "erase_last_app");
    TEST_ASSERT_EQUAL(ESP_PARTITION_SUBTYPE_APP_FACTORY, cur_app->subtype);
    TEST_ESP_ERR(ESP_FAIL, esp_ota_erase_last_boot_app_partition());
    erase_ota_data();
}