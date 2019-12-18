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
typedef  int /*<<< orphan*/  spi_flash_mmap_memory_t ;
typedef  int /*<<< orphan*/  spi_flash_mmap_handle_t ;
typedef  size_t ptrdiff_t ;
struct TYPE_3__ {size_t size; scalar_t__ flash_chip; size_t address; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_INVALID_SIZE ; 
 scalar_t__ ESP_ERR_NOT_SUPPORTED ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_flash_default_chip ; 
 scalar_t__ spi_flash_mmap (size_t,size_t,int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *) ; 

esp_err_t esp_partition_mmap(const esp_partition_t* partition, size_t offset, size_t size,
                             spi_flash_mmap_memory_t memory,
                             const void** out_ptr, spi_flash_mmap_handle_t* out_handle)
{
    assert(partition != NULL);
    if (offset > partition->size) {
        return ESP_ERR_INVALID_ARG;
    }
    if (offset + size > partition->size) {
        return ESP_ERR_INVALID_SIZE;
    }
    if (partition->flash_chip != esp_flash_default_chip) {
        return ESP_ERR_NOT_SUPPORTED;
    }
    size_t phys_addr = partition->address + offset;
    // offset within 64kB block
    size_t region_offset = phys_addr & 0xffff;
    size_t mmap_addr = phys_addr & 0xffff0000;
    esp_err_t rc = spi_flash_mmap(mmap_addr, size+region_offset, memory, out_ptr, out_handle);
    // adjust returned pointer to point to the correct offset
    if (rc == ESP_OK) {
        *out_ptr = (void*) (((ptrdiff_t) *out_ptr) + region_offset);
    }
    return rc;
}