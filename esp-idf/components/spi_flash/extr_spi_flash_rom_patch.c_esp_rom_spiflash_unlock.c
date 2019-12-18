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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ esp_rom_spiflash_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ROM_SPIFLASH_QE ; 
 scalar_t__ ESP_ROM_SPIFLASH_RESULT_ERR ; 
 scalar_t__ ESP_ROM_SPIFLASH_RESULT_OK ; 
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CMD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CTRL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_FLASH_WREN ; 
 int /*<<< orphan*/  SPI_IDX ; 
 int /*<<< orphan*/  SPI_MEM_CMD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_CTRL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_FLASH_WREN ; 
 int /*<<< orphan*/  SPI_MEM_WRSR_2B ; 
 int /*<<< orphan*/  SPI_WRSR_2B ; 
 scalar_t__ esp_rom_spiflash_read_statushigh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_rom_spiflash_wait_idle (int /*<<< orphan*/ *) ; 
 scalar_t__ esp_rom_spiflash_write_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_rom_spiflash_chip ; 

esp_rom_spiflash_result_t esp_rom_spiflash_unlock(void)
{
    uint32_t status;

    esp_rom_spiflash_wait_idle(&g_rom_spiflash_chip);

    if (esp_rom_spiflash_read_statushigh(&g_rom_spiflash_chip, &status) != ESP_ROM_SPIFLASH_RESULT_OK) {
        return ESP_ROM_SPIFLASH_RESULT_ERR;
    }

    /* Clear all bits except QIE, if it is set.
     (This is different from ROM esp_rom_spiflash_unlock, which keeps all bits as-is.)
    */
    status &= ESP_ROM_SPIFLASH_QE;

    esp_rom_spiflash_wait_idle(&g_rom_spiflash_chip);
#if CONFIG_IDF_TARGET_ESP32
    REG_WRITE(SPI_CMD_REG(SPI_IDX), SPI_FLASH_WREN);
    while (REG_READ(SPI_CMD_REG(SPI_IDX)) != 0) {
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    REG_WRITE(SPI_MEM_CMD_REG(SPI_IDX), SPI_MEM_FLASH_WREN);
    while (REG_READ(SPI_MEM_CMD_REG(SPI_IDX)) != 0) {
    }
#endif
    esp_rom_spiflash_wait_idle(&g_rom_spiflash_chip);
#if CONFIG_IDF_TARGET_ESP32
    SET_PERI_REG_MASK(SPI_CTRL_REG(SPI_IDX), SPI_WRSR_2B);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    SET_PERI_REG_MASK(SPI_MEM_CTRL_REG(SPI_IDX), SPI_MEM_WRSR_2B);
#endif
    if (esp_rom_spiflash_write_status(&g_rom_spiflash_chip, status) != ESP_ROM_SPIFLASH_RESULT_OK) {
        return ESP_ROM_SPIFLASH_RESULT_ERR;
    }

    return ESP_ROM_SPIFLASH_RESULT_OK;
}