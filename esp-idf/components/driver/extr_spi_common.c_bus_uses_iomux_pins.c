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
typedef  size_t spi_host_device_t ;
struct TYPE_4__ {scalar_t__ sclk_io_num; scalar_t__ quadwp_io_num; scalar_t__ quadhd_io_num; scalar_t__ mosi_io_num; scalar_t__ miso_io_num; } ;
typedef  TYPE_1__ spi_bus_config_t ;
struct TYPE_5__ {scalar_t__ spiclk_iomux_pin; scalar_t__ spiwp_iomux_pin; scalar_t__ spihd_iomux_pin; scalar_t__ spid_iomux_pin; scalar_t__ spiq_iomux_pin; } ;

/* Variables and functions */
 TYPE_2__* spi_periph_signal ; 

__attribute__((used)) static bool bus_uses_iomux_pins(spi_host_device_t host, const spi_bus_config_t* bus_config)
{
    if (bus_config->sclk_io_num>=0 &&
        bus_config->sclk_io_num != spi_periph_signal[host].spiclk_iomux_pin) return false;
    if (bus_config->quadwp_io_num>=0 &&
        bus_config->quadwp_io_num != spi_periph_signal[host].spiwp_iomux_pin) return false;
    if (bus_config->quadhd_io_num>=0 &&
        bus_config->quadhd_io_num != spi_periph_signal[host].spihd_iomux_pin) return false;
    if (bus_config->mosi_io_num >= 0 &&
        bus_config->mosi_io_num != spi_periph_signal[host].spid_iomux_pin) return false;
    if (bus_config->miso_io_num>=0 &&
        bus_config->miso_io_num != spi_periph_signal[host].spiq_iomux_pin) return false;

    return true;
}