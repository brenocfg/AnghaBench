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
 int /*<<< orphan*/  RTC_IO_DAC_XTAL_32K ; 
 int /*<<< orphan*/  RTC_IO_DBIAS_XTAL_32K ; 
 int /*<<< orphan*/  RTC_IO_DRES_XTAL_32K ; 
 int /*<<< orphan*/  RTC_IO_TOUCH_CFG_REG ; 
 int /*<<< orphan*/  RTC_IO_TOUCH_PAD8_DAC ; 
 int /*<<< orphan*/  RTC_IO_TOUCH_PAD8_DAC_S ; 
 int /*<<< orphan*/  RTC_IO_TOUCH_PAD8_REG ; 
 int /*<<< orphan*/  RTC_IO_TOUCH_PAD9_REG ; 
 int RTC_IO_TOUCH_PAD9_TIE_OPT_M ; 
 int RTC_IO_TOUCH_PAD9_XPD_M ; 
 int RTC_IO_TOUCH_XPD_BIAS_M ; 
 int RTC_IO_X32N_FUN_IE ; 
 int RTC_IO_X32N_MUX_SEL ; 
 int RTC_IO_X32N_RDE ; 
 int RTC_IO_X32N_RUE ; 
 int RTC_IO_X32P_FUN_IE ; 
 int RTC_IO_X32P_MUX_SEL ; 
 int RTC_IO_X32P_RDE ; 
 int RTC_IO_X32P_RUE ; 
 int RTC_IO_XPD_XTAL_32K_M ; 
 int /*<<< orphan*/  RTC_IO_XTAL_32K_PAD_REG ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtc_clk_32k_enable_common(int dac, int dres, int dbias)
{
    CLEAR_PERI_REG_MASK(RTC_IO_XTAL_32K_PAD_REG,
                        RTC_IO_X32P_RDE | RTC_IO_X32P_RUE | RTC_IO_X32N_RUE |
                        RTC_IO_X32N_RDE | RTC_IO_X32N_FUN_IE | RTC_IO_X32P_FUN_IE);
    SET_PERI_REG_MASK(RTC_IO_XTAL_32K_PAD_REG, RTC_IO_X32N_MUX_SEL | RTC_IO_X32P_MUX_SEL);
    /* Set the parameters of xtal
        dac --> current
        dres --> resistance
        dbias --> bais voltage
    */
    REG_SET_FIELD(RTC_IO_XTAL_32K_PAD_REG, RTC_IO_DAC_XTAL_32K, dac);
    REG_SET_FIELD(RTC_IO_XTAL_32K_PAD_REG, RTC_IO_DRES_XTAL_32K, dres);
    REG_SET_FIELD(RTC_IO_XTAL_32K_PAD_REG, RTC_IO_DBIAS_XTAL_32K, dbias);

#ifdef CONFIG_ESP32_RTC_EXT_CRYST_ADDIT_CURRENT
    /* TOUCH sensor can provide additional current to external XTAL.
       In some case, X32N and X32P PAD don't have enough drive capability to start XTAL */
    SET_PERI_REG_MASK(RTC_IO_TOUCH_CFG_REG, RTC_IO_TOUCH_XPD_BIAS_M);
    /* Tie PAD Touch8 to VDD
       NOTE: TOUCH8 and TOUCH9 register settings are reversed except for DAC, so we set RTC_IO_TOUCH_PAD9_REG here instead
    */
    SET_PERI_REG_MASK(RTC_IO_TOUCH_PAD9_REG, RTC_IO_TOUCH_PAD9_TIE_OPT_M);
    /* Set the current used to compensate TOUCH PAD8 */
    SET_PERI_REG_BITS(RTC_IO_TOUCH_PAD8_REG, RTC_IO_TOUCH_PAD8_DAC, 4, RTC_IO_TOUCH_PAD8_DAC_S);
    /* Power up TOUCH8
       So the Touch DAC start to drive some current from VDD to TOUCH8(which is also XTAL-N)
     */
    SET_PERI_REG_MASK(RTC_IO_TOUCH_PAD9_REG, RTC_IO_TOUCH_PAD9_XPD_M);
#endif // CONFIG_ESP32_RTC_EXT_CRYST_ADDIT_CURRENT
    /* Power up external xtal */
    SET_PERI_REG_MASK(RTC_IO_XTAL_32K_PAD_REG, RTC_IO_XPD_XTAL_32K_M);
}