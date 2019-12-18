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
typedef  int uint32_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EFUSE_MAC_FACTORY ; 
 int /*<<< orphan*/  ESP_EFUSE_MAC_FACTORY_CRC ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ esp_crc8 (scalar_t__*,int) ; 
 scalar_t__ esp_efuse_read_field_blob (int /*<<< orphan*/ ,scalar_t__*,int) ; 

esp_err_t esp_efuse_mac_get_default(uint8_t* mac)
{
    esp_err_t err = esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY, mac, 48);
    if (err != ESP_OK) {
        return err;
    }
#ifdef CONFIG_IDF_TARGET_ESP32
// Only ESP32 has MAC CRC in efuse, ESP32-S2 has internal efuse consistency checks
    uint8_t efuse_crc;
    esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY_CRC, &efuse_crc, 8);
    uint8_t calc_crc = esp_crc8(mac, 6);

    if (efuse_crc != calc_crc) {
         // Small range of MAC addresses are accepted even if CRC is invalid.
         // These addresses are reserved for Espressif internal use.
        uint32_t mac_high = ((uint32_t)mac[0] << 8) | mac[1];
        if ((mac_high & 0xFFFF) == 0x18fe) {
            uint32_t mac_low = ((uint32_t)mac[2] << 24) | ((uint32_t)mac[3] << 16) | ((uint32_t)mac[4] << 8) | mac[5];
            if ((mac_low >= 0x346a85c7) && (mac_low <= 0x346a85f8)) {
                return ESP_OK;
            }
        } else {
            ESP_LOGE(TAG, "Base MAC address from BLK0 of EFUSE CRC error, efuse_crc = 0x%02x; calc_crc = 0x%02x", efuse_crc, calc_crc);
            abort();
        }
    }
#endif // CONFIG_IDF_TARGET_ESP32
    return ESP_OK;
}