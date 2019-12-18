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
struct TYPE_5__ {int ota_seq; } ;
typedef  TYPE_1__ esp_ota_select_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int ESP_PARTITION_SUBTYPE_APP_OTA_MIN ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_APP ; 
 int /*<<< orphan*/  TAG ; 
 int bootloader_common_get_active_otadata (TYPE_1__*) ; 
 scalar_t__ bootloader_common_ota_select_invalid (TYPE_1__*) ; 
 int /*<<< orphan*/  const* esp_partition_find_first (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* find_default_boot_partition () ; 
 int get_ota_partition_count () ; 
 int /*<<< orphan*/ * read_otadata (TYPE_1__*) ; 

const esp_partition_t *esp_ota_get_boot_partition(void)
{
    esp_ota_select_entry_t otadata[2];
    const esp_partition_t *otadata_partition = read_otadata(otadata);
    if (otadata_partition == NULL) {
        return NULL;
    }

    int ota_app_count = get_ota_partition_count();
    ESP_LOGD(TAG, "found ota app max = %d", ota_app_count);

    if ((bootloader_common_ota_select_invalid(&otadata[0]) &&
         bootloader_common_ota_select_invalid(&otadata[1])) ||
         ota_app_count == 0) {
        ESP_LOGD(TAG, "finding factory app...");
        return find_default_boot_partition();
    } else {
        int active_otadata = bootloader_common_get_active_otadata(otadata);
        if (active_otadata != -1) {
            int ota_slot = (otadata[active_otadata].ota_seq - 1) % ota_app_count; // Actual OTA partition selection
            ESP_LOGD(TAG, "finding ota_%d app...", ESP_PARTITION_SUBTYPE_APP_OTA_MIN + ota_slot);
            return esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_MIN + ota_slot, NULL);
        } else {
            ESP_LOGE(TAG, "ota data invalid, no current app. Assuming factory");
            return find_default_boot_partition();
        }
    }
}