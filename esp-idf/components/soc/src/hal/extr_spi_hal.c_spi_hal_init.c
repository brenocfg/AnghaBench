#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * hw; } ;
typedef  TYPE_1__ spi_hal_context_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;
struct TYPE_6__ {int /*<<< orphan*/ * hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_ll_enable_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_master_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_set_int_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_set_mosi_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* spi_periph_signal ; 

void spi_hal_init(spi_hal_context_t *hal, int host_id)
{
    memset(hal, 0, sizeof(spi_hal_context_t));
    spi_dev_t *hw = spi_periph_signal[host_id].hw;
    hal->hw = hw;
    spi_ll_master_init(hw);

    //Force a transaction done interrupt. This interrupt won't fire yet because
    //we initialized the SPI interrupt as disabled. This way, we can just
    //enable the SPI interrupt and the interrupt handler will kick in, handling
    //any transactions that are queued.
    spi_ll_enable_int(hw);
    spi_ll_set_int_stat(hw);
    spi_ll_set_mosi_delay(hw, 0, 0);
}