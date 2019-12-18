#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  adc_i2s_encode_t ;
struct TYPE_3__ {int /*<<< orphan*/  data_sar_sel; } ;
struct TYPE_4__ {TYPE_1__ saradc_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ SYSCON ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

__attribute__((used)) static esp_err_t adc_set_data_format(adc_i2s_encode_t mode)
{
    portENTER_CRITICAL(&rtc_spinlock);
    //data format:
    //0: ADC_ENCODE_12BIT  [15:12]-channel [11:0]-12 bits ADC data
    //1: ADC_ENCODE_11BIT  [15]-1 [14:11]-channel [10:0]-11 bits ADC data, the resolution should not be larger than 11 bits in this case.
    SYSCON.saradc_ctrl.data_sar_sel = mode;
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}