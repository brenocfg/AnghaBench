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
typedef  int /*<<< orphan*/  esp_partition_t ;
struct TYPE_4__ {int ota_seq; } ;
typedef  TYPE_1__ esp_ota_select_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_IMAGE_VERIFY_SILENT ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ ESP_PARTITION_SUBTYPE_APP_OTA_MIN ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_APP ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * esp_partition_find_first (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int get_last_invalid_otadata (TYPE_1__*) ; 
 int get_ota_partition_count () ; 
 scalar_t__ image_validate (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_otadata (TYPE_1__*) ; 

const esp_partition_t* esp_ota_get_last_invalid_partition(void)
{
    esp_ota_select_entry_t otadata[2];
    if (read_otadata(otadata) == NULL) {
        return NULL;
    }

    int invalid_otadata = get_last_invalid_otadata(otadata);

    int ota_app_count = get_ota_partition_count();
    if (invalid_otadata != -1 && ota_app_count != 0) {
        int ota_slot = (otadata[invalid_otadata].ota_seq - 1) % ota_app_count;
        ESP_LOGD(TAG, "Find invalid ota_%d app", ESP_PARTITION_SUBTYPE_APP_OTA_MIN + ota_slot);

        const esp_partition_t* invalid_partition = esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_MIN + ota_slot, NULL);
        if (invalid_partition != NULL) {
            if (image_validate(invalid_partition, ESP_IMAGE_VERIFY_SILENT) != ESP_OK) {
                ESP_LOGD(TAG, "Last invalid partition has corrupted app");
                return NULL;
            }
        }
        return invalid_partition;
    }
    return NULL;
}