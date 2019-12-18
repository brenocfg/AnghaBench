#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; scalar_t__ subtype; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_10__ {int /*<<< orphan*/  secure_version; } ;
typedef  TYPE_2__ esp_app_desc_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_NOT_FOUND ; 
 scalar_t__ ESP_ERR_OTA_SMALL_SEC_VER ; 
 scalar_t__ ESP_ERR_OTA_VALIDATE_FAILED ; 
 int /*<<< orphan*/  ESP_IMAGE_VERIFY ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ ESP_PARTITION_SUBTYPE_APP_FACTORY ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_DATA_OTA ; 
 scalar_t__ ESP_PARTITION_TYPE_APP ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_DATA ; 
 int /*<<< orphan*/  TAG ; 
 int esp_efuse_check_secure_version (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_ota_get_partition_description (TYPE_1__ const*,TYPE_2__*) ; 
 scalar_t__ esp_partition_erase_range (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* esp_partition_find_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_rewrite_ota_data (scalar_t__) ; 
 scalar_t__ image_validate (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

esp_err_t esp_ota_set_boot_partition(const esp_partition_t *partition)
{
    if (partition == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (image_validate(partition, ESP_IMAGE_VERIFY) != ESP_OK) {
        return ESP_ERR_OTA_VALIDATE_FAILED;
    }

    // if set boot partition to factory bin ,just format ota info partition
    if (partition->type == ESP_PARTITION_TYPE_APP) {
        if (partition->subtype == ESP_PARTITION_SUBTYPE_APP_FACTORY) {
            const esp_partition_t *find_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_OTA, NULL);
            if (find_partition != NULL) {
                return esp_partition_erase_range(find_partition, 0, find_partition->size);
            } else {
                return ESP_ERR_NOT_FOUND;
            }
        } else {
#ifdef CONFIG_BOOTLOADER_APP_ANTI_ROLLBACK
            esp_app_desc_t partition_app_desc;
            esp_err_t err = esp_ota_get_partition_description(partition, &partition_app_desc);
            if (err != ESP_OK) {
                return err;
            }

            if (esp_efuse_check_secure_version(partition_app_desc.secure_version) == false) {
                ESP_LOGE(TAG, "This a new partition can not be booted due to a secure version is lower than stored in efuse. Partition will be erased.");
                esp_err_t err = esp_partition_erase_range(partition, 0, partition->size);
                if (err != ESP_OK) {
                    return err;
                }
                return ESP_ERR_OTA_SMALL_SEC_VER;
            }
#endif
            return esp_rewrite_ota_data(partition->subtype);
        }
    } else {
        return ESP_ERR_INVALID_ARG;
    }
}