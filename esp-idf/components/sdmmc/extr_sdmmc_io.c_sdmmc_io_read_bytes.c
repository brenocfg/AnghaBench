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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int SD_ARG_CMD53_INCREMENT ; 
 int SD_ARG_CMD53_READ ; 
 scalar_t__ sdmmc_io_rw_extended (int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ *,size_t) ; 

esp_err_t sdmmc_io_read_bytes(sdmmc_card_t* card, uint32_t function,
        uint32_t addr, void* dst, size_t size)
{
    /* host quirk: SDIO transfer with length not divisible by 4 bytes
     * has to be split into two transfers: one with aligned length,
     * the other one for the remaining 1-3 bytes.
     */
    uint8_t *pc_dst = dst;
    while (size > 0) {
        size_t size_aligned = size & (~3);
        size_t will_transfer = size_aligned > 0 ? size_aligned : size;

        esp_err_t err = sdmmc_io_rw_extended(card, function, addr,
                SD_ARG_CMD53_READ | SD_ARG_CMD53_INCREMENT,
                pc_dst, will_transfer);
        if (err != ESP_OK) {
            return err;
        }
        pc_dst += will_transfer;
        size -= will_transfer;
        addr += will_transfer;
    }
    return ESP_OK;
}