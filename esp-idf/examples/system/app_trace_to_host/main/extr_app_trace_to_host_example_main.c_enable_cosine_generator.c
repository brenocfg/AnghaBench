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
 int CW_FREQUENCY_STEP ; 
 int /*<<< orphan*/  DAC_CHANNEL_1 ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CLK_8M_DIV ; 
 int /*<<< orphan*/  RTC_CNTL_CK8M_DIV_SEL ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  SENS_DAC_CW_EN1_M ; 
 int /*<<< orphan*/  SENS_DAC_INV1 ; 
 int /*<<< orphan*/  SENS_DAC_INV1_S ; 
 int /*<<< orphan*/  SENS_SAR_DAC_CTRL1_REG ; 
 int /*<<< orphan*/  SENS_SAR_DAC_CTRL2_REG ; 
 int /*<<< orphan*/  SENS_SW_FSTEP ; 
 int /*<<< orphan*/  SENS_SW_FSTEP_S ; 
 int /*<<< orphan*/  SENS_SW_TONE_EN ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  dac_output_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_cosine_generator(void)
{
    // Enable tone generator common to both DAC channels 1 and 2
    SET_PERI_REG_MASK(SENS_SAR_DAC_CTRL1_REG, SENS_SW_TONE_EN);
    // Enable / connect tone tone generator on / to channel 1
    SET_PERI_REG_MASK(SENS_SAR_DAC_CTRL2_REG, SENS_DAC_CW_EN1_M);
    // Invert MSB, otherwise part of the waveform will be inverted
    SET_PERI_REG_BITS(SENS_SAR_DAC_CTRL2_REG, SENS_DAC_INV1, 2, SENS_DAC_INV1_S);
    // Set the frequency of waveform on CW output
#ifdef CONFIG_CUSTOM_RTC_CLK_8M_DIV
    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_CK8M_DIV_SEL, RTC_CLK_8M_DIV);
    ESP_LOGI(TAG, "Custom divider of RTC 8 MHz clock has been set.");
#endif
    SET_PERI_REG_BITS(SENS_SAR_DAC_CTRL1_REG, SENS_SW_FSTEP, CW_FREQUENCY_STEP, SENS_SW_FSTEP_S);

    dac_output_enable(DAC_CHANNEL_1);
}