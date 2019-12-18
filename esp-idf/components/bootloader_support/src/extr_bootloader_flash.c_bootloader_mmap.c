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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SPI_FLASH_MMAP_DATA ; 
 int SPI_FLASH_MMU_PAGE_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ map ; 
 scalar_t__ spi_flash_mmap (int,int,int /*<<< orphan*/ ,void const**,scalar_t__*) ; 

const void *bootloader_mmap(uint32_t src_addr, uint32_t size)
{
    if (map) {
        ESP_LOGE(TAG, "tried to bootloader_mmap twice");
        return NULL; /* existing mapping in use... */
    }
    const void *result = NULL;
    uint32_t src_page = src_addr & ~(SPI_FLASH_MMU_PAGE_SIZE - 1);
    size += (src_addr - src_page);
    esp_err_t err = spi_flash_mmap(src_page, size, SPI_FLASH_MMAP_DATA, &result, &map);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "spi_flash_mmap failed: 0x%x", err);
        return NULL;
    }
    return (void *)((intptr_t)result + (src_addr - src_page));
}