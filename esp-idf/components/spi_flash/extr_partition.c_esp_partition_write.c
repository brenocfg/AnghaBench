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
struct TYPE_3__ {size_t size; size_t address; scalar_t__ flash_chip; int /*<<< orphan*/  encrypted; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_SIZE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_flash_default_chip ; 
 int /*<<< orphan*/  esp_flash_write (scalar_t__,void const*,size_t,size_t) ; 
 int /*<<< orphan*/  spi_flash_write (size_t,void const*,size_t) ; 
 int /*<<< orphan*/  spi_flash_write_encrypted (size_t,void const*,size_t) ; 

esp_err_t esp_partition_write(const esp_partition_t* partition,
                             size_t dst_offset, const void* src, size_t size)
{
    assert(partition != NULL);
    if (dst_offset > partition->size) {
        return ESP_ERR_INVALID_ARG;
    }
    if (dst_offset + size > partition->size) {
        return ESP_ERR_INVALID_SIZE;
    }
    dst_offset = partition->address + dst_offset;
    if (!partition->encrypted) {
#ifndef CONFIG_SPI_FLASH_USE_LEGACY_IMPL
        return esp_flash_write(partition->flash_chip, src, dst_offset, size);
#else
        return spi_flash_write(dst_offset, src, size);
#endif // CONFIG_SPI_FLASH_USE_LEGACY_IMPL
    } else {
#if CONFIG_SECURE_FLASH_ENC_ENABLED
        if (partition->flash_chip != esp_flash_default_chip) {
            return ESP_ERR_NOT_SUPPORTED;
        }
        return spi_flash_write_encrypted(dst_offset, src, size);
#else
        return ESP_ERR_NOT_SUPPORTED;
#endif // CONFIG_SECURE_FLASH_ENC_ENABLED
    }
}