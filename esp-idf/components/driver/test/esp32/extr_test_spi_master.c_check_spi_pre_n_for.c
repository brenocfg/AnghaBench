#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_10__ {int length; char* tx_buffer; } ;
typedef  TYPE_2__ spi_transaction_t ;
struct TYPE_11__ {int clock_speed_hz; int duty_cycle_pos; int spics_io_num; int queue_size; int /*<<< orphan*/  mode; int /*<<< orphan*/  dummy_bits; int /*<<< orphan*/  address_bits; int /*<<< orphan*/  command_bits; } ;
typedef  TYPE_3__ spi_device_interface_config_t ;
typedef  int /*<<< orphan*/  spi_device_handle_t ;
struct TYPE_9__ {int clkdiv_pre; int clkcnt_n; } ;
struct TYPE_12__ {TYPE_1__ clock; } ;
typedef  TYPE_4__ spi_dev_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_13__ {TYPE_4__* hw; } ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 size_t TEST_SPI_HOST ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 
 scalar_t__ spi_bus_add_device (size_t,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ spi_bus_remove_device (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_device_transmit (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_5__* spi_periph_signal ; 

__attribute__((used)) static void check_spi_pre_n_for(int clk, int pre, int n)
{
    esp_err_t ret;
    spi_device_handle_t handle;

    spi_device_interface_config_t devcfg={
        .command_bits=0,
        .address_bits=0,
        .dummy_bits=0,
        .clock_speed_hz=clk,
        .duty_cycle_pos=128,
        .mode=0,
        .spics_io_num=21,
        .queue_size=3
    };
    char sendbuf[16]="";
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));

    ret=spi_bus_add_device(TEST_SPI_HOST, &devcfg, &handle);
    TEST_ASSERT(ret==ESP_OK);

    t.length=16*8;
    t.tx_buffer=sendbuf;
    ret=spi_device_transmit(handle, &t);

    spi_dev_t* hw = spi_periph_signal[TEST_SPI_HOST].hw;

    printf("Checking clk rate %dHz. expect pre %d n %d, got pre %d n %d\n", clk, pre, n, hw->clock.clkdiv_pre+1, hw->clock.clkcnt_n+1);

    TEST_ASSERT(hw->clock.clkcnt_n+1==n);
    TEST_ASSERT(hw->clock.clkdiv_pre+1==pre);

    ret=spi_bus_remove_device(handle);
    TEST_ASSERT(ret==ESP_OK);
}