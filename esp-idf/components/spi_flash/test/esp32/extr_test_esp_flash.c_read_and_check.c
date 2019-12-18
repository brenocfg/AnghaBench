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
typedef  int uint8_t ;
struct TYPE_3__ {scalar_t__ address; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  int /*<<< orphan*/  ends ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX8 (int const,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX8_ARRAY (int const*,int*,size_t) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int*) ; 
 int /*<<< orphan*/  esp_flash_read (int /*<<< orphan*/ *,int*,scalar_t__,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void read_and_check(esp_flash_t *chip, const esp_partition_t *part, const uint8_t *source, size_t length)
{
    printf("Checking chip %p, %d bytes\n", chip, length);
    uint8_t *buf = malloc(length);
    TEST_ASSERT_NOT_NULL(buf);
    ESP_ERROR_CHECK( esp_flash_read(chip, buf, part->address + 1, length) );
    TEST_ASSERT_EQUAL_HEX8_ARRAY(source, buf, length);
    free(buf);

    // check nothing was written at beginning or end
    uint8_t ends[8];

    ESP_ERROR_CHECK( esp_flash_read(chip, ends, part->address, sizeof(ends)) );
    TEST_ASSERT_EQUAL_HEX8(0xFF, ends[0]);
    TEST_ASSERT_EQUAL_HEX8(source[0], ends[1]);

    ESP_ERROR_CHECK( esp_flash_read(chip, ends, part->address + length, sizeof(ends)) );

    TEST_ASSERT_EQUAL_HEX8(source[length - 1], ends[0]);
    TEST_ASSERT_EQUAL_HEX8(0xFF, ends[1]);
    TEST_ASSERT_EQUAL_HEX8(0xFF, ends[2]);
    TEST_ASSERT_EQUAL_HEX8(0xFF, ends[3]);
}