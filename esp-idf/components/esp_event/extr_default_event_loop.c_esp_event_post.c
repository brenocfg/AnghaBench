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
typedef  int /*<<< orphan*/  esp_event_base_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  TickType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  esp_event_post_to (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * s_default_loop ; 

esp_err_t esp_event_post(esp_event_base_t event_base, int32_t event_id,
        void* event_data, size_t event_data_size, TickType_t ticks_to_wait)
{
    if (s_default_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    return esp_event_post_to(s_default_loop, event_base, event_id,
            event_data, event_data_size, ticks_to_wait);
}