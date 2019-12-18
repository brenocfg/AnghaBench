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
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ address; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX32 (int,int) ; 
 int /*<<< orphan*/  esp_flash_erase_region (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  esp_flash_read (int /*<<< orphan*/ *,int*,scalar_t__,int) ; 
 int /*<<< orphan*/  esp_flash_write (int /*<<< orphan*/ *,char const*,scalar_t__,int) ; 
 TYPE_1__* get_test_data_partition () ; 

void test_erase_large_region(esp_flash_t *chip)
{
    ESP_LOGI(TAG, "Testing chip %p...", chip);

    const esp_partition_t *part = get_test_data_partition();

    /* Write some noise at the start and the end of the region */
    const char *ohai = "OHAI";
    uint32_t readback;
    TEST_ASSERT_EQUAL(ESP_OK, esp_flash_write(chip, ohai, part->address, 5));
    TEST_ASSERT_EQUAL(ESP_OK, esp_flash_write(chip, ohai, part->address + part->size - 5, 5));

    /* sanity check what we just wrote. since the partition may haven't been erased, we only check the part which is written to 0. */
    uint32_t written_data = *((const uint32_t *)ohai);
    TEST_ASSERT_EQUAL(ESP_OK, esp_flash_read(chip, &readback, part->address + part->size - 5, 4));
    TEST_ASSERT_EQUAL_HEX32(0, readback & (~written_data));
    TEST_ASSERT_EQUAL(ESP_OK, esp_flash_read(chip, &readback, part->address, 4));
    TEST_ASSERT_EQUAL_HEX32(0, readback & (~written_data));

    /* Erase whole region */
    TEST_ASSERT_EQUAL(ESP_OK, esp_flash_erase_region(chip, part->address, part->size));

    /* ensure both areas we wrote are now all-FFs */
    TEST_ASSERT_EQUAL(ESP_OK, esp_flash_read(chip, &readback, part->address, 4));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, readback);

    TEST_ASSERT_EQUAL(ESP_OK, esp_flash_read(chip, &readback, part->address + part->size - 5, 4));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, readback);
}