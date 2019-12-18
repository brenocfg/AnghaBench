#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * flush_cache; TYPE_2__* driver_data; } ;
typedef  TYPE_1__ spi_flash_host_driver_t ;
struct TYPE_8__ {int /*<<< orphan*/ * spi; } ;
typedef  TYPE_2__ memspi_host_data_t ;
typedef  int /*<<< orphan*/  memspi_host_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SPI1 ; 
 int /*<<< orphan*/  esp_flash_default_host ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ spi_flash_hal_init (TYPE_2__*,int /*<<< orphan*/  const*) ; 

esp_err_t memspi_host_init_pointers(spi_flash_host_driver_t *host, memspi_host_data_t *data, const memspi_host_config_t *cfg)
{
    memcpy(host, &esp_flash_default_host, sizeof(spi_flash_host_driver_t));
    esp_err_t err = spi_flash_hal_init(data, cfg);
    if (err != ESP_OK) {
        return err;
    }

    host->driver_data = data;
    //some functions are not required if not SPI1
    if (data->spi != &SPI1) {
        host->flush_cache = NULL;
    }
    return ESP_OK;
}