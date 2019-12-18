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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX8 (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ erase_test_region (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  esp_flash_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  esp_flash_write (int /*<<< orphan*/ *,unsigned int*,scalar_t__,int) ; 

void test_single_read_write(esp_flash_t* chip)
{
    ESP_LOGI(TAG, "Testing chip %p...", chip);
    uint32_t offs = erase_test_region(chip, 2);

    for (unsigned v = 0; v < 512; v++) {
        TEST_ASSERT_EQUAL_HEX(ESP_OK, esp_flash_write(chip, &v, offs + v, 1) );
    }

    for (unsigned v = 0; v < 512; v++) {
        uint8_t readback;
        TEST_ASSERT_EQUAL_HEX(ESP_OK, esp_flash_read(chip, &readback, offs + v, 1) );
        TEST_ASSERT_EQUAL_HEX8(v, readback);
    }
}