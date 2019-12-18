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
struct TYPE_3__ {int /*<<< orphan*/  rx_bitlen; scalar_t__ rcv_buffer; int /*<<< orphan*/  hw; int /*<<< orphan*/  dma_enabled; } ;
typedef  TYPE_1__ spi_hal_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  spi_ll_read_buffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void spi_hal_fetch_result(const spi_hal_context_t *hal)
{
    if (hal->rcv_buffer && !hal->dma_enabled) {
        //Need to copy from SPI regs to result buffer.
        spi_ll_read_buffer(hal->hw, hal->rcv_buffer, hal->rx_bitlen);
    }
}