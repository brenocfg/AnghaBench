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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int SENS_DAC_CLK_INV_M ; 
 int SENS_DAC_DIG_FORCE_M ; 
 int /*<<< orphan*/  SENS_SAR_DAC_CTRL1_REG ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

esp_err_t dac_i2s_disable(void)
{
    portENTER_CRITICAL(&rtc_spinlock);
    CLEAR_PERI_REG_MASK(SENS_SAR_DAC_CTRL1_REG, SENS_DAC_DIG_FORCE_M | SENS_DAC_CLK_INV_M);
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}