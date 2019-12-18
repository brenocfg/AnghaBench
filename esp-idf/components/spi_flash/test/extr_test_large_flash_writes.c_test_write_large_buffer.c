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
struct TYPE_3__ {size_t size; scalar_t__ address; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  ends ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 size_t SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX8 (int const,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX8_ARRAY (int const*,int*,size_t) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int*) ; 
 int /*<<< orphan*/  free (int*) ; 
 TYPE_1__* get_test_data_partition () ; 
 int* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,size_t,int const*) ; 
 int /*<<< orphan*/  spi_flash_erase_range (scalar_t__,size_t) ; 
 int /*<<< orphan*/  spi_flash_read (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  spi_flash_write (scalar_t__,int const*,size_t) ; 

__attribute__((used)) static void test_write_large_buffer(const uint8_t *source, size_t length)
{
    const esp_partition_t *part = get_test_data_partition();
    TEST_ASSERT(part->size > length + 2 + SPI_FLASH_SEC_SIZE);

    printf("Writing %d bytes from source %p\n", length, source);

    uint8_t *buf = malloc(length);
    TEST_ASSERT_NOT_NULL(buf);

    ESP_ERROR_CHECK( spi_flash_erase_range(part->address, (length + SPI_FLASH_SEC_SIZE) & ~(SPI_FLASH_SEC_SIZE-1)) );

    // note writing to unaligned address
    ESP_ERROR_CHECK( spi_flash_write(part->address + 1, source, length) );

    ESP_ERROR_CHECK( spi_flash_read(part->address + 1, buf, length) );

    TEST_ASSERT_EQUAL_HEX8_ARRAY(source, buf, length);

    free(buf);

    // check nothing was written at beginning or end
    uint8_t ends[8];

    ESP_ERROR_CHECK( spi_flash_read(part->address, ends, sizeof(ends)) );
    TEST_ASSERT_EQUAL_HEX8(0xFF, ends[0]);
    TEST_ASSERT_EQUAL_HEX8(source[0] , ends[1]);

    ESP_ERROR_CHECK( spi_flash_read(part->address + length, ends, sizeof(ends)) );

    TEST_ASSERT_EQUAL_HEX8(source[length-1], ends[0]);
    TEST_ASSERT_EQUAL_HEX8(0xFF, ends[1]);
    TEST_ASSERT_EQUAL_HEX8(0xFF, ends[2]);
    TEST_ASSERT_EQUAL_HEX8(0xFF, ends[3]);
}