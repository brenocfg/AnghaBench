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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_BT_LPCK_DIV_A ; 
 int /*<<< orphan*/  DPORT_BT_LPCK_DIV_B ; 
 int /*<<< orphan*/  DPORT_BT_LPCK_DIV_FRAC_REG ; 
 int /*<<< orphan*/  DPORT_BT_LPCK_DIV_INT_REG ; 
 int /*<<< orphan*/  DPORT_BT_LPCK_DIV_NUM ; 
 int /*<<< orphan*/  DPORT_LPCLK_RTC_EN ; 
 int /*<<< orphan*/  DPORT_LPCLK_SEL_8M ; 
 int /*<<< orphan*/  DPORT_LPCLK_SEL_XTAL ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_CLK8M_EN ; 
 int /*<<< orphan*/  RTC_CNTL_ENCKINIT_XTAL_32K ; 
 int /*<<< orphan*/  RTC_CNTL_EXT_XTL_CONF_REG ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTAL_32K_BOOTSTRAP_DAC_VAL ; 
 int /*<<< orphan*/  XTAL_32K_BOOTSTRAP_DBIAS_VAL ; 
 int /*<<< orphan*/  XTAL_32K_BOOTSTRAP_DRES_VAL ; 
 int /*<<< orphan*/  ets_delay_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_clk_32k_enable_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtc_clk_32k_bootstrap(uint32_t cycle)
{
    /* Config a clock to stimulate xtal, this clock is divided by a clock mux
     * The default selection of the clock mux is to use 8M, but it may not have enough accuracy compared with 40M xtal
     * This clock will be a pulse clk with a double frequency of 32.768k.
     * and then it will become a 32.768k clock with 50% duty cycle in RTC.
     * (40M / 32.768k) * 2 = 2441 + 13/32
     */
    REG_SET_FIELD(DPORT_BT_LPCK_DIV_INT_REG, DPORT_BT_LPCK_DIV_NUM, 2441);
    REG_SET_FIELD(DPORT_BT_LPCK_DIV_FRAC_REG, DPORT_BT_LPCK_DIV_A, 32);
    REG_SET_FIELD(DPORT_BT_LPCK_DIV_FRAC_REG, DPORT_BT_LPCK_DIV_B, 13);

    /* Enable clock mux with 40M */
    SET_PERI_REG_MASK(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_CLK8M_EN);
    CLEAR_PERI_REG_MASK(DPORT_BT_LPCK_DIV_FRAC_REG, DPORT_LPCLK_SEL_8M);
    SET_PERI_REG_MASK(DPORT_BT_LPCK_DIV_FRAC_REG, DPORT_LPCLK_SEL_XTAL);

    /* connect clock to RTC */
    SET_PERI_REG_MASK(DPORT_BT_LPCK_DIV_FRAC_REG, DPORT_LPCLK_RTC_EN);
    /* connect clock to analog */
    SET_PERI_REG_MASK(RTC_CNTL_EXT_XTL_CONF_REG, RTC_CNTL_ENCKINIT_XTAL_32K);

    /* Enable 32k xtal */
    rtc_clk_32k_enable_internal(XTAL_32K_BOOTSTRAP_DAC_VAL, XTAL_32K_BOOTSTRAP_DRES_VAL, XTAL_32K_BOOTSTRAP_DBIAS_VAL);

    /* wait 32k xtal to be stable. Need to find a better way */
    ets_delay_us(cycle);

    /* Close clock source */
    CLEAR_PERI_REG_MASK(DPORT_BT_LPCK_DIV_FRAC_REG, DPORT_LPCLK_SEL_XTAL);
    CLEAR_PERI_REG_MASK(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_CLK8M_EN);
    CLEAR_PERI_REG_MASK(RTC_CNTL_EXT_XTL_CONF_REG, RTC_CNTL_ENCKINIT_XTAL_32K);
    CLEAR_PERI_REG_MASK(DPORT_BT_LPCK_DIV_FRAC_REG, DPORT_LPCLK_RTC_EN);
}