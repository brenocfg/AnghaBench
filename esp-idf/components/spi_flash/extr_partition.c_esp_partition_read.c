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
typedef  int /*<<< orphan*/  spi_flash_mmap_handle_t ;
struct TYPE_4__ {size_t size; scalar_t__ flash_chip; scalar_t__ address; int /*<<< orphan*/  encrypted; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_INVALID_SIZE ; 
 scalar_t__ ESP_ERR_NOT_SUPPORTED ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SPI_FLASH_MMAP_DATA ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_flash_default_chip ; 
 scalar_t__ esp_flash_read (scalar_t__,void*,scalar_t__,size_t) ; 
 scalar_t__ esp_partition_mmap (TYPE_1__ const*,size_t,size_t,int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  spi_flash_munmap (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_flash_read (scalar_t__,void*,size_t) ; 

esp_err_t esp_partition_read(const esp_partition_t* partition,
        size_t src_offset, void* dst, size_t size)
{
    assert(partition != NULL);
    if (src_offset > partition->size) {
        return ESP_ERR_INVALID_ARG;
    }
    if (src_offset + size > partition->size) {
        return ESP_ERR_INVALID_SIZE;
    }

    if (!partition->encrypted) {
#ifndef CONFIG_SPI_FLASH_USE_LEGACY_IMPL
        return esp_flash_read(partition->flash_chip, dst, partition->address + src_offset, size);
#else
        return spi_flash_read(partition->address + src_offset, dst, size);
#endif // CONFIG_SPI_FLASH_USE_LEGACY_IMPL
    } else {
#if CONFIG_SECURE_FLASH_ENC_ENABLED
        if (partition->flash_chip != esp_flash_default_chip) {
            return ESP_ERR_NOT_SUPPORTED;
        }

        /* Encrypted partitions need to be read via a cache mapping */
        const void *buf;
        spi_flash_mmap_handle_t handle;
        esp_err_t err;

        err = esp_partition_mmap(partition, src_offset, size,
                                 SPI_FLASH_MMAP_DATA, &buf, &handle);
        if (err != ESP_OK) {
            return err;
        }
        memcpy(dst, buf, size);
        spi_flash_munmap(handle);
        return ESP_OK;
#else
        return ESP_ERR_NOT_SUPPORTED;
#endif // CONFIG_SECURE_FLASH_ENC_ENABLED
    }
}