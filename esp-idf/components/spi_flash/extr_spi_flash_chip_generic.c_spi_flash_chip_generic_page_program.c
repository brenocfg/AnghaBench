#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {TYPE_1__* chip_drv; TYPE_4__* host; } ;
typedef  TYPE_2__ esp_flash_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* program_page ) (TYPE_4__*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {scalar_t__ (* wait_idle ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_PAGE_PROGRAM_TIMEOUT ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_2__*,int /*<<< orphan*/ ) ; 

esp_err_t spi_flash_chip_generic_page_program(esp_flash_t *chip, const void *buffer, uint32_t address, uint32_t length)
{
    esp_err_t err;

    err = chip->chip_drv->wait_idle(chip, DEFAULT_IDLE_TIMEOUT);

    if (err == ESP_OK) {
        // Perform the actual Page Program command
        chip->host->program_page(chip->host, buffer, address, length);

        err = chip->chip_drv->wait_idle(chip, DEFAULT_PAGE_PROGRAM_TIMEOUT);
    }
    return err;
}