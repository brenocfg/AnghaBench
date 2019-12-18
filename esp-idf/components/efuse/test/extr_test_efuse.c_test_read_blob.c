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
typedef  int* uint32_t ;
typedef  int /*<<< orphan*/  mac ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EFUSE_MAC_FACTORY ; 
 int /*<<< orphan*/  ESP_EFUSE_MAC_FACTORY_CRC ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX8 (int,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_INT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE_MESSAGE (int,char*) ; 
 int /*<<< orphan*/  TEST_ESP_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int esp_crc8 (int*,int) ; 
 int /*<<< orphan*/  esp_efuse_get_field_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  esp_efuse_utility_debug_dump_blocks () ; 
 int /*<<< orphan*/  esp_efuse_utility_update_virt_blocks () ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_read_blob(void)
{
    esp_efuse_utility_update_virt_blocks();
    esp_efuse_utility_debug_dump_blocks();

    uint8_t mac[6];

    ESP_LOGI(TAG, "1. Read MAC address");
    memset(mac, 0, sizeof(mac));
    TEST_ESP_OK(esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY, &mac, sizeof(mac) * 8));
    TEST_ASSERT_EQUAL_INT(sizeof(mac) * 8, esp_efuse_get_field_size(ESP_EFUSE_MAC_FACTORY));
    ESP_LOGI(TAG, "MAC: %02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

#if CONFIG_IDF_TARGET_ESP32
    ESP_LOGI(TAG, "2. Check CRC by MAC");
    uint8_t crc;
    TEST_ESP_OK(esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY_CRC, &crc, 8));
    TEST_ASSERT_EQUAL_HEX8(crc, esp_crc8(mac, sizeof(mac)));
#endif // CONFIG_IDF_TARGET_ESP32

    ESP_LOGI(TAG, "3. Test check args");
    uint32_t test_var;
    TEST_ESP_ERR(ESP_ERR_INVALID_ARG, esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY, NULL, 1));
    TEST_ESP_ERR(ESP_ERR_INVALID_ARG, esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY, &test_var, 0));

    uint8_t half_byte;
    TEST_ESP_OK(esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY, &half_byte, 4));
    TEST_ASSERT_EQUAL_HEX8(mac[0]&0x0F, half_byte);

    uint8_t buff[7] = {0x59};
    TEST_ESP_OK(esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY, &buff, sizeof(buff) * 8));
    TEST_ASSERT_TRUE_MESSAGE(memcmp(mac, buff, sizeof(mac)) == 0, "Operation read blob is not success");
    TEST_ASSERT_EQUAL_HEX8(0, buff[6]);
}