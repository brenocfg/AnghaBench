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
struct TYPE_3__ {size_t size; scalar_t__ address; int /*<<< orphan*/  flash_chip; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_SIZE ; 
 size_t SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_flash_erase_region (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  spi_flash_erase_range (scalar_t__,size_t) ; 

esp_err_t esp_partition_erase_range(const esp_partition_t* partition,
                                    size_t offset, size_t size)
{
    assert(partition != NULL);
    if (offset > partition->size) {
        return ESP_ERR_INVALID_ARG;
    }
    if (offset + size > partition->size) {
        return ESP_ERR_INVALID_SIZE;
    }
    if (size % SPI_FLASH_SEC_SIZE != 0) {
        return ESP_ERR_INVALID_SIZE;
    }
    if (offset % SPI_FLASH_SEC_SIZE != 0) {
        return ESP_ERR_INVALID_ARG;
    }
#ifndef CONFIG_SPI_FLASH_USE_LEGACY_IMPL
    return esp_flash_erase_region(partition->flash_chip, partition->address + offset, size);
#else
    return spi_flash_erase_range(partition->address + offset, size);
#endif // CONFIG_SPI_FLASH_USE_LEGACY_IMPL
}