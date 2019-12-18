#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const esp_efuse_coding_scheme_t ;
struct TYPE_3__ {int /*<<< orphan*/  custom_secure_version; int /*<<< orphan*/  setting_2; int /*<<< orphan*/  setting_1; int /*<<< orphan*/  device_role; int /*<<< orphan*/  module_version; } ;
typedef  TYPE_1__ device_desc_t ;

/* Variables and functions */
 scalar_t__ EFUSE_CODING_SCHEME_3_4 ; 
 scalar_t__ EFUSE_CODING_SCHEME_RS ; 
 int /*<<< orphan*/  ESP_EFUSE_CUSTOM_SECURE_VERSION ; 
 int /*<<< orphan*/  ESP_EFUSE_DEVICE_ROLE ; 
 int /*<<< orphan*/  ESP_EFUSE_MODULE_VERSION ; 
 int /*<<< orphan*/  ESP_EFUSE_SETTING_1 ; 
 int /*<<< orphan*/  ESP_EFUSE_SETTING_2 ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_efuse_batch_write_begin () ; 
 int /*<<< orphan*/  esp_efuse_batch_write_commit () ; 
 int /*<<< orphan*/  esp_efuse_write_field_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  esp_efuse_write_field_cnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_efuse_fields(device_desc_t *desc, esp_efuse_coding_scheme_t coding_scheme)
{
#ifdef CONFIG_EFUSE_VIRTUAL

#if CONFIG_IDF_TARGET_ESP32
    const esp_efuse_coding_scheme_t coding_scheme_for_batch_mode = EFUSE_CODING_SCHEME_3_4;
#else
    const esp_efuse_coding_scheme_t coding_scheme_for_batch_mode = EFUSE_CODING_SCHEME_RS;
#endif

    ESP_LOGI(TAG, "write custom efuse fields");
    if (coding_scheme == coding_scheme_for_batch_mode) {
        ESP_LOGI(TAG, "In the case of 3/4 or RS coding scheme, you cannot write efuse fields separately");
        ESP_LOGI(TAG, "You should use the batch mode of writing fields for this");
        ESP_ERROR_CHECK(esp_efuse_batch_write_begin());
    }

    ESP_ERROR_CHECK(esp_efuse_write_field_blob(ESP_EFUSE_MODULE_VERSION, &desc->module_version, 8));
    ESP_ERROR_CHECK(esp_efuse_write_field_blob(ESP_EFUSE_DEVICE_ROLE, &desc->device_role, 3));
    ESP_ERROR_CHECK(esp_efuse_write_field_blob(ESP_EFUSE_SETTING_1, &desc->setting_1, 6));
    ESP_ERROR_CHECK(esp_efuse_write_field_blob(ESP_EFUSE_SETTING_2, &desc->setting_2, 5));
    ESP_ERROR_CHECK(esp_efuse_write_field_cnt(ESP_EFUSE_CUSTOM_SECURE_VERSION, desc->custom_secure_version));

    if (coding_scheme == coding_scheme_for_batch_mode) {
        ESP_ERROR_CHECK(esp_efuse_batch_write_commit());
    }
#endif // CONFIG_EFUSE_VIRTUAL
}