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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ets_secure_boot_signature_t ;
typedef  int /*<<< orphan*/  ets_secure_boot_key_digests_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_IMAGE_INVALID ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * bootloader_mmap (int,int) ; 
 int /*<<< orphan*/  bootloader_munmap (int /*<<< orphan*/  const*) ; 
 int ets_secure_boot_read_key_digests (int /*<<< orphan*/ *) ; 
 int ets_secure_boot_verify_signature (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

esp_err_t esp_secure_boot_verify_signature_block(uint32_t sig_block_flash_offs, const uint8_t *image_digest)
{
    ets_secure_boot_key_digests_t trusted_keys;

    assert(sig_block_flash_offs % 4096 == 0); // TODO: enforce this in a better way

    const ets_secure_boot_signature_t *sig = bootloader_mmap(sig_block_flash_offs, sizeof(ets_secure_boot_signature_t));

    if (sig == NULL) {
        ESP_LOGE(TAG, "Failed to mmap data at offset 0x%x", sig_block_flash_offs);
        return ESP_FAIL;
    }

    int r = ets_secure_boot_read_key_digests(&trusted_keys);
    if (r != 0) {
        ESP_LOGE(TAG, "No trusted key digests were found in efuse!");
    } else {
        ESP_LOGD(TAG, "Verifying with RSA-PSS...");
        // TODO: calling this function in IDF app context is unsafe
        r = ets_secure_boot_verify_signature(sig, image_digest, &trusted_keys);
    }

    bootloader_munmap(sig);

    return (r == 0) ? ESP_OK : ESP_ERR_IMAGE_INVALID;
}