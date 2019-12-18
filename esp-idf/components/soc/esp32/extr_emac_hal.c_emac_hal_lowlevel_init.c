#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_5__* ext_regs; } ;
typedef  TYPE_6__ emac_hal_context_t ;
struct TYPE_11__ {scalar_t__ h_div_num; scalar_t__ div_num; } ;
struct TYPE_10__ {int clk_sel; } ;
struct TYPE_9__ {int mii_clk_rx_en; int mii_clk_tx_en; int ext_en; int int_en; } ;
struct TYPE_8__ {int phy_intf_sel; } ;
struct TYPE_12__ {TYPE_4__ ex_clkout_conf; TYPE_3__ ex_oscclk_conf; TYPE_2__ ex_clk_ctrl; TYPE_1__ ex_phyinf_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_GPIO0_CLK_OUT1 ; 
 int /*<<< orphan*/  FUNC_GPIO0_EMAC_TX_CLK ; 
 int /*<<< orphan*/  FUNC_GPIO16_EMAC_CLK_OUT ; 
 int /*<<< orphan*/  FUNC_GPIO17_EMAC_CLK_OUT_180 ; 
 int /*<<< orphan*/  FUNC_GPIO19_EMAC_TXD0 ; 
 int /*<<< orphan*/  FUNC_GPIO21_EMAC_TX_EN ; 
 int /*<<< orphan*/  FUNC_GPIO22_EMAC_TXD1 ; 
 int /*<<< orphan*/  FUNC_GPIO25_EMAC_RXD0 ; 
 int /*<<< orphan*/  FUNC_GPIO26_EMAC_RXD1 ; 
 int /*<<< orphan*/  FUNC_GPIO27_EMAC_RX_DV ; 
 int /*<<< orphan*/ * GPIO_PIN_MUX_REG ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO0_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO16_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO17_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO19_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO21_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO22_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO25_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO26_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO27_U ; 
 int /*<<< orphan*/  PIN_CTRL ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIN_INPUT_DISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIN_INPUT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emac_config_apll_clock () ; 

void emac_hal_lowlevel_init(emac_hal_context_t *hal)
{
    /* GPIO configuration */
    /* TX_EN to GPIO21 */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO21_U, FUNC_GPIO21_EMAC_TX_EN);
    PIN_INPUT_DISABLE(GPIO_PIN_MUX_REG[21]);
    /* TXD0 to GPIO19 */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO19_U, FUNC_GPIO19_EMAC_TXD0);
    PIN_INPUT_DISABLE(GPIO_PIN_MUX_REG[19]);
    /* TXD1 to GPIO22 */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO22_U, FUNC_GPIO22_EMAC_TXD1);
    PIN_INPUT_DISABLE(GPIO_PIN_MUX_REG[22]);
    /* RXD0 to GPIO25 */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO25_U, FUNC_GPIO25_EMAC_RXD0);
    PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[25]);
    /* RXD1 to GPIO26 */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO26_U, FUNC_GPIO26_EMAC_RXD1);
    PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[26]);
    /* CRS_DV to GPIO27 */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO27_U, FUNC_GPIO27_EMAC_RX_DV);
    PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[27]);
#if CONFIG_ETH_RMII_CLK_INPUT
#if CONFIG_ETH_RMII_CLK_IN_GPIO == 0
    /* RMII clock (50MHz) input to GPIO0 */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_EMAC_TX_CLK);
    PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[0]);
#else
#error "ESP32 EMAC only support input RMII clock to GPIO0"
#endif
#endif
#if CONFIG_ETH_RMII_CLK_OUTPUT
#if CONFIG_ETH_RMII_CLK_OUTPUT_GPIO0
    /* APLL clock output to GPIO0 (must be configured to 50MHz!) */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
    PIN_INPUT_DISABLE(GPIO_PIN_MUX_REG[0]);
#elif CONFIG_ETH_RMII_CLK_OUT_GPIO == 16
    /* RMII CLK (50MHz) output to GPIO16 */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO16_U, FUNC_GPIO16_EMAC_CLK_OUT);
    PIN_INPUT_DISABLE(GPIO_PIN_MUX_REG[16]);
#elif CONFIG_ETH_RMII_CLK_OUT_GPIO == 17
    /* RMII CLK (50MHz) output to GPIO17 */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO17_U, FUNC_GPIO17_EMAC_CLK_OUT_180);
    PIN_INPUT_DISABLE(GPIO_PIN_MUX_REG[17]);
#endif
#endif // CONFIG_ETH_RMII_CLK_OUTPUT
    /* Clock configuration */
#if CONFIG_ETH_PHY_INTERFACE_MII
    hal->ext_regs->ex_phyinf_conf.phy_intf_sel = 0;
    hal->ext_regs->ex_clk_ctrl.mii_clk_rx_en = 1;
    hal->ext_regs->ex_clk_ctrl.mii_clk_tx_en = 1;
#elif CONFIG_ETH_PHY_INTERFACE_RMII
    hal->ext_regs->ex_phyinf_conf.phy_intf_sel = 4;
#if CONFIG_ETH_RMII_CLK_INPUT
    hal->ext_regs->ex_clk_ctrl.ext_en = 1;
    hal->ext_regs->ex_clk_ctrl.int_en = 0;
    hal->ext_regs->ex_oscclk_conf.clk_sel = 1;
#elif CONFIG_ETH_RMII_CLK_OUTPUT
    hal->ext_regs->ex_clk_ctrl.ext_en = 0;
    hal->ext_regs->ex_clk_ctrl.int_en = 1;
    hal->ext_regs->ex_oscclk_conf.clk_sel = 0;
    emac_config_apll_clock();
    hal->ext_regs->ex_clkout_conf.div_num = 0;
    hal->ext_regs->ex_clkout_conf.h_div_num = 0;
#if CONFIG_ETH_RMII_CLK_OUTPUT_GPIO0
    /* Choose the APLL clock to output on GPIO */
    REG_WRITE(PIN_CTRL, 6);
#endif // CONFIG_RMII_CLK_OUTPUT_GPIO0
#endif // CONFIG_ETH_RMII_CLK_INPUT
#endif // CONFIG_ETH_PHY_INTERFACE_MII
}