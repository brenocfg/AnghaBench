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

/* Variables and functions */
 int /*<<< orphan*/  spi_flash_init_lock () ; 
 int /*<<< orphan*/  spi_flash_reset_counters () ; 

void spi_flash_init(void)
{
    spi_flash_init_lock();
#if CONFIG_SPI_FLASH_ENABLE_COUNTERS
    spi_flash_reset_counters();
#endif
}