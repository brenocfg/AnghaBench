#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {TYPE_2__* host; } ;
typedef  TYPE_1__ esp_flash_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_5__ {scalar_t__ (* read_status ) (TYPE_2__*,int*) ;} ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int SR_WREN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*,int*) ; 

esp_err_t spi_flash_chip_generic_get_write_protect(esp_flash_t *chip, bool *out_write_protect)
{
    esp_err_t err = ESP_OK;
    uint8_t status;
    assert(out_write_protect!=NULL);
    err = chip->host->read_status(chip->host, &status);
    if (err != ESP_OK) {
        return err;
    }

    *out_write_protect = ((status & SR_WREN) == 0);
    return err;
}