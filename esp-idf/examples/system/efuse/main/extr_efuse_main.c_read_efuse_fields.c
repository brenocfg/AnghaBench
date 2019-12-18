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
typedef  int /*<<< orphan*/  mac ;
typedef  int /*<<< orphan*/  device_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EFUSE_MAC_FACTORY ; 
 int /*<<< orphan*/  ESP_EFUSE_SECURE_VERSION ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  esp_efuse_read_field_cnt (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  read_device_desc_efuse_fields (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_efuse_fields(device_desc_t *desc)
{
    ESP_LOGI(TAG, "read efuse fields");

    uint8_t mac[6];
    ESP_ERROR_CHECK(esp_efuse_read_field_blob(ESP_EFUSE_MAC_FACTORY, &mac, sizeof(mac) * 8));
    ESP_LOGI(TAG, "1. read MAC address: %02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    size_t secure_version = 0;
    ESP_ERROR_CHECK(esp_efuse_read_field_cnt(ESP_EFUSE_SECURE_VERSION, &secure_version));
    ESP_LOGI(TAG, "2. read secure_version: %d", secure_version);

    ESP_LOGI(TAG, "3. read custom fields");
    read_device_desc_efuse_fields(desc);   
}