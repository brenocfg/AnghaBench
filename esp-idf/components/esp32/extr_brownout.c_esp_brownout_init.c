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
 int BROWNOUT_DET_LVL ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int RTC_CNTL_BROWN_OUT_ENA ; 
 int /*<<< orphan*/  RTC_CNTL_BROWN_OUT_INT_ENA_M ; 
 int RTC_CNTL_BROWN_OUT_PD_RF_ENA ; 
 int /*<<< orphan*/  RTC_CNTL_BROWN_OUT_REG ; 
 int RTC_CNTL_BROWN_OUT_RST_WAIT_S ; 
 int RTC_CNTL_DBROWN_OUT_THRES_S ; 
 int /*<<< orphan*/  RTC_CNTL_INT_ENA_REG ; 
 int /*<<< orphan*/  rtc_brownout_isr_handler ; 
 int /*<<< orphan*/  rtc_isr_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void esp_brownout_init(void)
{
    REG_WRITE(RTC_CNTL_BROWN_OUT_REG,
            RTC_CNTL_BROWN_OUT_ENA /* Enable BOD */
            | RTC_CNTL_BROWN_OUT_PD_RF_ENA /* Automatically power down RF */
            /* Reset timeout must be set to >1 even if BOR feature is not used */
            | (2 << RTC_CNTL_BROWN_OUT_RST_WAIT_S)
            | (BROWNOUT_DET_LVL << RTC_CNTL_DBROWN_OUT_THRES_S));

    ESP_ERROR_CHECK( rtc_isr_register(rtc_brownout_isr_handler, NULL, RTC_CNTL_BROWN_OUT_INT_ENA_M) );

    REG_SET_BIT(RTC_CNTL_INT_ENA_REG, RTC_CNTL_BROWN_OUT_INT_ENA_M);
}