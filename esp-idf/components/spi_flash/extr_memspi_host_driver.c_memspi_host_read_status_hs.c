#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int miso_len; int /*<<< orphan*/ * miso_data; int /*<<< orphan*/  mosi_len; int /*<<< orphan*/  mosi_data; int /*<<< orphan*/  command; } ;
typedef  TYPE_1__ spi_flash_trans_t ;
struct TYPE_7__ {scalar_t__ (* common_command ) (TYPE_2__*,TYPE_1__*) ;} ;
typedef  TYPE_2__ spi_flash_host_driver_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RDSR ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ stub1 (TYPE_2__*,TYPE_1__*) ; 

esp_err_t memspi_host_read_status_hs(spi_flash_host_driver_t *driver, uint8_t *out_sr)
{
    //NOTE: we do have a read id function, however it doesn't work in high freq
    spi_flash_trans_t t = {
        .command = CMD_RDSR,
        .mosi_data = 0,
        .mosi_len = 0,
        .miso_len = 8
    };
    esp_err_t err = driver->common_command(driver, &t);
    if (err != ESP_OK) {
        return err;
    }
    *out_sr = t.miso_data[0];
    return ESP_OK;
}