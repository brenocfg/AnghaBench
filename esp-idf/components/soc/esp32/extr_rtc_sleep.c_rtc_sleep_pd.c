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
struct TYPE_3__ {int /*<<< orphan*/  fe_pd; int /*<<< orphan*/  nrx_pd; int /*<<< orphan*/  bb_pd; int /*<<< orphan*/  i2s_pd; int /*<<< orphan*/  cpu_pd; int /*<<< orphan*/  rtc_pd; int /*<<< orphan*/  dig_pd; } ;
typedef  TYPE_1__ rtc_sleep_pd_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  BBPD_CTRL ; 
 int /*<<< orphan*/  BB_DC_EST_FORCE_PU ; 
 int /*<<< orphan*/  BB_FFT_FORCE_PU ; 
 int /*<<< orphan*/  DPORT_LSLP_MEM_PD_MASK ; 
 int /*<<< orphan*/  DPORT_MEM_PD_MASK_REG ; 
 int /*<<< orphan*/  DPORT_REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FE2_TX_INF_FORCE_PU ; 
 int /*<<< orphan*/  FE2_TX_INTERP_CTRL ; 
 int /*<<< orphan*/  FE_GEN_CTRL ; 
 int /*<<< orphan*/  FE_IQ_EST_FORCE_PU ; 
 int /*<<< orphan*/  I2S_FIFO_FORCE_PU ; 
 int /*<<< orphan*/  I2S_PD_CONF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_PLC_MEM_FORCE_PU ; 
 int /*<<< orphan*/  NRXPD_CTRL ; 
 int /*<<< orphan*/  NRX_DEMAP_FORCE_PU ; 
 int /*<<< orphan*/  NRX_RX_ROT_FORCE_PU ; 
 int /*<<< orphan*/  NRX_VIT_FORCE_PU ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_PWC_REG ; 
 int /*<<< orphan*/  RTC_CNTL_FASTMEM_FORCE_LPU ; 
 int /*<<< orphan*/  RTC_CNTL_LSLP_MEM_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_PWC_REG ; 
 int /*<<< orphan*/  RTC_CNTL_SLOWMEM_FORCE_LPU ; 

__attribute__((used)) static void rtc_sleep_pd(rtc_sleep_pd_config_t cfg)
{
    REG_SET_FIELD(RTC_CNTL_DIG_PWC_REG, RTC_CNTL_LSLP_MEM_FORCE_PU, ~cfg.dig_pd);
    REG_SET_FIELD(RTC_CNTL_PWC_REG, RTC_CNTL_SLOWMEM_FORCE_LPU, ~cfg.rtc_pd);
    REG_SET_FIELD(RTC_CNTL_PWC_REG, RTC_CNTL_FASTMEM_FORCE_LPU, ~cfg.rtc_pd);
    DPORT_REG_SET_FIELD(DPORT_MEM_PD_MASK_REG, DPORT_LSLP_MEM_PD_MASK, ~cfg.cpu_pd);
    REG_SET_FIELD(I2S_PD_CONF_REG(0), I2S_PLC_MEM_FORCE_PU, ~cfg.i2s_pd);
    REG_SET_FIELD(I2S_PD_CONF_REG(0), I2S_FIFO_FORCE_PU, ~cfg.i2s_pd);
    REG_SET_FIELD(BBPD_CTRL, BB_FFT_FORCE_PU, ~cfg.bb_pd);
    REG_SET_FIELD(BBPD_CTRL, BB_DC_EST_FORCE_PU, ~cfg.bb_pd);
    REG_SET_FIELD(NRXPD_CTRL, NRX_RX_ROT_FORCE_PU, ~cfg.nrx_pd);
    REG_SET_FIELD(NRXPD_CTRL, NRX_VIT_FORCE_PU, ~cfg.nrx_pd);
    REG_SET_FIELD(NRXPD_CTRL, NRX_DEMAP_FORCE_PU, ~cfg.nrx_pd);
    REG_SET_FIELD(FE_GEN_CTRL, FE_IQ_EST_FORCE_PU, ~cfg.fe_pd);
    REG_SET_FIELD(FE2_TX_INTERP_CTRL, FE2_TX_INF_FORCE_PU, ~cfg.fe_pd);
}