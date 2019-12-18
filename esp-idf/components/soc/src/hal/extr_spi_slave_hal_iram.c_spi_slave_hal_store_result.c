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
struct TYPE_3__ {int rcv_bitlen; int bitlen; int /*<<< orphan*/  hw; scalar_t__ rx_buffer; int /*<<< orphan*/  use_dma; } ;
typedef  TYPE_1__ spi_slave_hal_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_LL_INT_TYPE_NORMAL ; 
 int /*<<< orphan*/  spi_ll_read_buffer (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int spi_ll_slave_get_rcv_bitlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_slave_set_int_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void spi_slave_hal_store_result(spi_slave_hal_context_t *hal)
{
    //when data of cur_trans->length are all sent, the slv_rdata_bit
    //will be the length sent-1 (i.e. cur_trans->length-1 ), otherwise
    //the length sent.
    hal->rcv_bitlen = spi_ll_slave_get_rcv_bitlen(hal->hw);
    if (hal->rcv_bitlen == hal->bitlen - 1) {
        hal->rcv_bitlen++;
    }
    if (!hal->use_dma && hal->rx_buffer) {
        //Copy result out
        spi_ll_read_buffer(hal->hw, hal->rx_buffer, hal->bitlen);
    }
    spi_ll_slave_set_int_type(hal->hw, SPI_LL_INT_TYPE_NORMAL);
}