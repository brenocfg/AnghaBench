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
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_CNTL_DAC_XTAL_32K ; 
 int /*<<< orphan*/  RTC_CNTL_DGM_XTAL_32K ; 
 int /*<<< orphan*/  RTC_CNTL_DRES_XTAL_32K ; 
 int /*<<< orphan*/  RTC_CNTL_EXT_XTL_CONF_REG ; 
 int RTC_CNTL_XTAL32K_XPD_FORCE ; 
 int RTC_IO_X32N_FUN_IE ; 
 int /*<<< orphan*/  RTC_IO_X32N_MUX_SEL ; 
 int RTC_IO_X32N_RDE ; 
 int RTC_IO_X32N_RUE ; 
 int RTC_IO_X32P_FUN_IE ; 
 int /*<<< orphan*/  RTC_IO_X32P_MUX_SEL ; 
 int RTC_IO_X32P_RDE ; 
 int RTC_IO_X32P_RUE ; 
 int /*<<< orphan*/  RTC_IO_XTAL_32N_PAD_REG ; 
 int /*<<< orphan*/  RTC_IO_XTAL_32P_PAD_REG ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtc_clk_32k_enable_internal(int dac, int dres, int dgm)
{
    SET_PERI_REG_MASK(RTC_IO_XTAL_32P_PAD_REG, RTC_IO_X32P_MUX_SEL);
    SET_PERI_REG_MASK(RTC_IO_XTAL_32N_PAD_REG, RTC_IO_X32N_MUX_SEL);
    CLEAR_PERI_REG_MASK(RTC_IO_XTAL_32P_PAD_REG, RTC_IO_X32P_RUE | RTC_IO_X32P_FUN_IE | RTC_IO_X32P_RDE);
    CLEAR_PERI_REG_MASK(RTC_IO_XTAL_32N_PAD_REG, RTC_IO_X32N_RUE | RTC_IO_X32N_FUN_IE | RTC_IO_X32N_RDE);
    REG_SET_FIELD(RTC_CNTL_EXT_XTL_CONF_REG, RTC_CNTL_DAC_XTAL_32K, dac);
    REG_SET_FIELD(RTC_CNTL_EXT_XTL_CONF_REG, RTC_CNTL_DRES_XTAL_32K, dres);
    REG_SET_FIELD(RTC_CNTL_EXT_XTL_CONF_REG, RTC_CNTL_DGM_XTAL_32K, dgm);

    /* Differential buffer option. May need to change */
    // CLEAR_PERI_REG_MASK(RTC_CNTL_EXT_XTL_CONF_REG, RTC_CNTL_DBUF_XTAL_32K);

    /* Clear xpd force to use xtal32k watch dog to control xtal pxd. default on */
    CLEAR_PERI_REG_MASK(RTC_CNTL_EXT_XTL_CONF_REG, RTC_CNTL_XTAL32K_XPD_FORCE);
}