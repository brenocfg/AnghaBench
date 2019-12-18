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
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DRESULT ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  RES_ERROR ; 
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** s_cards ; 
 scalar_t__ sdmmc_write_sectors (int /*<<< orphan*/ *,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DRESULT ff_sdmmc_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count)
{
    sdmmc_card_t* card = s_cards[pdrv];
    assert(card);
    esp_err_t err = sdmmc_write_sectors(card, buff, sector, count);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "sdmmc_write_blocks failed (%d)", err);
        return RES_ERROR;
    }
    return RES_OK;
}