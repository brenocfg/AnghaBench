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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;

/* Variables and functions */
 int SD_IO_CCCR_BLKSIZEH ; 
 int SD_IO_CCCR_BLKSIZEL ; 
 int SD_IO_FBR_START ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdmmc_io_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_io_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdio_slave_set_blocksize(sdmmc_card_t* card, int function, uint16_t bs)
{
    const uint8_t* bs_u8 = (const uint8_t*) &bs;
    uint16_t bs_read = 0;
    uint8_t* bs_read_u8 = (uint8_t*) &bs_read;
    uint32_t offset = SD_IO_FBR_START * function;
    TEST_ESP_OK( sdmmc_io_write_byte(card, 0, offset + SD_IO_CCCR_BLKSIZEL, bs_u8[0], NULL));
    TEST_ESP_OK( sdmmc_io_write_byte(card, 0, offset + SD_IO_CCCR_BLKSIZEH, bs_u8[1], NULL));
    TEST_ESP_OK( sdmmc_io_read_byte(card, 0, offset + SD_IO_CCCR_BLKSIZEL, &bs_read_u8[0]));
    TEST_ESP_OK( sdmmc_io_read_byte(card, 0, offset + SD_IO_CCCR_BLKSIZEH, &bs_read_u8[1]));
    TEST_ASSERT_EQUAL_HEX16(bs, bs_read);
}