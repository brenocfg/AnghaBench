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
typedef  int rtc_xtal_freq_t ;
typedef  scalar_t__ rtc_cpu_freq_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int DIG_DBIAS_240M ; 
 int DIG_DBIAS_2M ; 
 int DIG_DBIAS_80M_160M ; 
 int DIG_DBIAS_XTAL ; 
 int /*<<< orphan*/  DPORT_CPUPERIOD_SEL ; 
 int /*<<< orphan*/  DPORT_CPU_PER_CONF_REG ; 
 int /*<<< orphan*/  DPORT_REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MHZ ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RTC_CNTL_BBPLL_FORCE_PD ; 
 int RTC_CNTL_BBPLL_I2C_FORCE_PD ; 
 int RTC_CNTL_BB_I2C_FORCE_PD ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_DBIAS_WAK ; 
 int /*<<< orphan*/  RTC_CNTL_OPTIONS0_REG ; 
 int /*<<< orphan*/  RTC_CNTL_REG ; 
 scalar_t__ RTC_CPU_320M_160M ; 
 scalar_t__ RTC_CPU_320M_80M ; 
 scalar_t__ RTC_CPU_FREQ_160M ; 
 scalar_t__ RTC_CPU_FREQ_240M ; 
 scalar_t__ RTC_CPU_FREQ_2M ; 
 scalar_t__ RTC_CPU_FREQ_80M ; 
 scalar_t__ RTC_CPU_FREQ_XTAL ; 
 int /*<<< orphan*/  RTC_PLL_320M ; 
 int /*<<< orphan*/  RTC_PLL_480M ; 
 int /*<<< orphan*/  RTC_PLL_NONE ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYSCON_PRE_DIV_CNT ; 
 int /*<<< orphan*/  SYSCON_SOC_CLK_SEL ; 
 int SYSCON_SOC_CLK_SEL_PLL ; 
 int SYSCON_SOC_CLK_SEL_XTL ; 
 int /*<<< orphan*/  SYSCON_SYSCLK_CONF_REG ; 
 int /*<<< orphan*/  ets_update_cpu_frequency (int) ; 
 int /*<<< orphan*/  rtc_clk_apb_freq_update (int) ; 
 int /*<<< orphan*/  rtc_clk_bbpll_set (int,int /*<<< orphan*/ ) ; 
 int rtc_clk_xtal_freq_get () ; 
 scalar_t__ s_cur_freq ; 
 int /*<<< orphan*/  s_cur_pll ; 

void rtc_clk_cpu_freq_set(rtc_cpu_freq_t cpu_freq)
{
    rtc_xtal_freq_t xtal_freq = rtc_clk_xtal_freq_get();
    /* Switch CPU to XTAL frequency first */
    REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_XTAL);
    REG_SET_FIELD(SYSCON_SYSCLK_CONF_REG, SYSCON_SOC_CLK_SEL, SYSCON_SOC_CLK_SEL_XTL);
    REG_SET_FIELD(SYSCON_SYSCLK_CONF_REG, SYSCON_PRE_DIV_CNT, 0);
    ets_update_cpu_frequency(xtal_freq);
    /* Frequency switch is synchronized to SLOW_CLK cycle. Wait until the switch
     * is complete before disabling the PLL.
     */
    /* register SOC_CLK_SEL is moved to APB domain, so this delay is not neccessary any more */
    //rtc_clk_wait_for_slow_cycle();

    DPORT_REG_SET_FIELD(DPORT_CPU_PER_CONF_REG, DPORT_CPUPERIOD_SEL, 0);

    /* BBPLL force power down won't affect force power up setting */
    SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG,
            RTC_CNTL_BB_I2C_FORCE_PD | RTC_CNTL_BBPLL_FORCE_PD |
            RTC_CNTL_BBPLL_I2C_FORCE_PD);
    s_cur_pll = RTC_PLL_NONE;
    rtc_clk_apb_freq_update(xtal_freq * MHZ);

    /* is APLL under force power down? */
    /* may need equivalent function
    uint32_t apll_fpd = REG_GET_FIELD(RTC_CNTL_ANA_CONF_REG, RTC_CNTL_PLLA_FORCE_PD);

     * if (apll_fpd) {
     *   SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_I2C_FORCE_PD);
     * }
    */

    /* now switch to the desired frequency */
    if (cpu_freq == RTC_CPU_FREQ_XTAL) {
        /* already at XTAL, nothing to do */
    } else if (cpu_freq == RTC_CPU_FREQ_2M) {
        /* set up divider to produce 2MHz from XTAL */
        REG_SET_FIELD(SYSCON_SYSCLK_CONF_REG, SYSCON_PRE_DIV_CNT, (xtal_freq / 2) - 1);
        ets_update_cpu_frequency(2);
        rtc_clk_apb_freq_update(2 * MHZ);
        /* lower the voltage */
        REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_2M);
    } else {
        /* use PLL as clock source */
        CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG,
                RTC_CNTL_BB_I2C_FORCE_PD |
                RTC_CNTL_BBPLL_FORCE_PD | RTC_CNTL_BBPLL_I2C_FORCE_PD);
        if (cpu_freq > RTC_CPU_FREQ_2M) {
            rtc_clk_bbpll_set(xtal_freq, RTC_PLL_320M);
            s_cur_pll = RTC_PLL_320M;
        } else {
            rtc_clk_bbpll_set(xtal_freq, RTC_PLL_480M);
            s_cur_pll = RTC_PLL_480M;
        }

        if ((cpu_freq == RTC_CPU_FREQ_80M) || (cpu_freq == RTC_CPU_320M_80M)) {
            REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_80M_160M);
            DPORT_REG_SET_FIELD(DPORT_CPU_PER_CONF_REG, DPORT_CPUPERIOD_SEL, 0);
            ets_update_cpu_frequency(80);
        } else if ((cpu_freq == RTC_CPU_FREQ_160M) || (cpu_freq == RTC_CPU_320M_160M)) {
            REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_80M_160M);
            DPORT_REG_SET_FIELD(DPORT_CPU_PER_CONF_REG, DPORT_CPUPERIOD_SEL, 1);
            ets_update_cpu_frequency(160);
        } else if (cpu_freq == RTC_CPU_FREQ_240M) {
            REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_240M);
            DPORT_REG_SET_FIELD(DPORT_CPU_PER_CONF_REG, DPORT_CPUPERIOD_SEL, 2);
            ets_update_cpu_frequency(240);
        }
        REG_SET_FIELD(SYSCON_SYSCLK_CONF_REG, SYSCON_SOC_CLK_SEL, SYSCON_SOC_CLK_SEL_PLL);
        //rtc_clk_wait_for_slow_cycle();
        rtc_clk_apb_freq_update(80 * MHZ);
    }
    s_cur_freq = cpu_freq;
}