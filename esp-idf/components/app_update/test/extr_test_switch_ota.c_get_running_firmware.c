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
struct TYPE_8__ {scalar_t__ subtype; int /*<<< orphan*/  address; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ esp_partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_PARTITION_SUBTYPE_APP_TEST ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_PTR (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 TYPE_1__* esp_ota_get_boot_partition () ; 
 TYPE_1__* esp_ota_get_running_partition () ; 

__attribute__((used)) static const esp_partition_t* get_running_firmware(void)
{
    const esp_partition_t *configured = esp_ota_get_boot_partition();
    const esp_partition_t *running = esp_ota_get_running_partition();
    ESP_LOGI(TAG, "Running partition type %d subtype %d (offset 0x%08x)",
            running->type, running->subtype, running->address);
    ESP_LOGI(TAG, "Configured partition type %d subtype %d (offset 0x%08x)",
            configured->type, configured->subtype, configured->address);
    TEST_ASSERT_NOT_EQUAL(NULL, configured);
    TEST_ASSERT_NOT_EQUAL(NULL, running);
    if (running->subtype != ESP_PARTITION_SUBTYPE_APP_TEST) {
        TEST_ASSERT_EQUAL_PTR(running, configured);
    }
    return running;
}