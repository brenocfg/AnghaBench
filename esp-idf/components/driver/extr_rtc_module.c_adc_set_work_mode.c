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
typedef  scalar_t__ adc_unit_t ;
struct TYPE_3__ {int work_mode; int sar_sel; } ;
struct TYPE_4__ {TYPE_1__ saradc_ctrl; } ;

/* Variables and functions */
 scalar_t__ ADC_UNIT_1 ; 
 scalar_t__ ADC_UNIT_2 ; 
 scalar_t__ ADC_UNIT_ALTER ; 
 scalar_t__ ADC_UNIT_BOTH ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ SYSCON ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

__attribute__((used)) static esp_err_t adc_set_work_mode(adc_unit_t adc_unit)
{
    portENTER_CRITICAL(&rtc_spinlock);
    if (adc_unit == ADC_UNIT_1) {
        // saradc mode sel : 0--single saradc;  1--double saradc;  2--alternative saradc
        SYSCON.saradc_ctrl.work_mode = 0;
        //ENABLE ADC  0: ADC1  1: ADC2, only work for single SAR mode
        SYSCON.saradc_ctrl.sar_sel = 0;
    } else if (adc_unit == ADC_UNIT_2) {
        // saradc mode sel : 0--single saradc;  1--double saradc;  2--alternative saradc
        SYSCON.saradc_ctrl.work_mode = 0;
        //ENABLE ADC1  0: SAR1  1: SAR2  only work for single SAR mode
        SYSCON.saradc_ctrl.sar_sel = 1;
    } else if (adc_unit == ADC_UNIT_BOTH) {
        // saradc mode sel : 0--single saradc;  1--double saradc;  2--alternative saradc
        SYSCON.saradc_ctrl.work_mode = 1;
    } else if (adc_unit == ADC_UNIT_ALTER) {
        // saradc mode sel : 0--single saradc;  1--double saradc;  2--alternative saradc
        SYSCON.saradc_ctrl.work_mode = 2;
    }
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}