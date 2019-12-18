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
typedef  int /*<<< orphan*/  pm_mode_t ;
typedef  scalar_t__ esp_pm_lock_type_t ;

/* Variables and functions */
 scalar_t__ ESP_PM_APB_FREQ_MAX ; 
 scalar_t__ ESP_PM_CPU_FREQ_MAX ; 
 scalar_t__ ESP_PM_NO_LIGHT_SLEEP ; 
 int /*<<< orphan*/  PM_MODE_APB_MAX ; 
 int /*<<< orphan*/  PM_MODE_APB_MIN ; 
 int /*<<< orphan*/  PM_MODE_CPU_MAX ; 
 int /*<<< orphan*/  abort () ; 

pm_mode_t esp_pm_impl_get_mode(esp_pm_lock_type_t type, int arg)
{
    (void) arg;
    if (type == ESP_PM_CPU_FREQ_MAX) {
        return PM_MODE_CPU_MAX;
    } else if (type == ESP_PM_APB_FREQ_MAX) {
        return PM_MODE_APB_MAX;
    } else if (type == ESP_PM_NO_LIGHT_SLEEP) {
        return PM_MODE_APB_MIN;
    } else {
        // unsupported mode
        abort();
    }
}