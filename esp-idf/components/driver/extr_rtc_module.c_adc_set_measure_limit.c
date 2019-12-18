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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int meas_num_limit; int /*<<< orphan*/  max_meas_num; } ;
struct TYPE_4__ {TYPE_1__ saradc_ctrl2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ SYSCON ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

__attribute__((used)) static esp_err_t adc_set_measure_limit(uint8_t meas_num, bool lim_en)
{
    portENTER_CRITICAL(&rtc_spinlock);
    // Set max measure number
    SYSCON.saradc_ctrl2.max_meas_num = meas_num;
    // Enable max measure number limit
    SYSCON.saradc_ctrl2.meas_num_limit = lim_en;
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}