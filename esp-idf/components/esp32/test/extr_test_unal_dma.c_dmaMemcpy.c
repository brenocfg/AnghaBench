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
struct TYPE_2__ {int length; int size; int owner; int eof; scalar_t__ empty; scalar_t__ offset; int /*<<< orphan*/ * buf; scalar_t__ sosf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPIO_ENABLE_W1TS_REG ; 
 int /*<<< orphan*/  GPIO_FUNC0_OUT_SEL_CFG_REG ; 
 int GPIO_FUNC0_OUT_SEL_S ; 
 int GPIO_FUNC11_OUT_INV_SEL ; 
 int /*<<< orphan*/  GPIO_FUNC11_OUT_SEL_CFG_REG ; 
 int /*<<< orphan*/  GPIO_FUNC16_OUT_SEL_CFG_REG ; 
 int /*<<< orphan*/  GPIO_FUNC17_OUT_SEL_CFG_REG ; 
 int /*<<< orphan*/  GPIO_FUNC18_OUT_SEL_CFG_REG ; 
 int /*<<< orphan*/  GPIO_FUNC19_OUT_SEL_CFG_REG ; 
 int /*<<< orphan*/  GPIO_FUNC20_OUT_SEL_CFG_REG ; 
 int /*<<< orphan*/  GPIO_FUNC26_OUT_SEL_CFG_REG ; 
 int /*<<< orphan*/  GPIO_FUNC2_OUT_SEL_CFG_REG ; 
 int /*<<< orphan*/  GPIO_FUNC5_OUT_SEL_CFG_REG ; 
 int I2S0O_WS_OUT_IDX ; 
 int I2S_AHBM_FIFO_RST ; 
 int I2S_AHBM_RST ; 
 int I2S_CLKA_ENA ; 
 int /*<<< orphan*/  I2S_CLKM_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_CLKM_DIV_A_S ; 
 int I2S_CLKM_DIV_B_S ; 
 int I2S_CLKM_DIV_NUM_S ; 
 int I2S_CLK_EN ; 
 int /*<<< orphan*/  I2S_CONF1_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_CONF2_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_CONF_CHAN_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_DSCR_EN ; 
 int /*<<< orphan*/  I2S_FIFO_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_INDSCR_BURST_EN ; 
 int I2S_INLINK_ADDR ; 
 int I2S_INLINK_START ; 
 int /*<<< orphan*/  I2S_INT_CLR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_INT_RAW_REG (int /*<<< orphan*/ ) ; 
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
 int I2S_RX_BCK_DIV_NUM_S ; 
 int I2S_RX_BITS_MOD_S ; 
 int I2S_RX_CHAN_MOD_S ; 
 int I2S_RX_DATA_NUM_S ; 
 int I2S_RX_FIFO_RESET ; 
 int I2S_RX_PCM_BYPASS ; 
 int I2S_RX_RESET ; 
 int I2S_RX_RIGHT_FIRST ; 
 int I2S_RX_START ; 
 int /*<<< orphan*/  I2S_SAMPLE_RATE_CONF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_STATE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_TIMING_REG (int /*<<< orphan*/ ) ; 
 int I2S_TX_BCK_DIV_NUM_S ; 
 int I2S_TX_BITS_MOD_S ; 
 int I2S_TX_CHAN_MOD_S ; 
 int I2S_TX_DATA_NUM_S ; 
 int I2S_TX_FIFO_RESET ; 
 int I2S_TX_FIFO_RESET_BACK ; 
 int I2S_TX_IDLE ; 
 int I2S_TX_PCM_BYPASS ; 
 int I2S_TX_REMPTY_INT_RAW ; 
 int I2S_TX_RESET ; 
 int I2S_TX_RIGHT_FIRST ; 
 int I2S_TX_START ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO0_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO16_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO17_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO18_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO19_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO20_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO26_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO2_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO5_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SD_CMD_U ; 
 int /*<<< orphan*/  PERIPH_I2S0_MODULE ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int) ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* dmaDesc ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmaMemcpy(void *in, void *out, int len)
{
    volatile int i;
    periph_module_enable(PERIPH_I2S0_MODULE);

    //Init pins to i2s functions
    SET_PERI_REG_MASK(GPIO_ENABLE_W1TS_REG, (1 << 11) | (1 << 3) | (1 << 0) | (1 << 2) | (1 << 5) | (1 << 16) | (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20)); //ENABLE GPIO oe_enable

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, 0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, 0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, 0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO16_U, 0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO17_U, 0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO18_U, 0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO19_U, 0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO20_U, 0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_CMD_U, 2); //11
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO26_U, 0); //RS

    WRITE_PERI_REG(GPIO_FUNC0_OUT_SEL_CFG_REG, (148 << GPIO_FUNC0_OUT_SEL_S));
    WRITE_PERI_REG(GPIO_FUNC2_OUT_SEL_CFG_REG, (149 << GPIO_FUNC0_OUT_SEL_S));
    WRITE_PERI_REG(GPIO_FUNC5_OUT_SEL_CFG_REG, (150 << GPIO_FUNC0_OUT_SEL_S));
    WRITE_PERI_REG(GPIO_FUNC16_OUT_SEL_CFG_REG, (151 << GPIO_FUNC0_OUT_SEL_S));
    WRITE_PERI_REG(GPIO_FUNC17_OUT_SEL_CFG_REG, (152 << GPIO_FUNC0_OUT_SEL_S));
    WRITE_PERI_REG(GPIO_FUNC18_OUT_SEL_CFG_REG, (153 << GPIO_FUNC0_OUT_SEL_S));
    WRITE_PERI_REG(GPIO_FUNC19_OUT_SEL_CFG_REG, (154 << GPIO_FUNC0_OUT_SEL_S));
    WRITE_PERI_REG(GPIO_FUNC20_OUT_SEL_CFG_REG, (155 << GPIO_FUNC0_OUT_SEL_S));
    WRITE_PERI_REG(GPIO_FUNC26_OUT_SEL_CFG_REG, (156 << GPIO_FUNC0_OUT_SEL_S)); //RS
    WRITE_PERI_REG(GPIO_FUNC11_OUT_SEL_CFG_REG, (I2S0O_WS_OUT_IDX << GPIO_FUNC0_OUT_SEL_S));
