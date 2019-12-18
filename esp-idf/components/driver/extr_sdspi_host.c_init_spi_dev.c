#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spi_host_device_t ;
struct TYPE_4__ {int clock_speed_hz; int /*<<< orphan*/  queue_size; int /*<<< orphan*/  spics_io_num; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ spi_device_interface_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_NUM_NC ; 
 int /*<<< orphan*/  SDSPI_TRANSACTION_COUNT ; 
 TYPE_3__* s_slots ; 
 int /*<<< orphan*/  spi_bus_add_device (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  spi_bus_remove_device (scalar_t__) ; 
 scalar_t__ spi_handle (int) ; 

__attribute__((used)) static esp_err_t init_spi_dev(int slot, int clock_speed_hz)
{
    if (spi_handle(slot)) {
        // Reinitializing
        spi_bus_remove_device(spi_handle(slot));
        s_slots[slot].handle = NULL;
    }
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = clock_speed_hz,
        .mode = 0,
        // For SD cards, CS must stay low during the whole read/write operation,
        // rather than a single SPI transaction.
        .spics_io_num = GPIO_NUM_NC,
        .queue_size = SDSPI_TRANSACTION_COUNT,
    };
    return spi_bus_add_device((spi_host_device_t) slot, &devcfg, &s_slots[slot].handle);
}