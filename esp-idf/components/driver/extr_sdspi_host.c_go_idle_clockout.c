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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int length; int /*<<< orphan*/ * rx_buffer; int /*<<< orphan*/ * tx_buffer; } ;
typedef  TYPE_1__ spi_transaction_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spi_device_transmit (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  spi_handle (int) ; 

__attribute__((used)) static void go_idle_clockout(int slot)
{
    //actually we need 10, declare 12 to meet requirement of RXDMA
    uint8_t data[12];
    memset(data, 0xff, sizeof(data));
    spi_transaction_t t = {
        .length = 10*8,
        .tx_buffer = data,
        .rx_buffer = data,
    };
    spi_device_transmit(spi_handle(slot), &t);
    // don't care if this failed
}