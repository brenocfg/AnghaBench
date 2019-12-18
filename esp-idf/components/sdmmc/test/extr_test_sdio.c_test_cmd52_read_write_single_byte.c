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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 size_t DR_REG_SLCHOST_BASE ; 
 size_t SLCHOST_CONF_W0 ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_UINT8 (int const,int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sdmmc_io_read_byte (int /*<<< orphan*/ *,int,size_t const,int*) ; 
 int /*<<< orphan*/  sdmmc_io_write_byte (int /*<<< orphan*/ *,int,size_t const,int const,int*) ; 

__attribute__((used)) static void test_cmd52_read_write_single_byte(sdmmc_card_t* card)
{
    esp_err_t err;
    printf("Write bytes to slave's W0_REG using CMD52\n");
    const size_t scratch_area_reg = SLCHOST_CONF_W0 - DR_REG_SLCHOST_BASE;

    const uint8_t test_byte_1 = 0xa5;
    const uint8_t test_byte_2 = 0xb6;
    // used to check Read-After-Write
    uint8_t test_byte_1_raw;
    uint8_t test_byte_2_raw;
    uint8_t val = 0;
    err = sdmmc_io_write_byte(card, 1, scratch_area_reg, test_byte_1, &test_byte_1_raw);
    TEST_ESP_OK(err);
    TEST_ASSERT_EQUAL_UINT8(test_byte_1, test_byte_1_raw);
    err = sdmmc_io_write_byte(card, 1, scratch_area_reg + 1, test_byte_2, &test_byte_2_raw);
    TEST_ESP_OK(err);
    TEST_ASSERT_EQUAL_UINT8(test_byte_2, test_byte_2_raw);

    printf("Read back bytes using CMD52\n");
    TEST_ESP_OK(sdmmc_io_read_byte(card, 1, scratch_area_reg, &val));
    TEST_ASSERT_EQUAL_UINT8(test_byte_1, val);

    TEST_ESP_OK(sdmmc_io_read_byte(card, 1, scratch_area_reg + 1, &val));
    TEST_ASSERT_EQUAL_UINT8(test_byte_2, val);
}