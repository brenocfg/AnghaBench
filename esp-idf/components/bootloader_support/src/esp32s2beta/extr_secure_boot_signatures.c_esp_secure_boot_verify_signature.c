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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct ets_secure_boot_sig_block {int dummy; } ;
typedef  int /*<<< orphan*/  ets_secure_boot_signature_t ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ets_secure_boot_key_digests_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  bootloader_sha256_handle_t ;

/* Variables and functions */
 int DIGEST_LEN ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int ETS_OK ; 
 int /*<<< orphan*/  SHA2_256 ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * bootloader_mmap (int,int) ; 
 int /*<<< orphan*/  bootloader_munmap (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bootloader_sha256_data (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bootloader_sha256_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bootloader_sha256_start () ; 
 int /*<<< orphan*/  esp_sha (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int ets_secure_boot_read_key_digests (TYPE_1__*) ; 
 int ets_secure_boot_verify_signature (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_1__*) ; 

esp_err_t esp_secure_boot_verify_signature(uint32_t src_addr, uint32_t length)
{
    ets_secure_boot_key_digests_t trusted_keys = { 0 };
    uint8_t digest[DIGEST_LEN];
    const uint8_t *data;

    ESP_LOGD(TAG, "verifying signature src_addr 0x%x length 0x%x", src_addr, length);

    if ((src_addr + length) % 4096 != 0) {
        ESP_LOGE(TAG, "addr 0x%x length 0x%x doesn't end on a sector boundary", src_addr, length);
        return ESP_ERR_INVALID_ARG;
    }

    data = bootloader_mmap(src_addr, length + sizeof(struct ets_secure_boot_sig_block));
    if(data == NULL) {
        ESP_LOGE(TAG, "bootloader_mmap(0x%x, 0x%x) failed", src_addr, length+sizeof(ets_secure_boot_signature_t));
        return ESP_FAIL;
    }

    // Calculate digest of main image
#ifdef BOOTLOADER_BUILD
    bootloader_sha256_handle_t handle = bootloader_sha256_start();
    bootloader_sha256_data(handle, data, length);
    bootloader_sha256_finish(handle, digest);
#else
    /* Use thread-safe esp-idf SHA function */
    esp_sha(SHA2_256, data, length, digest);
#endif

    int r = ets_secure_boot_read_key_digests(&trusted_keys);

    if (r == ETS_OK) {
        const ets_secure_boot_signature_t *sig = (const ets_secure_boot_signature_t *)(data + length);
        // TODO: calling this function in IDF app context is unsafe
        r = ets_secure_boot_verify_signature(sig, digest, &trusted_keys);
    }
    bootloader_munmap(data);

    return (r == ETS_OK) ? ESP_OK : ESP_FAIL;
}