//  WRITE_PERI_REG(GPIO_FUNC11_OUT_SEL_CFG, (I2S0O_BCK_OUT_IDX<<GPIO_GPIO_FUNC0_OUT_SEL_S));

    //GPIO_SET_GPIO_FUNC11_OUT_INV_SEL(1); //old
    WRITE_PERI_REG(GPIO_FUNC11_OUT_SEL_CFG_REG, READ_PERI_REG(GPIO_FUNC11_OUT_SEL_CFG_REG) | GPIO_FUNC11_OUT_INV_SEL);

    //Reset I2S subsystem
    CLEAR_PERI_REG_MASK(I2S_CONF_REG(0), I2S_RX_RESET | I2S_TX_RESET);
    SET_PERI_REG_MASK(I2S_CONF_REG(0), I2S_RX_RESET | I2S_TX_RESET);
    CLEAR_PERI_REG_MASK(I2S_CONF_REG(0), I2S_RX_RESET | I2S_TX_RESET);

    WRITE_PERI_REG(I2S_CONF_REG(0), 0);//I2S_I2S_SIG_LOOPBACK);
    WRITE_PERI_REG(I2S_CONF2_REG(0), 0);

    WRITE_PERI_REG(I2S_SAMPLE_RATE_CONF_REG(0),
                   (16 << I2S_RX_BITS_MOD_S) |
                   (16 << I2S_TX_BITS_MOD_S) |
                   (1 << I2S_RX_BCK_DIV_NUM_S) |
                   (1 << I2S_TX_BCK_DIV_NUM_S));
    WRITE_PERI_REG(I2S_CLKM_CONF_REG(0),
                   I2S_CLKA_ENA | I2S_CLK_EN |
                   (1 << I2S_CLKM_DIV_A_S) |
                   (1 << I2S_CLKM_DIV_B_S) |
                   (1 << I2S_CLKM_DIV_NUM_S));
    WRITE_PERI_REG(I2S_FIFO_CONF_REG(0),
                   (32 << I2S_TX_DATA_NUM_S) |     //Low watermark for IRQ
                   (32 << I2S_RX_DATA_NUM_S));

    WRITE_PERI_REG(I2S_CONF1_REG(0), I2S_RX_PCM_BYPASS | I2S_TX_PCM_BYPASS);

    WRITE_PERI_REG(I2S_CONF_CHAN_REG(0), (2 << I2S_TX_CHAN_MOD_S) | (2 << I2S_RX_CHAN_MOD_S));

    //Invert WS to active-low
    SET_PERI_REG_MASK(I2S_CONF_REG(0), I2S_TX_RIGHT_FIRST | I2S_RX_RIGHT_FIRST);
    WRITE_PERI_REG(I2S_TIMING_REG(0), 0);

//--
    //Fill DMA descriptor
    dmaDesc[0].length = len;
    dmaDesc[0].size = len;
    dmaDesc[0].owner = 1;
    dmaDesc[0].sosf = 0;
    dmaDesc[0].buf = (uint8_t *)in;
    dmaDesc[0].offset = 0; //unused in hw
    dmaDesc[0].empty = 0;
    dmaDesc[0].eof = 1;
    dmaDesc[1].length = len;
    dmaDesc[1].size = len;
    dmaDesc[1].owner = 1;
    dmaDesc[1].sosf = 0;
    dmaDesc[1].buf = (uint8_t *)out;
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
//--
    //No need to finish if no DMA transfer going on
    if (!(READ_PERI_REG(I2S_FIFO_CONF_REG(0))&I2S_DSCR_EN)) {
        return;
    }

    //Wait till fifo done
    while (!(READ_PERI_REG(I2S_INT_RAW_REG(0))&I2S_TX_REMPTY_INT_RAW)) ;
    //Wait for last bytes to leave i2s xmit thing
    //ToDo: poll bit in next hw
    for (i = 0; i < (1 << 8); i++);
    while (!(READ_PERI_REG(I2S_STATE_REG(0))&I2S_TX_IDLE));

    //Reset I2S for next transfer
    CLEAR_PERI_REG_MASK(I2S_CONF_REG(0), I2S_TX_START | I2S_RX_START);
    CLEAR_PERI_REG_MASK(I2S_OUT_LINK_REG(0), I2S_OUTLINK_START | I2S_INLINK_START);

    SET_PERI_REG_MASK(I2S_CONF_REG(0), I2S_TX_RESET | I2S_TX_FIFO_RESET | I2S_RX_RESET | I2S_RX_FIFO_RESET);
    CLEAR_PERI_REG_MASK(I2S_CONF_REG(0), I2S_TX_RESET | I2S_TX_FIFO_RESET | I2S_RX_RESET | I2S_RX_FIFO_RESET);

//  for (i=0; i<(1<<8); i++);
    while ((READ_PERI_REG(I2S_STATE_REG(0))&I2S_TX_FIFO_RESET_BACK));

}