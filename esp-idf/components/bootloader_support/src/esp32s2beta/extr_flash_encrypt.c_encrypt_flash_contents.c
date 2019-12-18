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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_partition_info_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_PGM_DATA2_REG ; 
 int EFUSE_SPI_BOOT_CRYPT_CNT ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int ESP_PARTITION_TABLE_MAX_ENTRIES ; 
 int /*<<< orphan*/  ETS_EFUSE_BLOCK0 ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TAG ; 
 int __builtin_ffs (int) ; 
 scalar_t__ encrypt_and_load_partition_table (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ encrypt_bootloader () ; 
 scalar_t__ encrypt_partition (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ets_efuse_clear_program_registers () ; 
 int /*<<< orphan*/  ets_efuse_program (int /*<<< orphan*/ ) ; 
 scalar_t__ initialise_flash_encryption () ; 

__attribute__((used)) static esp_err_t encrypt_flash_contents(uint32_t spi_boot_crypt_cnt, bool flash_crypt_wr_dis)
{
    esp_err_t err;
    esp_partition_info_t partition_table[ESP_PARTITION_TABLE_MAX_ENTRIES];
    int num_partitions;

    /* If the last spi_boot_crypt_cnt bit is burned or write-disabled, the
       device can't re-encrypt itself. */
    if (flash_crypt_wr_dis || spi_boot_crypt_cnt == EFUSE_SPI_BOOT_CRYPT_CNT) {
        ESP_LOGE(TAG, "Cannot re-encrypt data (SPI_BOOT_CRYPT_CNT 0x%02x write disabled %d", spi_boot_crypt_cnt, flash_crypt_wr_dis);
        return ESP_FAIL;
    }

    if (spi_boot_crypt_cnt == 0) {
        /* Very first flash of encrypted data: generate keys, etc. */
        err = initialise_flash_encryption();
        if (err != ESP_OK) {
            return err;
        }
    }

    err = encrypt_bootloader();
    if (err != ESP_OK) {
        return err;
    }

    err = encrypt_and_load_partition_table(partition_table, &num_partitions);
    if (err != ESP_OK) {
        return err;
    }

    /* Now iterate the just-loaded partition table, looking for entries to encrypt
     */

    /* Go through each partition and encrypt if necessary */
    for (int i = 0; i < num_partitions; i++) {
        err = encrypt_partition(i, &partition_table[i]);
        if (err != ESP_OK) {
            return err;
        }
    }

    ESP_LOGD(TAG, "All flash regions checked for encryption pass");

    /* Set least significant 0-bit in spi_boot_crypt_cnt */
    int ffs_inv = __builtin_ffs((~spi_boot_crypt_cnt) & 0x7);
    /* ffs_inv shouldn't be zero, as zero implies spi_boot_crypt_cnt == 0xFF */
    uint32_t new_spi_boot_crypt_cnt = spi_boot_crypt_cnt + (1 << (ffs_inv - 1));
    ESP_LOGD(TAG, "SPI_BOOT_CRYPT_CNT 0x%x -> 0x%x", spi_boot_crypt_cnt, new_spi_boot_crypt_cnt);

    ets_efuse_clear_program_registers();
    REG_SET_FIELD(EFUSE_PGM_DATA2_REG, EFUSE_SPI_BOOT_CRYPT_CNT, new_spi_boot_crypt_cnt);
    ets_efuse_program(ETS_EFUSE_BLOCK0);

    ESP_LOGI(TAG, "Flash encryption completed");

    return ESP_OK;
}