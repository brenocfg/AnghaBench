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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_event_handler_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  esp_event_handler_unregister_with (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * s_default_loop ; 

esp_err_t esp_event_handler_unregister(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler)
{
    if (s_default_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    return esp_event_handler_unregister_with(s_default_loop, event_base, event_id,
            event_handler);
}