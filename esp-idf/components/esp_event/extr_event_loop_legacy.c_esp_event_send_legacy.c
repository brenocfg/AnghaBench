#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  event_id; } ;
typedef  TYPE_1__ system_event_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSTEM_EVENT ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_event_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_initialized ; 

esp_err_t esp_event_send_legacy(system_event_t *event)
{
    if (!s_initialized) {
        ESP_LOGE(TAG, "system event loop not initialized via esp_event_loop_init");
        return ESP_ERR_INVALID_STATE;
    }

    return esp_event_post(SYSTEM_EVENT, event->event_id, event, sizeof(*event), 0);
}