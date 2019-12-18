#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  spi_flash_host_driver_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPI0 ; 
 int /*<<< orphan*/  SPI1 ; 
 int /*<<< orphan*/ * get_spi_dev (int /*<<< orphan*/ *) ; 
 int spi_flash_ll_host_idle (int /*<<< orphan*/ *) ; 

bool spi_flash_hal_host_idle(spi_flash_host_driver_t *host)
{
    spi_dev_t *dev = get_spi_dev(host);
    bool idle = spi_flash_ll_host_idle(dev);

    // Not clear if this is necessary, or only necessary if
    // chip->spi == SPI1. But probably doesn't hurt...
    if (dev == &SPI1) {
        idle &= spi_flash_ll_host_idle(&SPI0);
    }

    return idle;
}