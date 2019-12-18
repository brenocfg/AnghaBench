#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * hw; } ;
typedef  TYPE_1__ spi_slave_hal_context_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;
struct TYPE_6__ {int /*<<< orphan*/ * hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_LL_INT_TYPE_NORMAL ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_ll_set_int_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_slave_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_slave_set_int_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* spi_periph_signal ; 

void spi_slave_hal_init(spi_slave_hal_context_t *hal, int host_id)
{
    memset(hal, 0, sizeof(spi_slave_hal_context_t));
    spi_dev_t *hw = spi_periph_signal[host_id].hw;
    hal->hw = hw;

    spi_ll_slave_init(hal->hw);

    //Force a transaction done interrupt. This interrupt won't fire yet because we initialized the SPI interrupt as
    //disabled.  This way, we can just enable the SPI interrupt and the interrupt handler will kick in, handling
    //any transactions that are queued.
    spi_ll_set_int_stat(hal->hw);
    spi_ll_slave_set_int_type(hal->hw, SPI_LL_INT_TYPE_NORMAL);
}