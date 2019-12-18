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
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_BROWN_OUT_INT_CLR ; 
 int /*<<< orphan*/  RTC_CNTL_INT_CLR_REG ; 
 int /*<<< orphan*/  esp_cpu_stall (int) ; 
 int /*<<< orphan*/  esp_restart_noos () ; 
 int /*<<< orphan*/  ets_printf (char*) ; 
 int /*<<< orphan*/  xPortGetCoreID () ; 

__attribute__((used)) static void rtc_brownout_isr_handler(void *arg)
{
    /* Normally RTC ISR clears the interrupt flag after the application-supplied
     * handler returns. Since restart is called here, the flag needs to be
     * cleared manually.
     */
    REG_WRITE(RTC_CNTL_INT_CLR_REG, RTC_CNTL_BROWN_OUT_INT_CLR);
    /* Stall the other CPU to make sure the code running there doesn't use UART
     * at the same time as the following ets_printf.
     */
    esp_cpu_stall(!xPortGetCoreID());
    ets_printf("\r\nBrownout detector was triggered\r\n\r\n");
    esp_restart_noos();
}