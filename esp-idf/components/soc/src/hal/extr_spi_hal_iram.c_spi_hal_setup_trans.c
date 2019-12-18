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
typedef  int uint32_t ;
struct TYPE_5__ {int mode; int cmd_bits; int addr_bits; scalar_t__ cs_setup; int /*<<< orphan*/  tx_lsbfirst; int /*<<< orphan*/  addr; int /*<<< orphan*/  cmd; scalar_t__ half_duplex; int /*<<< orphan*/  tx_bitlen; int /*<<< orphan*/  rx_bitlen; TYPE_1__* timing_conf; scalar_t__ dummy_bits; int /*<<< orphan*/  no_compensate; scalar_t__ rcv_buffer; int /*<<< orphan*/  io_mode; int /*<<< orphan*/ * hw; } ;
typedef  TYPE_2__ spi_hal_context_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;
struct TYPE_4__ {int timing_dummy; int timing_miso_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  spi_ll_clear_int_stat (int /*<<< orphan*/ *) ; 
 scalar_t__ spi_ll_get_running_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_master_set_io_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_set_addr_bitlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi_ll_set_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_set_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_set_command_bitlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi_ll_set_dummy (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spi_ll_set_miso_bitlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_set_miso_delay (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spi_ll_set_mosi_bitlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void spi_hal_setup_trans(const spi_hal_context_t *hal)
{
    spi_dev_t *hw = hal->hw;

    //clear int bit
    spi_ll_clear_int_stat(hal->hw);
    //We should be done with the transmission.
    assert(spi_ll_get_running_cmd(hw) == 0);

    spi_ll_master_set_io_mode(hw, hal->io_mode);

    int extra_dummy = 0;
    //when no_dummy is not set and in half-duplex mode, sets the dummy bit if RX phase exist
    if (hal->rcv_buffer && !hal->no_compensate && hal->half_duplex) {
        extra_dummy = hal->timing_conf->timing_dummy;
    }

    //SPI iface needs to be configured for a delay in some cases.
    //configure dummy bits
    spi_ll_set_dummy(hw, extra_dummy + hal->dummy_bits);

    uint32_t miso_delay_num = 0;
    uint32_t miso_delay_mode = 0;
    if (hal->timing_conf->timing_miso_delay < 0) {
        //if the data comes too late, delay half a SPI clock to improve reading
        switch (hal->mode) {
        case 0:
            miso_delay_mode = 2;
            break;
        case 1:
            miso_delay_mode = 1;
            break;
        case 2:
            miso_delay_mode = 1;
            break;
        case 3:
            miso_delay_mode = 2;
            break;
        }
        miso_delay_num = 0;
    } else {
        //if the data is so fast that dummy_bit is used, delay some apb clocks to meet the timing
        miso_delay_num = extra_dummy ? hal->timing_conf->timing_miso_delay : 0;
        miso_delay_mode = 0;
    }
    spi_ll_set_miso_delay(hw, miso_delay_mode, miso_delay_num);

    spi_ll_set_mosi_bitlen(hw, hal->tx_bitlen);

    if (hal->half_duplex) {
        spi_ll_set_miso_bitlen(hw, hal->rx_bitlen);
    } else {
        //rxlength is not used in full-duplex mode
        spi_ll_set_miso_bitlen(hw, hal->tx_bitlen);
    }

    //Configure bit sizes, load addr and command
    int cmdlen = hal->cmd_bits;
    int addrlen = hal->addr_bits;
    if (!hal->half_duplex && hal->cs_setup != 0) {
        /* The command and address phase is not compatible with cs_ena_pretrans
         * in full duplex mode.
         */
        cmdlen = 0;
        addrlen = 0;
    }

    spi_ll_set_addr_bitlen(hw, addrlen);
    spi_ll_set_command_bitlen(hw, cmdlen);

    spi_ll_set_command(hw, hal->cmd, cmdlen, hal->tx_lsbfirst);
    spi_ll_set_address(hw, hal->addr, addrlen, hal->tx_lsbfirst);
}