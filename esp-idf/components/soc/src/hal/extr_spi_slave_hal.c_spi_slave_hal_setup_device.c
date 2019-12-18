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
struct TYPE_3__ {int /*<<< orphan*/  use_dma; int /*<<< orphan*/  mode; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_lsbfirst; int /*<<< orphan*/  rx_lsbfirst; } ;
typedef  TYPE_1__ spi_slave_hal_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  spi_ll_set_rx_lsbfirst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_set_tx_lsbfirst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_slave_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void spi_slave_hal_setup_device(const spi_slave_hal_context_t *hal)
{
    spi_ll_set_rx_lsbfirst(hal->hw, hal->rx_lsbfirst);
    spi_ll_set_tx_lsbfirst(hal->hw, hal->tx_lsbfirst);
    spi_ll_slave_set_mode(hal->hw, hal->mode, hal->use_dma);
}