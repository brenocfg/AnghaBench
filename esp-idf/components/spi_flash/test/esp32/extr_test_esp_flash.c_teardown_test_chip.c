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
typedef  int /*<<< orphan*/  spi_host_device_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;

/* Variables and functions */
 int /*<<< orphan*/  release_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_remove_flash_device (int /*<<< orphan*/ *) ; 

void teardown_test_chip(esp_flash_t* chip, spi_host_device_t host)
{
    //happen to work when chip==NULL
    spi_bus_remove_flash_device(chip);
    release_bus(host);
}