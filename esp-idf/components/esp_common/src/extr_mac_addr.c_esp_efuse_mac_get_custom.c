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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EFUSE_MAC_CUSTOM ; 
 int /*<<< orphan*/  ESP_EFUSE_MAC_CUSTOM_CRC ; 
 int /*<<< orphan*/  ESP_EFUSE_MAC_CUSTOM_VER ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_CRC ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_VERSION ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int esp_crc8 (int*,int) ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,int*,int) ; 

esp_err_t esp_efuse_mac_get_custom(uint8_t *mac)
{
#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
    return ESP_ERR_NOT_SUPPORTED; // TODO: support custom MAC in efuse
#else
    uint8_t version;
    esp_efuse_read_field_blob(ESP_EFUSE_MAC_CUSTOM_VER, &version, 8);
    if (version != 1) {
        ESP_LOGE(TAG, "Base MAC address from BLK3 of EFUSE version error, version = %d", version);
        return ESP_ERR_INVALID_VERSION;
    }

    uint8_t efuse_crc;
    esp_efuse_read_field_blob(ESP_EFUSE_MAC_CUSTOM, mac, 48);
    esp_efuse_read_field_blob(ESP_EFUSE_MAC_CUSTOM_CRC, &efuse_crc, 8);
    uint8_t calc_crc = esp_crc8(mac, 6);

    if (efuse_crc != calc_crc) {
        ESP_LOGE(TAG, "Base MAC address from BLK3 of EFUSE CRC error, efuse_crc = 0x%02x; calc_crc = 0x%02x", efuse_crc, calc_crc);
        return ESP_ERR_INVALID_CRC;
    }
    return ESP_OK;
#endif // IDF_TARGET_ESP32S2BETA
}