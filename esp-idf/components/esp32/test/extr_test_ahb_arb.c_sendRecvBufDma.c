#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int length; int size; int owner; int eof; scalar_t__ empty; scalar_t__ offset; int /*<<< orphan*/ * buf; scalar_t__ sosf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int I2S_AHBM_FIFO_RST ; 
 int I2S_AHBM_RST ; 
 int /*<<< orphan*/  I2S_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_DSCR_EN ; 
 int /*<<< orphan*/  I2S_FIFO_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_INDSCR_BURST_EN ; 
 int I2S_INLINK_ADDR ; 
 int I2S_INLINK_START ; 
 int /*<<< orphan*/  I2S_INT_CLR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_IN_LINK_REG (int /*<<< orphan*/ ) ; 
 int I2S_IN_RST ; 
 int /*<<< orphan*/  I2S_LC_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_MEM_TRANS_EN ; 
 int I2S_OUTDSCR_BURST_EN ; 
 int I2S_OUTLINK_ADDR ; 
 int I2S_OUTLINK_START ; 
 int I2S_OUT_DATA_BURST_EN ; 
 int I2S_OUT_EOF_MODE ; 
 int /*<<< orphan*/  I2S_OUT_LINK_REG (int /*<<< orphan*/ ) ; 
 int I2S_OUT_RST ; 
 int /*<<< orphan*/  I2S_RXEOF_NUM_REG (int /*<<< orphan*/ ) ; 
 int I2S_RX_FIFO_RESET ; 
 int I2S_RX_RESET ; 
 int I2S_RX_START ; 
 int I2S_TX_FIFO_RESET ; 
 int I2S_TX_RESET ; 
 int I2S_TX_START ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* dmaDesc ; 

__attribute__((used)) static void sendRecvBufDma(uint16_t *sbuf, uint16_t *rbuf, int len)
{
    //Fill DMA descriptor
    dmaDesc[0].length = len * 2;
    dmaDesc[0].size = len * 2;
    dmaDesc[0].owner = 1;
    dmaDesc[0].sosf = 0;
    dmaDesc[0].buf = (uint8_t *)sbuf;
    dmaDesc[0].offset = 0; //unused in hw
    dmaDesc[0].empty = 0;
    dmaDesc[0].eof = 1;
    dmaDesc[1].length = len * 2;
    dmaDesc[1].size = len * 2;
    dmaDesc[1].owner = 1;
    dmaDesc[1].sosf = 0;
    dmaDesc[1].buf = (uint8_t *)rbuf;
    dmaDesc[1].offset = 0; //unused in hw
    dmaDesc[1].empty = 0;
    dmaDesc[1].eof = 1;

    //Reset DMA
    SET_PERI_REG_MASK(I2S_LC_CONF_REG(0), I2S_IN_RST | I2S_OUT_RST | I2S_AHBM_RST | I2S_AHBM_FIFO_RST);
    CLEAR_PERI_REG_MASK(I2S_LC_CONF_REG(0), I2S_IN_RST | I2S_OUT_RST | I2S_AHBM_RST | I2S_AHBM_FIFO_RST);

    //Reset I2S FIFO
    SET_PERI_REG_MASK(I2S_CONF_REG(0), I2S_RX_RESET | I2S_TX_RESET | I2S_TX_FIFO_RESET | I2S_RX_FIFO_RESET);
    CLEAR_PERI_REG_MASK(I2S_CONF_REG(0), I2S_RX_RESET | I2S_TX_RESET | I2S_TX_FIFO_RESET | I2S_RX_FIFO_RESET);

    //Set desc addr
    CLEAR_PERI_REG_MASK(I2S_OUT_LINK_REG(0), I2S_OUTLINK_ADDR);
    SET_PERI_REG_MASK(I2S_OUT_LINK_REG(0), ((uint32_t)(&dmaDesc[0]))&I2S_OUTLINK_ADDR);
    CLEAR_PERI_REG_MASK(I2S_IN_LINK_REG(0), I2S_INLINK_ADDR);
    SET_PERI_REG_MASK(I2S_IN_LINK_REG(0), ((uint32_t)(&dmaDesc[1]))&I2S_INLINK_ADDR);

    SET_PERI_REG_MASK(I2S_FIFO_CONF_REG(0), I2S_DSCR_EN); //Enable DMA mode

    WRITE_PERI_REG(I2S_RXEOF_NUM_REG(0), len);

    //Enable and configure DMA
    WRITE_PERI_REG(I2S_LC_CONF_REG(0), I2S_OUT_DATA_BURST_EN  |
                   I2S_OUT_EOF_MODE | I2S_OUTDSCR_BURST_EN | I2S_OUT_DATA_BURST_EN |
                   I2S_INDSCR_BURST_EN | I2S_MEM_TRANS_EN);

    //Start transmission
    SET_PERI_REG_MASK(I2S_OUT_LINK_REG(0), I2S_OUTLINK_START);
    SET_PERI_REG_MASK(I2S_IN_LINK_REG(0), I2S_INLINK_START);

    SET_PERI_REG_MASK(I2S_CONF_REG(0), I2S_TX_START | I2S_RX_START);
    //Clear int flags
    WRITE_PERI_REG(I2S_INT_CLR_REG(0), 0xFFFFFFFF);
}