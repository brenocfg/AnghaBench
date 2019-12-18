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
struct TYPE_5__ {TYPE_1__* dmadesc_rx; scalar_t__ rx_buffer; scalar_t__ use_dma; } ;
typedef  TYPE_2__ spi_slave_hal_context_t ;
struct TYPE_4__ {scalar_t__ eof; scalar_t__ owner; } ;

/* Variables and functions */

bool spi_slave_hal_dma_need_reset(const spi_slave_hal_context_t *hal)
{
    bool ret;
    ret = false;
    if (hal->use_dma && hal->rx_buffer) {
        int i;
        //In case CS goes high too soon, the transfer is aborted while the DMA channel still thinks it's going. This
        //leads to issues later on, so in that case we need to reset the channel. The state can be detected because
        //the DMA system doesn't give back the offending descriptor; the owner is still set to DMA.
        for (i = 0; hal->dmadesc_rx[i].eof == 0 && hal->dmadesc_rx[i].owner == 0; i++) {}
        if (hal->dmadesc_rx[i].owner) {
            ret = true;
        }
    }
    return ret;
}