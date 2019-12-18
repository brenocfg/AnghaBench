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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  esp_secure_boot_sig_block_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  bootloader_sha256_handle_t ;

/* Variables and functions */
 int DIGEST_LEN ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ MMAP_ALIGNED_MASK ; 
 scalar_t__ SPI_FLASH_MMU_PAGE_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ bootloader_mmap (scalar_t__,int) ; 
 scalar_t__ bootloader_mmap_get_free_pages () ; 
 int /*<<< orphan*/  bootloader_munmap (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bootloader_sha256_data (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  bootloader_sha256_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bootloader_sha256_start () ; 
 int /*<<< orphan*/  esp_secure_boot_verify_signature_block (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

esp_err_t esp_secure_boot_verify_signature(uint32_t src_addr, uint32_t length)
{
    uint8_t digest[DIGEST_LEN];
    const uint8_t *data;
    const esp_secure_boot_sig_block_t *sigblock;

    ESP_LOGD(TAG, "verifying signature src_addr 0x%x length 0x%x", src_addr, length);

    bootloader_sha256_handle_t handle = bootloader_sha256_start();

    uint32_t free_page_count = bootloader_mmap_get_free_pages();
    ESP_LOGD(TAG, "free data page_count 0x%08x", free_page_count);

    int32_t data_len_remain = length;
    uint32_t data_addr = src_addr;
    while (data_len_remain > 0) {
        uint32_t offset_page = ((data_addr & MMAP_ALIGNED_MASK) != 0) ? 1 : 0;
        /* Data we could map in case we are not aligned to PAGE boundary is one page size lesser. */
        uint32_t data_len = MIN(data_len_remain, ((free_page_count - offset_page) * SPI_FLASH_MMU_PAGE_SIZE));
        data = (const uint8_t *) bootloader_mmap(data_addr, data_len);
        if(!data) {
            ESP_LOGE(TAG, "bootloader_mmap(0x%x, 0x%x) failed", data_addr, data_len);
            bootloader_sha256_finish(handle, NULL);
            return ESP_FAIL;
        }
        bootloader_sha256_data(handle, data, data_len);
        bootloader_munmap(data);

        data_addr += data_len;
        data_len_remain -= data_len;
    }

    /* Done! Get the digest */
    bootloader_sha256_finish(handle, digest);

    // Map the signature block
    sigblock = (const esp_secure_boot_sig_block_t *) bootloader_mmap(src_addr + length, sizeof(esp_secure_boot_sig_block_t));
    if(!sigblock) {
        ESP_LOGE(TAG, "bootloader_mmap(0x%x, 0x%x) failed", src_addr + length, sizeof(esp_secure_boot_sig_block_t));
        return ESP_FAIL;
    }
    // Verify the signature
    esp_err_t err = esp_secure_boot_verify_signature_block(sigblock, digest);
    // Unmap
    bootloader_munmap(sigblock);

    return err;
}