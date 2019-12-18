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

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_BROWN_OUT_INT_ENA_M ; 
 int /*<<< orphan*/  RTC_CNTL_INT_ENA_REG ; 
 int /*<<< orphan*/  rtc_brownout_isr_handler ; 
 int /*<<< orphan*/  rtc_isr_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void esp_brownout_init(void)
{
// TODO: implement brownout threshold configuration for esp32s2beta - IDF-751

    ESP_ERROR_CHECK( rtc_isr_register(rtc_brownout_isr_handler, NULL, RTC_CNTL_BROWN_OUT_INT_ENA_M) );

    REG_SET_BIT(RTC_CNTL_INT_ENA_REG, RTC_CNTL_BROWN_OUT_INT_ENA_M);
}