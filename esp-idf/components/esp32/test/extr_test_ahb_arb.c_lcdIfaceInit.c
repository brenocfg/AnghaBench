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
 int /*<<< orphan*/  I2S_FIFO_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_RX_BCK_DIV_NUM_S ; 
 int I2S_RX_BITS_MOD_S ; 
 int I2S_RX_CHAN_MOD_S ; 
 int I2S_RX_DATA_NUM_S ; 
 int I2S_RX_PCM_BYPASS ; 
 int I2S_RX_RESET ; 
 int I2S_RX_RIGHT_FIRST ; 
 int /*<<< orphan*/  I2S_SAMPLE_RATE_CONF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_TIMING_REG (int /*<<< orphan*/ ) ; 
 int I2S_TX_BCK_DIV_NUM_S ; 
 int I2S_TX_BITS_MOD_S ; 
 int I2S_TX_CHAN_MOD_S ; 
 int I2S_TX_DATA_NUM_S ; 
 int I2S_TX_PCM_BYPASS ; 
 int I2S_TX_RESET ; 
 int I2S_TX_RIGHT_FIRST ; 
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
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lcdIfaceInit(void)
{
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

    WRITE_PERI_REG(I2S_CONF_REG(0), 0);//I2S_SIG_LOOPBACK);
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
}