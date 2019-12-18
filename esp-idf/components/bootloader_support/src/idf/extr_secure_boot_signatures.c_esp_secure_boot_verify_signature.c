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
typedef  int /*<<< orphan*/  esp_secure_boot_sig_block_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int DIGEST_LEN ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * bootloader_mmap (int,int) ; 
 int /*<<< orphan*/  bootloader_munmap (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  esp_secure_boot_verify_signature_block (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_ret (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

esp_err_t esp_secure_boot_verify_signature(uint32_t src_addr, uint32_t length)
{
    uint8_t digest[DIGEST_LEN];
    const uint8_t *data;
    const esp_secure_boot_sig_block_t *sigblock;

    ESP_LOGD(TAG, "verifying signature src_addr 0x%x length 0x%x", src_addr, length);

    data = bootloader_mmap(src_addr, length + sizeof(esp_secure_boot_sig_block_t));
    if (data == NULL) {
        ESP_LOGE(TAG, "bootloader_mmap(0x%x, 0x%x) failed", src_addr, length + sizeof(esp_secure_boot_sig_block_t));
        return ESP_FAIL;
    }

    // Calculate digest of main image
    mbedtls_sha256_ret(data, length, digest, 0);

    // Map the signature block and verify the signature
    sigblock = (const esp_secure_boot_sig_block_t *)(data + length);
    esp_err_t err = esp_secure_boot_verify_signature_block(sigblock, digest);
    bootloader_munmap(data);
    return err;
}