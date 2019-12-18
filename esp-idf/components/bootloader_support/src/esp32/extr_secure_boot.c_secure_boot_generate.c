#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ digest; scalar_t__ iv; } ;
typedef  TYPE_1__ esp_secure_boot_iv_digest_t ;
typedef  int esp_err_t ;
typedef  int /*<<< orphan*/  digest ;

/* Variables and functions */
 int /*<<< orphan*/  Cache_Read_Enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BOOTLOADER_OFFSET ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  FLASH_OFFS_SECURE_BOOT_IV_DIGEST ; 
 int /*<<< orphan*/  TAG ; 
 int bootloader_flash_erase_sector (int /*<<< orphan*/ ) ; 
 int bootloader_flash_write (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int* bootloader_mmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bootloader_munmap (int const*) ; 
 int /*<<< orphan*/  esp_flash_encryption_enabled () ; 
 int /*<<< orphan*/  ets_secure_boot_finish () ; 
 int /*<<< orphan*/  ets_secure_boot_hash (int const*) ; 
 int /*<<< orphan*/  ets_secure_boot_obtain () ; 
 int /*<<< orphan*/  ets_secure_boot_rd_abstract (int*) ; 
 int /*<<< orphan*/  ets_secure_boot_rd_iv (int*) ; 
 int /*<<< orphan*/  ets_secure_boot_start () ; 

__attribute__((used)) static bool secure_boot_generate(uint32_t image_len){
    esp_err_t err;
    esp_secure_boot_iv_digest_t digest;
    const uint32_t *image;

    /* hardware secure boot engine only takes full blocks, so round up the
       image length. The additional data should all be 0xFF (or the appended SHA, if it falls in the same block).
    */
    if (image_len % sizeof(digest.iv) != 0) {
        image_len = (image_len / sizeof(digest.iv) + 1) * sizeof(digest.iv);
    }
    ets_secure_boot_start();
    ets_secure_boot_rd_iv((uint32_t *)digest.iv);
    ets_secure_boot_hash(NULL);
    /* iv stored in sec 0 */
    err = bootloader_flash_erase_sector(0);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "SPI erase failed: 0x%x", err);
        return false;
    }

    /* generate digest from image contents */
    image = bootloader_mmap(ESP_BOOTLOADER_OFFSET, image_len);
    if (!image) {
        ESP_LOGE(TAG, "bootloader_mmap(0x1000, 0x%x) failed", image_len);
        return false;
    }
    for (int i = 0; i < image_len; i+= sizeof(digest.iv)) {
        ets_secure_boot_hash(&image[i/sizeof(uint32_t)]);
    }
    bootloader_munmap(image);

    ets_secure_boot_obtain();
    ets_secure_boot_rd_abstract((uint32_t *)digest.digest);
    ets_secure_boot_finish();

    ESP_LOGD(TAG, "write iv+digest to flash");
    err = bootloader_flash_write(FLASH_OFFS_SECURE_BOOT_IV_DIGEST, &digest,
                           sizeof(digest), esp_flash_encryption_enabled());
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "SPI write failed: 0x%x", err);
        return false;
    }
    Cache_Read_Enable(0);
    return true;
}