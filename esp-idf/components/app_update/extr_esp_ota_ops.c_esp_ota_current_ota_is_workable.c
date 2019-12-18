#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_partition_t ;
struct TYPE_5__ {scalar_t__ ota_state; int /*<<< orphan*/  ota_seq; } ;
typedef  TYPE_1__ esp_ota_select_entry_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NOT_FOUND ; 
 scalar_t__ ESP_ERR_OTA_ROLLBACK_FAILED ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ ESP_OTA_IMG_INVALID ; 
 scalar_t__ ESP_OTA_IMG_VALID ; 
 int /*<<< orphan*/  TAG ; 
 int bootloader_common_get_active_otadata (TYPE_1__*) ; 
 int esp_ota_check_rollback_is_possible () ; 
 scalar_t__ esp_ota_set_anti_rollback () ; 
 int /*<<< orphan*/  esp_restart () ; 
 scalar_t__ get_ota_partition_count () ; 
 int /*<<< orphan*/ * read_otadata (TYPE_1__*) ; 
 scalar_t__ rewrite_ota_seq (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static esp_err_t esp_ota_current_ota_is_workable(bool valid)
{
    esp_ota_select_entry_t otadata[2];
    const esp_partition_t *otadata_partition = read_otadata(otadata);
    if (otadata_partition == NULL) {
        return ESP_ERR_NOT_FOUND;
    }

    int active_otadata = bootloader_common_get_active_otadata(otadata);
    if (active_otadata != -1 && get_ota_partition_count() != 0) {
        if (valid == true && otadata[active_otadata].ota_state != ESP_OTA_IMG_VALID) {
            otadata[active_otadata].ota_state = ESP_OTA_IMG_VALID;
            ESP_LOGD(TAG, "OTA[current] partition is marked as VALID");
            esp_err_t err = rewrite_ota_seq(otadata, otadata[active_otadata].ota_seq, active_otadata, otadata_partition);
#ifdef CONFIG_BOOTLOADER_APP_ANTI_ROLLBACK
            if (err == ESP_OK) {
                return esp_ota_set_anti_rollback();
            }
#endif
            return err;
        } else if (valid == false) {
            if (esp_ota_check_rollback_is_possible() == false) {
                ESP_LOGE(TAG, "Rollback is not possible, do not have any suitable apps in slots");
                return ESP_ERR_OTA_ROLLBACK_FAILED;
            }
            ESP_LOGD(TAG, "OTA[current] partition is marked as INVALID");
            otadata[active_otadata].ota_state = ESP_OTA_IMG_INVALID;
            esp_err_t err = rewrite_ota_seq(otadata, otadata[active_otadata].ota_seq, active_otadata, otadata_partition);
            if (err != ESP_OK) {
                return err;
            }
            ESP_LOGI(TAG, "Rollback to previously worked partition. Restart.");
            esp_restart();
        }
    } else {
        ESP_LOGE(TAG, "Running firmware is factory");
        return ESP_FAIL;
    }
    return ESP_OK;
}