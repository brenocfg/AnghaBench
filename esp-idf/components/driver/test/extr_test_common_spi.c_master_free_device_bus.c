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
typedef  int /*<<< orphan*/  spi_device_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_SPI_HOST ; 
 int /*<<< orphan*/  spi_bus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_remove_device (int /*<<< orphan*/ ) ; 

void master_free_device_bus(spi_device_handle_t spi)
{
    TEST_ESP_OK( spi_bus_remove_device(spi) );
    TEST_ESP_OK( spi_bus_free(TEST_SPI_HOST) );
}