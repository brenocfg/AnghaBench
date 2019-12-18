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
 int /*<<< orphan*/  DPORT_CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_I2S0_CLK_EN ; 
 int /*<<< orphan*/  DPORT_I2S0_RST ; 
 int /*<<< orphan*/  DPORT_PERIP_CLK_EN_REG ; 
 int /*<<< orphan*/  DPORT_PERIP_RST_EN_REG ; 
 int /*<<< orphan*/  DPORT_SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int I2S_CAMERA_EN ; 
 int /*<<< orphan*/  I2S_CONF2_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2S_CONF_REG (int /*<<< orphan*/ ) ; 
 int I2S_DATA_ENABLE ; 
 int I2S_DATA_ENABLE_TEST_EN ; 
 int I2S_LCD_EN ; 
 int I2S_RX_RESET ; 
 int I2S_RX_START ; 
 int /*<<< orphan*/  PERIPH_I2S0_MODULE ; 
 int /*<<< orphan*/  RTC_CNTL_DTEST_RTC ; 
 int /*<<< orphan*/  RTC_CNTL_DTEST_RTC_S ; 
 int RTC_CNTL_ENT_RTC ; 
 int /*<<< orphan*/  RTC_CNTL_TEST_MUX_REG ; 
 int /*<<< orphan*/  SENS_FORCE_XPD_SAR ; 
 int /*<<< orphan*/  SENS_FORCE_XPD_SAR_S ; 
 int SENS_SAR1_DIG_FORCE ; 
 int SENS_SAR2_DIG_FORCE ; 
 int SENS_SAR2_EN_TEST ; 
 int /*<<< orphan*/  SENS_SAR_MEAS1_MUX_REG ; 
 int /*<<< orphan*/  SENS_SAR_MEAS2_CTRL1_REG ; 
 int /*<<< orphan*/  SENS_SAR_MEAS_WAIT2_REG ; 
 int /*<<< orphan*/  SENS_SAR_POWER_XPD_SAR_REG ; 
 int /*<<< orphan*/  SENS_SAR_READ_CTRL2_REG ; 
 int /*<<< orphan*/  SENS_SAR_READ_CTRL_REG ; 
 int /*<<< orphan*/  SENS_SAR_START_FORCE_REG ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYSCON_SARADC_CTRL_REG ; 
 int SYSCON_SARADC_DATA_TO_I2S ; 
 int /*<<< orphan*/  SYSCON_SARADC_FSM_REG ; 
 int SYSCON_SARADC_SAR2_MUX ; 
 int SYSCON_SARADC_SAR_SEL ; 
 int /*<<< orphan*/  SYSCON_SARADC_START_WAIT ; 
 int /*<<< orphan*/  SYSCON_SARADC_START_WAIT_S ; 
 int /*<<< orphan*/  periph_module_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  periph_module_reset (int /*<<< orphan*/ ) ; 

void bootloader_random_disable(void)
{
    /* Reset some i2s configuration (possibly redundant as we reset entire
       I2S peripheral further down). */
    CLEAR_PERI_REG_MASK(I2S_CONF_REG(0), I2S_RX_START);
    SET_PERI_REG_MASK(I2S_CONF_REG(0), I2S_RX_RESET);
    CLEAR_PERI_REG_MASK(I2S_CONF_REG(0), I2S_RX_RESET);
    CLEAR_PERI_REG_MASK(I2S_CONF2_REG(0), I2S_CAMERA_EN);
    CLEAR_PERI_REG_MASK(I2S_CONF2_REG(0), I2S_LCD_EN);
    CLEAR_PERI_REG_MASK(I2S_CONF2_REG(0), I2S_DATA_ENABLE_TEST_EN);
    CLEAR_PERI_REG_MASK(I2S_CONF2_REG(0), I2S_DATA_ENABLE);

    /* Disable i2s clock */
#ifdef BOOTLOADER_BUILD
    DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2S0_CLK_EN);
#else
    periph_module_disable(PERIPH_I2S0_MODULE);
#endif // BOOTLOADER_BUILD

    /* Restore SYSCON mode registers */
#if CONFIG_IDF_TARGET_ESP32
    CLEAR_PERI_REG_MASK(SENS_SAR_READ_CTRL_REG, SENS_SAR1_DIG_FORCE);
    CLEAR_PERI_REG_MASK(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_DIG_FORCE);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    CLEAR_PERI_REG_MASK(SENS_SAR_MEAS1_MUX_REG, SENS_SAR1_DIG_FORCE);
#endif

#if CONFIG_IDF_TARGET_ESP32
    /* Restore SAR ADC mode */
    CLEAR_PERI_REG_MASK(SENS_SAR_START_FORCE_REG, SENS_SAR2_EN_TEST);
    CLEAR_PERI_REG_MASK(SYSCON_SARADC_CTRL_REG, SYSCON_SARADC_SAR2_MUX
                        | SYSCON_SARADC_SAR_SEL | SYSCON_SARADC_DATA_TO_I2S);
    SET_PERI_REG_BITS(SENS_SAR_MEAS_WAIT2_REG, SENS_FORCE_XPD_SAR, 0, SENS_FORCE_XPD_SAR_S);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    CLEAR_PERI_REG_MASK(SENS_SAR_MEAS2_CTRL1_REG, SENS_SAR2_EN_TEST);
    CLEAR_PERI_REG_MASK(SYSCON_SARADC_CTRL_REG, SYSCON_SARADC_SAR_SEL | SYSCON_SARADC_DATA_TO_I2S);
    SET_PERI_REG_BITS(SENS_SAR_POWER_XPD_SAR_REG, SENS_FORCE_XPD_SAR, 0, SENS_FORCE_XPD_SAR_S);
#endif

#if CONFIG_IDF_TARGET_ESP32
    SET_PERI_REG_BITS(SYSCON_SARADC_FSM_REG, SYSCON_SARADC_START_WAIT, 8, SYSCON_SARADC_START_WAIT_S);
#endif

    /* Reset i2s peripheral */
#ifdef BOOTLOADER_BUILD
    DPORT_SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2S0_RST);
    DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2S0_RST);
#else
    periph_module_reset(PERIPH_I2S0_MODULE);
#endif

    /* Disable pull supply voltage to SAR ADC */
    CLEAR_PERI_REG_MASK(RTC_CNTL_TEST_MUX_REG, RTC_CNTL_ENT_RTC);
    SET_PERI_REG_BITS(RTC_CNTL_TEST_MUX_REG, RTC_CNTL_DTEST_RTC, 0, RTC_CNTL_DTEST_RTC_S);
}