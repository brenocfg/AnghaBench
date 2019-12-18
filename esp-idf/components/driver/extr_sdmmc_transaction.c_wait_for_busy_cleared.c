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
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  sdmmc_host_card_busy () ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static bool wait_for_busy_cleared(int timeout_ms)
{
    if (timeout_ms == 0) {
        return !sdmmc_host_card_busy();
    }

    /* It would have been nice to do this without polling, however the peripheral
     * can only generate Busy Clear Interrupt for data write commands, and waiting
     * for busy clear is mostly needed for other commands such as MMC_SWITCH.
     */
    int timeout_ticks = (timeout_ms + portTICK_PERIOD_MS - 1) / portTICK_PERIOD_MS;
    while (timeout_ticks-- > 0) {
        if (!sdmmc_host_card_busy()) {
            return true;
        }
        vTaskDelay(1);
    }
    return false;
}