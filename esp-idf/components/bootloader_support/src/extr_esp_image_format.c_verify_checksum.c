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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ hash_appended; } ;
struct TYPE_5__ {int image_len; TYPE_1__ image; scalar_t__ start_addr; } ;
typedef  TYPE_2__ esp_image_metadata_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/ * bootloader_sha256_handle_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_IMAGE_INVALID ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ HASH_LEN ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ bootloader_flash_read (scalar_t__,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  bootloader_sha256_data (int /*<<< orphan*/ *,scalar_t__*,int) ; 

__attribute__((used)) static esp_err_t verify_checksum(bootloader_sha256_handle_t sha_handle, uint32_t checksum_word, esp_image_metadata_t *data)
{
    uint32_t unpadded_length = data->image_len;
    uint32_t length = unpadded_length + 1; // Add a byte for the checksum
    length = (length + 15) & ~15; // Pad to next full 16 byte block

    // Verify checksum
    uint8_t buf[16];
    esp_err_t err = bootloader_flash_read(data->start_addr + unpadded_length, buf, length - unpadded_length, true);
    uint8_t calc = buf[length - unpadded_length - 1];
    uint8_t checksum = (checksum_word >> 24)
                       ^ (checksum_word >> 16)
                       ^ (checksum_word >> 8)
                       ^ (checksum_word >> 0);
    if (err != ESP_OK || checksum != calc) {
        ESP_LOGE(TAG, "Checksum failed. Calculated 0x%x read 0x%x", checksum, calc);
        return ESP_ERR_IMAGE_INVALID;
    }
    if (sha_handle != NULL) {
        bootloader_sha256_data(sha_handle, buf, length - unpadded_length);
    }

    if (data->image.hash_appended) {
        // Account for the hash in the total image length
        length += HASH_LEN;
    }
    data->image_len = length;

    return ESP_OK;
}