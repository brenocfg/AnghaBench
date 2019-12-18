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
typedef  int /*<<< orphan*/  esp_bluedroid_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_INITIALIZED ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_UNINITIALIZED ; 
 scalar_t__ bd_already_enable ; 
 scalar_t__ bd_already_init ; 

esp_bluedroid_status_t esp_bluedroid_get_status(void)
{
    if (bd_already_init) {
        if (bd_already_enable) {
            return ESP_BLUEDROID_STATUS_ENABLED;
        } else {
            return ESP_BLUEDROID_STATUS_INITIALIZED;
        }
    } else {
        return ESP_BLUEDROID_STATUS_UNINITIALIZED;
    }
}