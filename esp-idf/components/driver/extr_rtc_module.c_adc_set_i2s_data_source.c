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
typedef  scalar_t__ adc_i2s_source_t ;
struct TYPE_3__ {scalar_t__ data_to_i2s; } ;
struct TYPE_4__ {TYPE_1__ saradc_ctrl; } ;

/* Variables and functions */
 scalar_t__ ADC_I2S_DATA_SRC_MAX ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ SYSCON ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

esp_err_t adc_set_i2s_data_source(adc_i2s_source_t src)
{
    RTC_MODULE_CHECK(src < ADC_I2S_DATA_SRC_MAX, "ADC i2s data source error", ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&rtc_spinlock);
    // 1: I2S input data is from SAR ADC (for DMA)  0: I2S input data is from GPIO matrix
    SYSCON.saradc_ctrl.data_to_i2s = src;
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}