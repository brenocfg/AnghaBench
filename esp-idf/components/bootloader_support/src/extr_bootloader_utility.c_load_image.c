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
typedef  int /*<<< orphan*/  esp_image_metadata_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bootloader_random_disable () ; 
 int /*<<< orphan*/  bootloader_reset () ; 
 scalar_t__ esp_flash_encrypt_check_and_update () ; 
 int esp_flash_encryption_enabled () ; 
 scalar_t__ esp_secure_boot_generate_digest () ; 
 scalar_t__ esp_secure_boot_permanently_enable () ; 
 int /*<<< orphan*/  uart_tx_wait_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_load_app (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void load_image(const esp_image_metadata_t *image_data)
{
    /**
     * Rough steps for a first boot, when encryption and secure boot are both disabled:
     *   1) Generate secure boot key and write to EFUSE.
     *   2) Write plaintext digest based on plaintext bootloader
     *   3) Generate flash encryption key and write to EFUSE.
     *   4) Encrypt flash in-place including bootloader, then digest,
     *      then app partitions and other encrypted partitions
     *   5) Burn EFUSE to enable flash encryption (FLASH_CRYPT_CNT)
     *   6) Burn EFUSE to enable secure boot (ABS_DONE_0)
     *
     * If power failure happens during Step 1, probably the next boot will continue from Step 2.
     * There is some small chance that EFUSEs will be part-way through being written so will be
     * somehow corrupted here. Thankfully this window of time is very small, but if that's the
     * case, one has to use the espefuse tool to manually set the remaining bits and enable R/W
     * protection. Once the relevant EFUSE bits are set and R/W protected, Step 1 will be skipped
     * successfully on further reboots.
     *
     * If power failure happens during Step 2, Step 1 will be skipped and Step 2 repeated:
     * the digest will get re-written on the next boot.
     *
     * If power failure happens during Step 3, it's possible that EFUSE was partially written
     * with the generated flash encryption key, though the time window for that would again
     * be very small. On reboot, Step 1 will be skipped and Step 2 repeated, though, Step 3
     * may fail due to the above mentioned reason, in which case, one has to use the espefuse
     * tool to manually set the remaining bits and enable R/W protection. Once the relevant EFUSE
     * bits are set and R/W protected, Step 3 will be skipped successfully on further reboots.
     *
     * If power failure happens after start of 4 and before end of 5, the next boot will fail
     * (bootloader header is encrypted and flash encryption isn't enabled yet, so it looks like
     * noise to the ROM bootloader). The check in the ROM is pretty basic so if the first byte of
     * ciphertext happens to be the magic byte E9 then it may try to boot, but it will definitely
     * crash (no chance that the remaining ciphertext will look like a valid bootloader image).
     * Only solution is to reflash with all plaintext and the whole process starts again: skips
     * Step 1, repeats Step 2, skips Step 3, etc.
     *
     * If power failure happens after 5 but before 6, the device will reboot with flash
     * encryption on and will regenerate an encrypted digest in Step 2. This should still
     * be valid as the input data for the digest is read via flash cache (so will be decrypted)
     * and the code in secure_boot_generate() tells bootloader_flash_write() to encrypt the data
     * on write if flash encryption is enabled. Steps 3 - 5 are skipped (encryption already on),
     * then Step 6 enables secure boot.
     */

#if defined(CONFIG_SECURE_BOOT_ENABLED) || defined(CONFIG_SECURE_FLASH_ENC_ENABLED)
    esp_err_t err;
#endif

#ifdef CONFIG_SECURE_BOOT_ENABLED
    /* Steps 1 & 2 (see above for full description):
     *   1) Generate secure boot EFUSE key
     *   2) Compute digest of plaintext bootloader
     */
    err = esp_secure_boot_generate_digest();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Bootloader digest generation for secure boot failed (%d).", err);
        return;
    }
#endif

#ifdef CONFIG_SECURE_FLASH_ENC_ENABLED
    /* Steps 3, 4 & 5 (see above for full description):
     *   3) Generate flash encryption EFUSE key
     *   4) Encrypt flash contents
     *   5) Burn EFUSE to enable flash encryption
     */
    ESP_LOGI(TAG, "Checking flash encryption...");
    bool flash_encryption_enabled = esp_flash_encryption_enabled();
    err = esp_flash_encrypt_check_and_update();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Flash encryption check failed (%d).", err);
        return;
    }
#endif

#ifdef CONFIG_SECURE_BOOT_ENABLED
    /* Step 6 (see above for full description):
     *   6) Burn EFUSE to enable secure boot
     */
    ESP_LOGI(TAG, "Checking secure boot...");
    err = esp_secure_boot_permanently_enable();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "FAILED TO ENABLE SECURE BOOT (%d).", err);
        /* Panic here as secure boot is not properly enabled
           due to one of the reasons in above function
        */
        abort();
    }
#endif

#ifdef CONFIG_SECURE_FLASH_ENC_ENABLED
    if (!flash_encryption_enabled && esp_flash_encryption_enabled()) {
        /* Flash encryption was just enabled for the first time,
           so issue a system reset to ensure flash encryption
           cache resets properly */
        ESP_LOGI(TAG, "Resetting with flash encryption enabled...");
        uart_tx_wait_idle(0);
        bootloader_reset();
    }
#endif

    ESP_LOGI(TAG, "Disabling RNG early entropy source...");
    bootloader_random_disable();

    // copy loaded segments to RAM, set up caches for mapped segments, and start application
    unpack_load_app(image_data);
}