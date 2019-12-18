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
typedef  int /*<<< orphan*/  esp_flash_enc_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EFUSE_DISABLE_DL_CACHE ; 
 int /*<<< orphan*/  ESP_EFUSE_DISABLE_DL_DECRYPT ; 
 int /*<<< orphan*/  ESP_EFUSE_DISABLE_DL_ENCRYPT ; 
 int /*<<< orphan*/  ESP_EFUSE_WR_DIS_FLASH_CRYPT_CNT ; 
 int /*<<< orphan*/  ESP_FLASH_ENC_MODE_DEVELOPMENT ; 
 int /*<<< orphan*/  ESP_FLASH_ENC_MODE_DISABLED ; 
 int /*<<< orphan*/  ESP_FLASH_ENC_MODE_RELEASE ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ esp_flash_encryption_enabled () ; 

esp_flash_enc_mode_t esp_get_flash_encryption_mode(void)
{
    uint8_t efuse_flash_crypt_cnt_wr_protected = 0;
    uint8_t dis_dl_enc = 0, dis_dl_dec = 0, dis_dl_cache = 0;
    esp_flash_enc_mode_t mode = ESP_FLASH_ENC_MODE_DEVELOPMENT;

    if (esp_flash_encryption_enabled()) {
        /* Check if FLASH CRYPT CNT is write protected */
        esp_efuse_read_field_blob(ESP_EFUSE_WR_DIS_FLASH_CRYPT_CNT, &efuse_flash_crypt_cnt_wr_protected, 1);
        if (efuse_flash_crypt_cnt_wr_protected) {
            esp_efuse_read_field_blob(ESP_EFUSE_DISABLE_DL_CACHE, &dis_dl_cache, 1);
            esp_efuse_read_field_blob(ESP_EFUSE_DISABLE_DL_ENCRYPT, &dis_dl_enc, 1);
            esp_efuse_read_field_blob(ESP_EFUSE_DISABLE_DL_DECRYPT, &dis_dl_dec, 1);
            /* Check if DISABLE_DL_DECRYPT, DISABLE_DL_ENCRYPT & DISABLE_DL_CACHE are set */
            if ( dis_dl_cache && dis_dl_enc && dis_dl_dec ) {
                mode = ESP_FLASH_ENC_MODE_RELEASE;
            }
        }
    } else {
        mode = ESP_FLASH_ENC_MODE_DISABLED;
    }

    return mode;
}