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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ dac_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DAC_CHANNEL_1 ; 
 scalar_t__ DAC_CHANNEL_2 ; 
 scalar_t__ DAC_CHANNEL_MAX ; 
 int /*<<< orphan*/  DAC_ERR_STR_CHANNEL_ERROR ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_IO_PAD_DAC1_REG ; 
 int /*<<< orphan*/  RTC_IO_PAD_DAC2_REG ; 
 int /*<<< orphan*/  RTC_IO_PDAC1_DAC ; 
 int /*<<< orphan*/  RTC_IO_PDAC1_DAC_S ; 
 int /*<<< orphan*/  RTC_IO_PDAC2_DAC ; 
 int /*<<< orphan*/  RTC_IO_PDAC2_DAC_S ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SENS_DAC_CW_EN1_M ; 
 int /*<<< orphan*/  SENS_DAC_CW_EN2_M ; 
 int /*<<< orphan*/  SENS_SAR_DAC_CTRL1_REG ; 
 int /*<<< orphan*/  SENS_SAR_DAC_CTRL2_REG ; 
 int /*<<< orphan*/  SENS_SW_TONE_EN ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

esp_err_t dac_output_voltage(dac_channel_t channel, uint8_t dac_value)
{
    RTC_MODULE_CHECK((channel >= DAC_CHANNEL_1) && (channel < DAC_CHANNEL_MAX), DAC_ERR_STR_CHANNEL_ERROR, ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&rtc_spinlock);
    //Disable Tone
    CLEAR_PERI_REG_MASK(SENS_SAR_DAC_CTRL1_REG, SENS_SW_TONE_EN);

    //Disable Channel Tone
    if (channel == DAC_CHANNEL_1) {
        CLEAR_PERI_REG_MASK(SENS_SAR_DAC_CTRL2_REG, SENS_DAC_CW_EN1_M);
    } else if (channel == DAC_CHANNEL_2) {
        CLEAR_PERI_REG_MASK(SENS_SAR_DAC_CTRL2_REG, SENS_DAC_CW_EN2_M);
    }

    //Set the Dac value
    if (channel == DAC_CHANNEL_1) {
        SET_PERI_REG_BITS(RTC_IO_PAD_DAC1_REG, RTC_IO_PDAC1_DAC, dac_value, RTC_IO_PDAC1_DAC_S);   //dac_output
    } else if (channel == DAC_CHANNEL_2) {
        SET_PERI_REG_BITS(RTC_IO_PAD_DAC2_REG, RTC_IO_PDAC2_DAC, dac_value, RTC_IO_PDAC2_DAC_S);   //dac_output
    }

    portEXIT_CRITICAL(&rtc_spinlock);

    return ESP_OK;
}