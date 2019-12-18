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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ size; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 TYPE_1__* get_test_data_partition () ; 
 int /*<<< orphan*/  read_and_check (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  write_large_buffer (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void test_write_large_buffer(esp_flash_t *chip, const uint8_t *source, size_t length)
{
    ESP_LOGI(TAG, "Testing chip %p...", chip);
    const esp_partition_t *part = get_test_data_partition();
    TEST_ASSERT(part->size > length + 2 + SPI_FLASH_SEC_SIZE);

    write_large_buffer(chip, part, source, length);
    read_and_check(chip, part, source, length);
}