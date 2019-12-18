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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ spi_flash_host_driver_t ;
struct TYPE_5__ {int /*<<< orphan*/ * spi; } ;
typedef  TYPE_2__ memspi_host_data_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SPI1 ; 
 int /*<<< orphan*/  spi_flash_check_and_flush_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t memspi_host_flush_cache(spi_flash_host_driver_t* driver, uint32_t addr, uint32_t size)
{
    if (((memspi_host_data_t*)(driver->driver_data))->spi == &SPI1) {
        spi_flash_check_and_flush_cache(addr, size);
    }
    return ESP_OK;
}