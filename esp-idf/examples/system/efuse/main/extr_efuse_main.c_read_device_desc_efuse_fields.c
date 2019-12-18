#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  custom_secure_version; int /*<<< orphan*/  setting_2; int /*<<< orphan*/  setting_1; int /*<<< orphan*/  device_role; int /*<<< orphan*/  module_version; } ;
typedef  TYPE_1__ device_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EFUSE_CUSTOM_SECURE_VERSION ; 
 int /*<<< orphan*/  ESP_EFUSE_DEVICE_ROLE ; 
 int /*<<< orphan*/  ESP_EFUSE_MODULE_VERSION ; 
 int /*<<< orphan*/  ESP_EFUSE_SETTING_1 ; 
 int /*<<< orphan*/  ESP_EFUSE_SETTING_2 ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  esp_efuse_read_field_cnt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_device_desc (TYPE_1__*) ; 

__attribute__((used)) static void read_device_desc_efuse_fields(device_desc_t *desc)
{
    ESP_ERROR_CHECK(esp_efuse_read_field_blob(ESP_EFUSE_MODULE_VERSION, &desc->module_version, 8));
    ESP_ERROR_CHECK(esp_efuse_read_field_blob(ESP_EFUSE_DEVICE_ROLE, &desc->device_role, 3));
    ESP_ERROR_CHECK(esp_efuse_read_field_blob(ESP_EFUSE_SETTING_1, &desc->setting_1, 6));
    ESP_ERROR_CHECK(esp_efuse_read_field_blob(ESP_EFUSE_SETTING_2, &desc->setting_2, 5));
    ESP_ERROR_CHECK(esp_efuse_read_field_cnt(ESP_EFUSE_CUSTOM_SECURE_VERSION, &desc->custom_secure_version));
    print_device_desc(desc);
}