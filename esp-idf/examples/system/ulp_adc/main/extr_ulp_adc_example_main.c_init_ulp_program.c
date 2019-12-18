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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC1_CHANNEL_6 ; 
 int /*<<< orphan*/  ADC_ATTEN_DB_11 ; 
 int /*<<< orphan*/  ADC_WIDTH_BIT_12 ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_NUM_12 ; 
 int /*<<< orphan*/  GPIO_NUM_15 ; 
 int /*<<< orphan*/  adc1_config_channel_atten (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc1_config_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc1_ulp_enable () ; 
 int /*<<< orphan*/  esp_deep_sleep_disable_rom_logging () ; 
 int /*<<< orphan*/  rtc_gpio_isolate (int /*<<< orphan*/ ) ; 
 int ulp_high_thr ; 
 int /*<<< orphan*/  ulp_load_binary (int /*<<< orphan*/ ,int,int) ; 
 int ulp_low_thr ; 
 int ulp_main_bin_end ; 
 int ulp_main_bin_start ; 
 int /*<<< orphan*/  ulp_set_wakeup_period (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_ulp_program(void)
{
    esp_err_t err = ulp_load_binary(0, ulp_main_bin_start,
            (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));
    ESP_ERROR_CHECK(err);

    /* Configure ADC channel */
    /* Note: when changing channel here, also change 'adc_channel' constant
       in adc.S */
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_ulp_enable();

    /* Set low and high thresholds, approx. 1.35V - 1.75V*/
    ulp_low_thr = 1500;
    ulp_high_thr = 2000;

    /* Set ULP wake up period to 20ms */
    ulp_set_wakeup_period(0, 20000);

    /* Disconnect GPIO12 and GPIO15 to remove current drain through
     * pullup/pulldown resistors.
     * GPIO12 may be pulled high to select flash voltage.
     */
    rtc_gpio_isolate(GPIO_NUM_12);
    rtc_gpio_isolate(GPIO_NUM_15);
    esp_deep_sleep_disable_rom_logging(); // suppress boot messages
}