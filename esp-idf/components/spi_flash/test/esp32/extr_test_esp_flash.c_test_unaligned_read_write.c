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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_STRING_LEN (char const*,char*,int) ; 
 scalar_t__ erase_test_region (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  esp_flash_read (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  esp_flash_write (int /*<<< orphan*/ *,char const*,scalar_t__,int) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int strlen (char const*) ; 

void test_unaligned_read_write(esp_flash_t *chip)
{
    ESP_LOGI(TAG, "Testing chip %p...", chip);
    uint32_t offs = erase_test_region(chip, 2);

    const char *msg = "i am a message";
    TEST_ASSERT(strlen(msg) + 1 % 4 != 0);
    TEST_ASSERT_EQUAL(ESP_OK, esp_flash_write(chip, msg, offs + 1, strlen(msg) + 1) );

    char buf[strlen(msg) + 1];

    memset(buf, 0xEE, sizeof(buf));

    TEST_ASSERT_EQUAL(ESP_OK, esp_flash_read(chip, buf, offs + 1, strlen(msg) + 1) );
    TEST_ASSERT_EQUAL_STRING_LEN(msg, buf, strlen(msg));
    TEST_ASSERT(memcmp(buf, msg, strlen(msg) + 1) == 0);
}