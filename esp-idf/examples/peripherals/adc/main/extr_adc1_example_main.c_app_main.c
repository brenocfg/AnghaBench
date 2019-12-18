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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_adc_cal_value_t ;
typedef  int /*<<< orphan*/  esp_adc_cal_characteristics_t ;
typedef  int /*<<< orphan*/  adc2_channel_t ;
typedef  int /*<<< orphan*/  adc1_channel_t ;

/* Variables and functions */
 int ADC_UNIT_1 ; 
 int /*<<< orphan*/  ADC_WIDTH_BIT_12 ; 
 int /*<<< orphan*/  DEFAULT_VREF ; 
 int NO_OF_SAMPLES ; 
 int /*<<< orphan*/  adc1_config_channel_atten (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc1_config_width (int /*<<< orphan*/ ) ; 
 scalar_t__ adc1_get_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc2_config_channel_atten (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc2_get_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  adc_chars ; 
 int /*<<< orphan*/  atten ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int channel ; 
 int /*<<< orphan*/  check_efuse () ; 
 int /*<<< orphan*/  esp_adc_cal_characterize (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int esp_adc_cal_raw_to_voltage (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int /*<<< orphan*/  print_char_val_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 int unit ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 

void app_main(void)
{
#if CONFIG_IDF_TARGET_ESP32
    //Check if Two Point or Vref are burned into eFuse
    check_efuse();
#endif

    //Configure ADC
    if (unit == ADC_UNIT_1) {
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(channel, atten);
    } else {
        adc2_config_channel_atten((adc2_channel_t)channel, atten);
    }

#if CONFIG_IDF_TARGET_ESP32
    //Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);
#endif

    //Continuously sample ADC1
    while (1) {
        uint32_t adc_reading = 0;
        //Multisampling
        for (int i = 0; i < NO_OF_SAMPLES; i++) {
            if (unit == ADC_UNIT_1) {
                adc_reading += adc1_get_raw((adc1_channel_t)channel);
            } else {
                int raw;
                adc2_get_raw((adc2_channel_t)channel, ADC_WIDTH_BIT_12, &raw);
                adc_reading += raw;
            }
        }
        adc_reading /= NO_OF_SAMPLES;
#if CONFIG_IDF_TARGET_ESP32
        //Convert adc_reading to voltage in mV
        uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
        printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
        printf("ADC%d CH%d Raw: %d\t\n", unit, channel, adc_reading);
#endif
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}