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
typedef  int /*<<< orphan*/  esp_rom_spiflash_chip_t ;

/* Variables and functions */
 scalar_t__ ESP_ROM_SPIFLASH_RESULT_ERR ; 
 scalar_t__ ESP_ROM_SPIFLASH_RESULT_OK ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_EXT2_REG (int) ; 
 int /*<<< orphan*/  SPI_MEM_FSM_REG (int) ; 
 int SPI_MEM_ST ; 
 int SPI_ST ; 
 scalar_t__ esp_rom_spiflash_read_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

esp_rom_spiflash_result_t esp_rom_spiflash_wait_idle(esp_rom_spiflash_chip_t *spi)
{
    uint32_t status;
#if CONFIG_IDF_TARGET_ESP32
    //wait for spi control ready
    while ((REG_READ(SPI_EXT2_REG(1)) & SPI_ST)) {
    }
    while ((REG_READ(SPI_EXT2_REG(0)) & SPI_ST)) {
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    while ((REG_READ(SPI_MEM_FSM_REG(1)) & SPI_MEM_ST)) {
    }
    while ((REG_READ(SPI_MEM_FSM_REG(0)) & SPI_MEM_ST)) {
    }
#endif
    //wait for flash status ready
    if ( ESP_ROM_SPIFLASH_RESULT_OK != esp_rom_spiflash_read_status(spi, &status)) {
        return ESP_ROM_SPIFLASH_RESULT_ERR;
    }
    return  ESP_ROM_SPIFLASH_RESULT_OK;
}