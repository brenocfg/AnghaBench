#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* poll_cmd_done ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ spi_flash_host_driver_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/ * get_spi_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_flash_ll_set_write_protect (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

esp_err_t spi_flash_hal_set_write_protect(spi_flash_host_driver_t *host, bool wp)
{
    spi_dev_t *dev = get_spi_dev(host);
    spi_flash_ll_set_write_protect(dev, wp);
    host->poll_cmd_done(host);
    return ESP_OK;
}