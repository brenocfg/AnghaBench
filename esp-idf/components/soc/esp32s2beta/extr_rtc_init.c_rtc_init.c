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
typedef  int /*<<< orphan*/  rtc_sleep_pd_config_t ;
struct TYPE_3__ {int xtal_fpu; int bbpll_fpu; scalar_t__ cpu_waiti_clk_gate; scalar_t__ rtc_dboost_fpd; scalar_t__ pwrctl_init; scalar_t__ clkctl_init; int /*<<< orphan*/  ck8m_wait; int /*<<< orphan*/  pll_wait; } ;
typedef  TYPE_1__ rtc_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DG_WRAP_POWERUP_CYCLES ; 
 int /*<<< orphan*/  DG_WRAP_WAIT_CYCLES ; 
 int /*<<< orphan*/  DPORT_CPU_PER_CONF_REG ; 
 int DPORT_CPU_WAIT_MODE_FORCE_ON ; 
 int DPORT_LSLP_MEM_PD_MASK ; 
 int /*<<< orphan*/  DPORT_MEM_PD_MASK_REG ; 
 int DPORT_PRO_CACHE_MMU_MEM_FORCE_ON ; 
 int /*<<< orphan*/  DPORT_PRO_CACHE_MMU_POWER_CTRL_REG ; 
 int DPORT_PRO_DCACHE_TAG_MEM_FORCE_ON ; 
 int /*<<< orphan*/  DPORT_PRO_DCACHE_TAG_POWER_CTRL_REG ; 
 int DPORT_PRO_ICACHE_TAG_MEM_FORCE_ON ; 
 int /*<<< orphan*/  DPORT_PRO_ICACHE_TAG_POWER_CTRL_REG ; 
 int /*<<< orphan*/  DPORT_ROM_CTRL_0_REG ; 
 int /*<<< orphan*/  DPORT_ROM_FO ; 
 int /*<<< orphan*/  DPORT_SRAM_CTRL_0_REG ; 
 int /*<<< orphan*/  DPORT_SRAM_FO ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_ANA_CONF_REG ; 
 int RTC_CNTL_BBPLL_FORCE_PU ; 
 int RTC_CNTL_BBPLL_I2C_FORCE_PU ; 
 int RTC_CNTL_BB_I2C_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_BIAS_CONF_REG ; 
 int RTC_CNTL_BIAS_FORCE_NOSLEEP ; 
 int RTC_CNTL_BIAS_SLEEP_FOLW_8M ; 
 int RTC_CNTL_CK8M_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_CK8M_WAIT ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DBIAS_1V10 ; 
 int /*<<< orphan*/  RTC_CNTL_DBIAS_SLP ; 
 int /*<<< orphan*/  RTC_CNTL_DBIAS_WAK ; 
 int RTC_CNTL_DBOOST_FORCE_PD ; 
 int RTC_CNTL_DBOOST_FORCE_PU ; 
 int RTC_CNTL_DEC_HEARTBEAT_WIDTH ; 
 int RTC_CNTL_DG_PAD_AUTOHOLD_EN ; 
 int RTC_CNTL_DG_PAD_FORCE_NOISO ; 
 int RTC_CNTL_DG_PAD_FORCE_UNHOLD ; 
 int RTC_CNTL_DG_WRAP_FORCE_NOISO ; 
 int RTC_CNTL_DG_WRAP_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_DG_WRAP_POWERUP_TIMER ; 
 int /*<<< orphan*/  RTC_CNTL_DG_WRAP_WAIT_TIMER ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_ISO_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_PWC_REG ; 
 int RTC_CNTL_FORCE_NOISO ; 
 int RTC_CNTL_INC_HEARTBEAT_PERIOD ; 
 int RTC_CNTL_MEM_FORCE_NOISO ; 
 int RTC_CNTL_MEM_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_MIN_SLP_VAL ; 
 int /*<<< orphan*/  RTC_CNTL_MIN_SLP_VAL_MIN ; 
 int /*<<< orphan*/  RTC_CNTL_OPTIONS0_REG ; 
 int RTC_CNTL_PAD_AUTOHOLD_EN ; 
 int RTC_CNTL_PAD_FORCE_NOISO ; 
 int RTC_CNTL_PAD_FORCE_UNHOLD ; 
 int RTC_CNTL_PLLA_FORCE_PD ; 
 int RTC_CNTL_PLLA_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_PLL_BUF_WAIT ; 
 int /*<<< orphan*/  RTC_CNTL_POWERUP_TIMER ; 
 int RTC_CNTL_PVTMON_PU ; 
 int RTC_CNTL_PWC_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_PWC_REG ; 
 int /*<<< orphan*/  RTC_CNTL_REG ; 
 int RTC_CNTL_REGULATOR_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_RTCMEM_POWERUP_TIMER ; 
 int /*<<< orphan*/  RTC_CNTL_RTCMEM_WAIT_TIMER ; 
 int /*<<< orphan*/  RTC_CNTL_TIMER1_REG ; 
 int /*<<< orphan*/  RTC_CNTL_TIMER3_REG ; 
 int /*<<< orphan*/  RTC_CNTL_TIMER4_REG ; 
 int /*<<< orphan*/  RTC_CNTL_TIMER5_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WAIT_TIMER ; 
 int RTC_CNTL_WIFI_FORCE_NOISO ; 
 int RTC_CNTL_WIFI_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_WIFI_POWERUP_TIMER ; 
 int /*<<< orphan*/  RTC_CNTL_WIFI_WAIT_TIMER ; 
 int RTC_CNTL_XTL_FORCE_PU ; 
 int /*<<< orphan*/  RTC_MEM_POWERUP_CYCLES ; 
 int /*<<< orphan*/  RTC_MEM_WAIT_CYCLES ; 
 int /*<<< orphan*/  RTC_POWERUP_CYCLES ; 
 int /*<<< orphan*/  RTC_SLEEP_PD_CONFIG_ALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_WAIT_CYCLES ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int SPI_MEM_CLK_EN ; 
 int /*<<< orphan*/  SPI_MEM_CLOCK_GATE_REG (int) ; 
 int /*<<< orphan*/  WIFI_POWERUP_CYCLES ; 
 int /*<<< orphan*/  WIFI_WAIT_CYCLES ; 
 int /*<<< orphan*/  rtc_clk_set_xtal_wait () ; 
 int /*<<< orphan*/  rtc_sleep_pd (int /*<<< orphan*/ ) ; 

