#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ esp_partition_pos_t ;
struct TYPE_6__ {scalar_t__ hash_appended; } ;
struct TYPE_8__ {int /*<<< orphan*/  image_len; int /*<<< orphan*/  image_digest; TYPE_1__ image; } ;
typedef  TYPE_3__ esp_image_metadata_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/ * bootloader_sha256_handle_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_IMAGE_INVALID ; 
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_IMAGE_VERIFY_SILENT ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ESP_PARTITION_HASH_LEN ; 
 int PART_TYPE_APP ; 
 int /*<<< orphan*/  TAG ; 
 void* bootloader_mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootloader_munmap (void const*) ; 
 int /*<<< orphan*/  bootloader_sha256_data (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootloader_sha256_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bootloader_sha256_start () ; 
 scalar_t__ esp_image_verify (int /*<<< orphan*/ ,TYPE_2__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t bootloader_common_get_sha256_of_partition (uint32_t address, uint32_t size, int type, uint8_t *out_sha_256)
{
    if (out_sha_256 == NULL || size == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    if (type == PART_TYPE_APP) {
        const esp_partition_pos_t partition_pos = {
            .offset = address,
            .size = size,
        };
        esp_image_metadata_t data;
        // Function esp_image_verify() verifies and fills the structure data.
        // here important to get: image_digest, image_len, hash_appended.
        if (esp_image_verify(ESP_IMAGE_VERIFY_SILENT, &partition_pos, &data) != ESP_OK) {
            return ESP_ERR_IMAGE_INVALID;
        }
        if (data.image.hash_appended) {
            memcpy(out_sha_256, data.image_digest, ESP_PARTITION_HASH_LEN);
            return ESP_OK;
        }
        // If image doesn't have a appended hash then hash calculates for entire image.
        size = data.image_len;
    }
    // If image is type by data then hash is calculated for entire image.
    const void *partition_bin = bootloader_mmap(address, size);
    if (partition_bin == NULL) {
        ESP_LOGE(TAG, "bootloader_mmap(0x%x, 0x%x) failed", address, size);
        return ESP_FAIL;
    }
    bootloader_sha256_handle_t sha_handle = bootloader_sha256_start();
    if (sha_handle == NULL) {
        bootloader_munmap(partition_bin);
        return ESP_ERR_NO_MEM;
    }
    bootloader_sha256_data(sha_handle, partition_bin, size);
    bootloader_sha256_finish(sha_handle, out_sha_256);

    bootloader_munmap(partition_bin);

    return ESP_OK;
}