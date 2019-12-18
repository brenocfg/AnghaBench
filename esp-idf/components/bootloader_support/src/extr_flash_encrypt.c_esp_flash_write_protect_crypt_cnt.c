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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EFUSE_WR_DIS_FLASH_CRYPT_CNT ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  esp_efuse_write_field_cnt (int /*<<< orphan*/ ,int) ; 

void esp_flash_write_protect_crypt_cnt(void)
{
    uint8_t flash_crypt_cnt_wr_dis = 0;
    esp_efuse_read_field_blob(ESP_EFUSE_WR_DIS_FLASH_CRYPT_CNT, &flash_crypt_cnt_wr_dis, 1);
    if (!flash_crypt_cnt_wr_dis) {
        esp_efuse_write_field_cnt(ESP_EFUSE_WR_DIS_FLASH_CRYPT_CNT, 1);
    }
}