void rtc_init(rtc_config_t cfg)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_ANA_CONF_REG, RTC_CNTL_PVTMON_PU);
    rtc_clk_set_xtal_wait();
    REG_SET_FIELD(RTC_CNTL_TIMER1_REG, RTC_CNTL_PLL_BUF_WAIT, cfg.pll_wait);
    REG_SET_FIELD(RTC_CNTL_TIMER1_REG, RTC_CNTL_CK8M_WAIT, cfg.ck8m_wait);

    /* Moved from rtc sleep to rtc init to save sleep function running time */
    // set shortest possible sleep time limit
    REG_SET_FIELD(RTC_CNTL_TIMER5_REG, RTC_CNTL_MIN_SLP_VAL, RTC_CNTL_MIN_SLP_VAL_MIN);

    /* This power domian removed
    * set rom&ram timer
    * REG_SET_FIELD(RTC_CNTL_TIMER3_REG, RTC_CNTL_ROM_RAM_POWERUP_TIMER, ROM_RAM_POWERUP_CYCLES);
    * REG_SET_FIELD(RTC_CNTL_TIMER3_REG, RTC_CNTL_ROM_RAM_WAIT_TIMER, ROM_RAM_WAIT_CYCLES);
    */
    // set wifi timer
    REG_SET_FIELD(RTC_CNTL_TIMER3_REG, RTC_CNTL_WIFI_POWERUP_TIMER, WIFI_POWERUP_CYCLES);
    REG_SET_FIELD(RTC_CNTL_TIMER3_REG, RTC_CNTL_WIFI_WAIT_TIMER, WIFI_WAIT_CYCLES);
    // set rtc peri timer
    REG_SET_FIELD(RTC_CNTL_TIMER4_REG, RTC_CNTL_POWERUP_TIMER, RTC_POWERUP_CYCLES);
    REG_SET_FIELD(RTC_CNTL_TIMER4_REG, RTC_CNTL_WAIT_TIMER, RTC_WAIT_CYCLES);
    // set digital wrap timer
    REG_SET_FIELD(RTC_CNTL_TIMER4_REG, RTC_CNTL_DG_WRAP_POWERUP_TIMER, DG_WRAP_POWERUP_CYCLES);
    REG_SET_FIELD(RTC_CNTL_TIMER4_REG, RTC_CNTL_DG_WRAP_WAIT_TIMER, DG_WRAP_WAIT_CYCLES);
    // set rtc memory timer
    REG_SET_FIELD(RTC_CNTL_TIMER5_REG, RTC_CNTL_RTCMEM_POWERUP_TIMER, RTC_MEM_POWERUP_CYCLES);
    REG_SET_FIELD(RTC_CNTL_TIMER5_REG, RTC_CNTL_RTCMEM_WAIT_TIMER, RTC_MEM_WAIT_CYCLES);

    SET_PERI_REG_MASK(RTC_CNTL_BIAS_CONF_REG,
            RTC_CNTL_DEC_HEARTBEAT_WIDTH | RTC_CNTL_INC_HEARTBEAT_PERIOD);

    /* Reset RTC bias to default value (needed if waking up from deep sleep) */
    REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DBIAS_WAK, RTC_CNTL_DBIAS_1V10);
    REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DBIAS_SLP, RTC_CNTL_DBIAS_1V10);

    if (cfg.clkctl_init) {
        //clear CMMU clock force on
        CLEAR_PERI_REG_MASK(DPORT_PRO_CACHE_MMU_POWER_CTRL_REG, DPORT_PRO_CACHE_MMU_MEM_FORCE_ON);
        //clear rom clock force on
        REG_SET_FIELD(DPORT_ROM_CTRL_0_REG, DPORT_ROM_FO, 0);
        //clear sram clock force on
        REG_SET_FIELD(DPORT_SRAM_CTRL_0_REG, DPORT_SRAM_FO, 0);
        //clear tag clock force on
        CLEAR_PERI_REG_MASK(DPORT_PRO_DCACHE_TAG_POWER_CTRL_REG, DPORT_PRO_DCACHE_TAG_MEM_FORCE_ON);
        CLEAR_PERI_REG_MASK(DPORT_PRO_ICACHE_TAG_POWER_CTRL_REG, DPORT_PRO_ICACHE_TAG_MEM_FORCE_ON);
        //clear register clock force on
        CLEAR_PERI_REG_MASK(SPI_MEM_CLOCK_GATE_REG(0), SPI_MEM_CLK_EN);
        CLEAR_PERI_REG_MASK(SPI_MEM_CLOCK_GATE_REG(1), SPI_MEM_CLK_EN);
    }
    if (cfg.pwrctl_init) {
        CLEAR_PERI_REG_MASK(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_CK8M_FORCE_PU);
        //cancel xtal force pu if no need to force power up
        //cannot cancel xtal force pu if pll is force power on
        if (!(cfg.xtal_fpu | cfg.bbpll_fpu)) {
            CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_XTL_FORCE_PU);
        } else {
            SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_XTL_FORCE_PU);
        }
        // cancel BIAS force pu
        // CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_CORE_FORCE_PU);
        // CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_I2C_FORCE_PU);
        CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_FORCE_NOSLEEP);
        // bias follow 8M
        // SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_CORE_FOLW_8M);
        // SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_I2C_FOLW_8M);
        SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_SLEEP_FOLW_8M);
        // CLEAR APLL close
        CLEAR_PERI_REG_MASK(RTC_CNTL_ANA_CONF_REG, RTC_CNTL_PLLA_FORCE_PU);
        SET_PERI_REG_MASK(RTC_CNTL_ANA_CONF_REG, RTC_CNTL_PLLA_FORCE_PD);

        //cancel bbpll force pu if setting no force power up
        if (!cfg.bbpll_fpu) {
            CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BBPLL_FORCE_PU);
            CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BBPLL_I2C_FORCE_PU);
            CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BB_I2C_FORCE_PU);
        } else {
            SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BBPLL_FORCE_PU);
            SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BBPLL_I2C_FORCE_PU);
            SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BB_I2C_FORCE_PU);
        }
        //cancel RTC REG force PU
        CLEAR_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_PWC_FORCE_PU);
        CLEAR_PERI_REG_MASK(RTC_CNTL_REG, RTC_CNTL_REGULATOR_FORCE_PU);
        CLEAR_PERI_REG_MASK(RTC_CNTL_REG, RTC_CNTL_DBOOST_FORCE_PU);

        //combine two rtc memory options
        CLEAR_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_MEM_FORCE_PU);
        CLEAR_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_MEM_FORCE_NOISO);

        if (cfg.rtc_dboost_fpd) {
            SET_PERI_REG_MASK(RTC_CNTL_REG, RTC_CNTL_DBOOST_FORCE_PD);
        } else {
            CLEAR_PERI_REG_MASK(RTC_CNTL_REG, RTC_CNTL_DBOOST_FORCE_PD);
        }
        //cancel digital pu force
        CLEAR_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_MEM_FORCE_PU);

        /* If this mask is enabled, all soc memories cannot enter power down mode */
        /* We should control soc memory power down mode from RTC, so we will not touch this register any more */
        CLEAR_PERI_REG_MASK(DPORT_MEM_PD_MASK_REG, DPORT_LSLP_MEM_PD_MASK);
        /* If this pd_cfg is set to 1, all memory won't enter low power mode during light sleep */
        /* If this pd_cfg is set to 0, all memory will enter low power mode during light sleep */
        rtc_sleep_pd_config_t pd_cfg = RTC_SLEEP_PD_CONFIG_ALL(0);
        rtc_sleep_pd(pd_cfg);

        CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_PWC_REG, RTC_CNTL_DG_WRAP_FORCE_PU);
        CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_PWC_REG, RTC_CNTL_WIFI_FORCE_PU);
        // ROM_RAM power domain is removed
        // CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_PWC_REG, RTC_CNTL_CPU_ROM_RAM_FORCE_PU);
        CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_WRAP_FORCE_NOISO);
        CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_WIFI_FORCE_NOISO);
        // CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_CPU_ROM_RAM_FORCE_NOISO);
        CLEAR_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_FORCE_NOISO);
        //cancel digital PADS force no iso
        if (cfg.cpu_waiti_clk_gate){
            CLEAR_PERI_REG_MASK(DPORT_CPU_PER_CONF_REG, DPORT_CPU_WAIT_MODE_FORCE_ON);
        }
        else{
            SET_PERI_REG_MASK(DPORT_CPU_PER_CONF_REG, DPORT_CPU_WAIT_MODE_FORCE_ON);
        }
        /*if DPORT_CPU_WAIT_MODE_FORCE_ON == 0 , the cpu clk will be closed when cpu enter WAITI mode*/

#ifdef CONFIG_CHIP_IS_ESP32
        CLEAR_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_PAD_FORCE_UNHOLD);
        CLEAR_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_PAD_FORCE_NOISO);
#endif
        CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_UNHOLD);
        CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_NOISO);
#ifdef CONFIG_CHIP_IS_ESP32
        SET_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_PAD_AUTOHOLD_EN);
        SET_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_DG_PAD_AUTOHOLD_EN);
#endif
    }
}