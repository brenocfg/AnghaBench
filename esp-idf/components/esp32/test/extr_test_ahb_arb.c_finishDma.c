#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I2S_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_DSCR_EN ; 
 int /*<<< orphan*/  I2S_FIFO_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_INLINK_START ; 
 int /*<<< orphan*/  I2S_INT_RAW_REG (int /*<<< orphan*/ ) ; 
 int I2S_OUTLINK_START ; 
 int /*<<< orphan*/  I2S_OUT_LINK_REG (int /*<<< orphan*/ ) ; 
 int I2S_RX_FIFO_RESET ; 
 int I2S_RX_RESET ; 
 int I2S_RX_START ; 
 int /*<<< orphan*/  I2S_STATE_REG (int /*<<< orphan*/ ) ; 
 int I2S_TX_FIFO_RESET ; 
 int I2S_TX_FIFO_RESET_BACK ; 
 int I2S_TX_IDLE ; 
 int I2S_TX_REMPTY_INT_RAW ; 
 int I2S_TX_RESET ; 
 int I2S_TX_START ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void finishDma(void)
{
    //No need to finish if no DMA transfer going on
    if (!(READ_PERI_REG(I2S_FIFO_CONF_REG(0))&I2S_DSCR_EN)) {
        return;
    }

    //Wait till fifo done
    while (!(READ_PERI_REG(I2S_INT_RAW_REG(0))&I2S_TX_REMPTY_INT_RAW)) ;
    //Wait for last bytes to leave i2s xmit thing
    //ToDo: poll bit in next hw
//  for (i=0; i<(1<<8); i++);
    while (!(READ_PERI_REG(I2S_STATE_REG(0))&I2S_TX_IDLE));

    //Reset I2S for next transfer
    CLEAR_PERI_REG_MASK(I2S_CONF_REG(0), I2S_TX_START | I2S_RX_START);
    CLEAR_PERI_REG_MASK(I2S_OUT_LINK_REG(0), I2S_OUTLINK_START | I2S_INLINK_START);

    SET_PERI_REG_MASK(I2S_CONF_REG(0), I2S_TX_RESET | I2S_TX_FIFO_RESET | I2S_RX_RESET | I2S_RX_FIFO_RESET);
    CLEAR_PERI_REG_MASK(I2S_CONF_REG(0), I2S_TX_RESET | I2S_TX_FIFO_RESET | I2S_RX_RESET | I2S_RX_FIFO_RESET);

//  for (i=0; i<(1<<8); i++);
    while ((READ_PERI_REG(I2S_STATE_REG(0))&I2S_TX_FIFO_RESET_BACK));
}