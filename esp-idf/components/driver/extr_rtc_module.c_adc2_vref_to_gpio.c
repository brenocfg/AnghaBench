#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {int dtest_rtc; int ent_rtc; } ;
struct TYPE_7__ {scalar_t__ dbg_atten; } ;
struct TYPE_12__ {TYPE_2__ test_mux; TYPE_1__ bias_conf; } ;
struct TYPE_10__ {int sar2_en_pad_force; int sar2_en_pad; } ;
struct TYPE_9__ {int sar2_en_test; } ;
struct TYPE_11__ {TYPE_4__ sar_meas_start2; TYPE_3__ sar_start_force; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ GPIO_NUM_25 ; 
 scalar_t__ GPIO_NUM_26 ; 
 scalar_t__ GPIO_NUM_27 ; 
 TYPE_6__ RTCCNTL ; 
 TYPE_5__ SENS ; 
 int /*<<< orphan*/  adc_power_always_on () ; 
 int /*<<< orphan*/  rtc_gpio_init (scalar_t__) ; 
 int /*<<< orphan*/  rtc_gpio_input_disable (scalar_t__) ; 
 int /*<<< orphan*/  rtc_gpio_output_disable (scalar_t__) ; 
 int /*<<< orphan*/  rtc_gpio_pulldown_dis (scalar_t__) ; 
 int /*<<< orphan*/  rtc_gpio_pullup_dis (scalar_t__) ; 

esp_err_t adc2_vref_to_gpio(gpio_num_t gpio)
{
#if CONFIG_IDF_TARGET_ESP32
    int channel;
    if(gpio == GPIO_NUM_25){
        channel = 8;    //Channel 8 bit
    }else if (gpio == GPIO_NUM_26){
        channel = 9;    //Channel 9 bit
    }else if (gpio == GPIO_NUM_27){
        channel = 7;    //Channel 7 bit
    }else{
        return ESP_ERR_INVALID_ARG;
    }

    //Configure RTC gpio
    rtc_gpio_init(gpio);
    rtc_gpio_output_disable(gpio);
    rtc_gpio_input_disable(gpio);
    rtc_gpio_pullup_dis(gpio);
    rtc_gpio_pulldown_dis(gpio);
    //force fsm
    adc_power_always_on();               //Select power source of ADC

    RTCCNTL.bias_conf.dbg_atten = 0;     //Check DBG effect outside sleep mode
    //set dtest (MUX_SEL : 0 -> RTC; 1-> vdd_sar2)
    RTCCNTL.test_mux.dtest_rtc = 1;      //Config test mux to route v_ref to ADC2 Channels
    //set ent
    RTCCNTL.test_mux.ent_rtc = 1;
    //set sar2_en_test
    SENS.sar_start_force.sar2_en_test = 1;
    //set sar2 en force
    SENS.sar_meas_start2.sar2_en_pad_force = 1;      //Pad bitmap controlled by SW
    //set en_pad for channels 7,8,9 (bits 0x380)
    SENS.sar_meas_start2.sar2_en_pad = 1<<channel;
#endif
    return ESP_OK;
}