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
struct TYPE_5__ {int /*<<< orphan*/  cs_pin_id; int /*<<< orphan*/  cs_hold; int /*<<< orphan*/  cs_setup; int /*<<< orphan*/  sio; int /*<<< orphan*/  half_duplex; int /*<<< orphan*/  mode; int /*<<< orphan*/  tx_lsbfirst; int /*<<< orphan*/  rx_lsbfirst; TYPE_1__* timing_conf; int /*<<< orphan*/  positive_cs; int /*<<< orphan*/  as_cs; int /*<<< orphan*/ * hw; } ;
typedef  TYPE_2__ spi_hal_context_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;
struct TYPE_4__ {int /*<<< orphan*/  clock_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_ll_master_select_cs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_master_set_cksel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_master_set_clock_by_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_master_set_cs_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_master_set_cs_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_master_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_master_set_pos_cs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_set_half_duplex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_set_rx_lsbfirst (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_set_sio_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_set_tx_lsbfirst (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void spi_hal_setup_device(const spi_hal_context_t *hal)
{
    //Configure clock settings
    spi_dev_t *hw = hal->hw;
#ifdef SOC_SPI_SUPPORT_AS_CS
    spi_ll_master_set_cksel(hw, hal->cs_pin_id, hal->as_cs);
#endif
    spi_ll_master_set_pos_cs(hw, hal->cs_pin_id, hal->positive_cs);
    spi_ll_master_set_clock_by_reg(hw, &hal->timing_conf->clock_reg);
    //Configure bit order
    spi_ll_set_rx_lsbfirst(hw, hal->rx_lsbfirst);
    spi_ll_set_tx_lsbfirst(hw, hal->tx_lsbfirst);
    spi_ll_master_set_mode(hw, hal->mode);
    //Configure misc stuff
    spi_ll_set_half_duplex(hw, hal->half_duplex);
    spi_ll_set_sio_mode(hw, hal->sio);
    //Configure CS pin and timing
    spi_ll_master_set_cs_setup(hw, hal->cs_setup);
    spi_ll_master_set_cs_hold(hw, hal->cs_hold);
    spi_ll_master_select_cs(hw, hal->cs_pin_id);
}