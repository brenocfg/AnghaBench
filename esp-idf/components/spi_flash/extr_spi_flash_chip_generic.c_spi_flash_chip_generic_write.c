#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {TYPE_3__* host; TYPE_1__* chip_drv; } ;
typedef  TYPE_2__ esp_flash_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_9__ {scalar_t__ const max_write_bytes; scalar_t__ (* flush_cache ) (TYPE_3__*,scalar_t__,scalar_t__) ;} ;
struct TYPE_7__ {scalar_t__ page_size; scalar_t__ (* set_chip_write_protect ) (TYPE_2__*,int) ;scalar_t__ (* program_page ) (TYPE_2__*,void const*,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 scalar_t__ MIN (scalar_t__ const,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*,int) ; 
 scalar_t__ stub2 (TYPE_2__*,void const*,scalar_t__,scalar_t__) ; 
 scalar_t__ stub3 (TYPE_3__*,scalar_t__,scalar_t__) ; 

esp_err_t spi_flash_chip_generic_write(esp_flash_t *chip, const void *buffer, uint32_t address, uint32_t length)
{
    esp_err_t err = ESP_OK;
    const uint32_t page_size = chip->chip_drv->page_size;

    while (err == ESP_OK && length > 0) {
        uint32_t page_len = MIN(chip->host->max_write_bytes, MIN(page_size, length));
        if ((address + page_len) / page_size != address / page_size) {
            // Most flash chips can't page write across a page boundary
            page_len = page_size - (address % page_size);
        }

        err = chip->chip_drv->set_chip_write_protect(chip, false);

        if (err == ESP_OK) {
            err = chip->chip_drv->program_page(chip, buffer, address, page_len);
            address += page_len;
            buffer = (void *)((intptr_t)buffer + page_len);
            length -= page_len;
        }
    }
    if (err == ESP_OK && chip->host->flush_cache) {
        err = chip->host->flush_cache(chip->host, address, length);
    }
    return err;
}