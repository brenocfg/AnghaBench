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
struct TYPE_3__ {int mosi_io_num; int miso_io_num; int sclk_io_num; int quadwp_io_num; int quadhd_io_num; } ;
typedef  TYPE_1__ spi_bus_config_t ;
typedef  int /*<<< orphan*/  pin_array ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ GPIO_IS_VALID_GPIO (int const) ; 
 int /*<<< orphan*/  gpio_reset_pin (int const) ; 

esp_err_t spicommon_bus_free_io_cfg(const spi_bus_config_t *bus_cfg)
{
    int pin_array[] = {
        bus_cfg->mosi_io_num,
        bus_cfg->miso_io_num,
        bus_cfg->sclk_io_num,
        bus_cfg->quadwp_io_num,
        bus_cfg->quadhd_io_num,
    };
    for (int i = 0; i < sizeof(pin_array)/sizeof(int); i ++) {
        const int io = pin_array[i];
        if (io >= 0 && GPIO_IS_VALID_GPIO(io)) gpio_reset_pin(io);
    }
    return ESP_OK;
}