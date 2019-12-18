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

/* Variables and functions */
 int /*<<< orphan*/  get_spi_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_flash_ll_cmd_is_done (int /*<<< orphan*/ ) ; 

void spi_flash_hal_poll_cmd_done(spi_flash_host_driver_t *host)
{
    while (!spi_flash_ll_cmd_is_done(get_spi_dev(host))) {
        //nop
    }
}