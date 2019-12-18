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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLC0TX_LINK ; 
 int /*<<< orphan*/  SLCCONF1 ; 
 int SLC_SLC0_RX_STITCH_EN ; 
 int SLC_SLC0_TXLINK_START ; 
 int SLC_SLC0_TX_STITCH_EN ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  slave_slc_reg_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  slave_slc_reg_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void esp32_slave_init_extra(sdmmc_card_t* card)
{
    printf("Initialize some ESP32 SDIO slave registers\n");

    uint32_t reg_val;
    TEST_ESP_OK( slave_slc_reg_read(card, SLCCONF1, &reg_val) );
    reg_val &= ~(SLC_SLC0_RX_STITCH_EN | SLC_SLC0_TX_STITCH_EN);
    TEST_ESP_OK( slave_slc_reg_write(card, SLCCONF1, reg_val) );

    TEST_ESP_OK( slave_slc_reg_read(card, SLC0TX_LINK, &reg_val) );
    reg_val |= SLC_SLC0_TXLINK_START;
    TEST_ESP_OK( slave_slc_reg_write(card, SLC0TX_LINK, reg_val) );
}