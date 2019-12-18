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
struct TYPE_3__ {int /*<<< orphan*/  sar_clk_div; } ;
struct TYPE_4__ {TYPE_1__ saradc_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ SYSCON ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

esp_err_t adc_set_clk_div(uint8_t clk_div)
{
    portENTER_CRITICAL(&rtc_spinlock);
    // ADC clock devided from APB clk, 80 / 2 = 40Mhz,
    SYSCON.saradc_ctrl.sar_clk_div = clk_div;
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}