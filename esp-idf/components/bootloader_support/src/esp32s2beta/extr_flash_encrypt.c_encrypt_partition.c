#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int flags; scalar_t__ type; scalar_t__ subtype; TYPE_2__ pos; } ;
typedef  TYPE_1__ esp_partition_info_t ;
typedef  int /*<<< orphan*/  esp_image_metadata_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_IMAGE_VERIFY ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int PART_FLAG_ENCRYPTED ; 
 scalar_t__ PART_SUBTYPE_DATA_OTA ; 
 scalar_t__ PART_TYPE_APP ; 
 scalar_t__ PART_TYPE_DATA ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_flash_encrypt_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_image_verify (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t encrypt_partition(int index, const esp_partition_info_t *partition)
{
    esp_err_t err;
    bool should_encrypt = (partition->flags & PART_FLAG_ENCRYPTED);

    if (partition->type == PART_TYPE_APP) {
      /* check if the partition holds a valid unencrypted app */
      esp_image_metadata_t data_ignored;
      err = esp_image_verify(ESP_IMAGE_VERIFY,
                           &partition->pos,
                           &data_ignored);
      should_encrypt = (err == ESP_OK);
    } else if (partition->type == PART_TYPE_DATA && partition->subtype == PART_SUBTYPE_DATA_OTA) {
        /* check if we have ota data partition and the partition should be encrypted unconditionally */
        should_encrypt = true;
    }

    if (!should_encrypt) {
        return ESP_OK;
    }
    else {
        /* should_encrypt */
        ESP_LOGI(TAG, "Encrypting partition %d at offset 0x%x (length 0x%x)...", index, partition->pos.offset, partition->pos.size);

        err = esp_flash_encrypt_region(partition->pos.offset, partition->pos.size);
        ESP_LOGI(TAG, "Done encrypting");
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to encrypt partition %d", index);
        }
        return err;
    }
}