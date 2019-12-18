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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_EVENT_ANY_ID ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SYSTEM_EVENT ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_event_handler_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_event_loop_delete_default () ; 
 int /*<<< orphan*/  esp_event_post_to_user ; 
 int /*<<< orphan*/ * s_event_ctx ; 
 int /*<<< orphan*/ * s_event_handler_cb ; 
 int s_initialized ; 

esp_err_t esp_event_loop_deinit(void) 
{
    if (!s_initialized) {
        ESP_LOGE(TAG, "system event loop not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err = esp_event_handler_unregister(SYSTEM_EVENT, ESP_EVENT_ANY_ID, esp_event_post_to_user);
    if (err != ESP_OK) {
        return err;
    }

    err = esp_event_loop_delete_default();
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        return err;
    }

    s_initialized = false;
    s_event_handler_cb = NULL;
    s_event_ctx = NULL;
    return ESP_OK;
}