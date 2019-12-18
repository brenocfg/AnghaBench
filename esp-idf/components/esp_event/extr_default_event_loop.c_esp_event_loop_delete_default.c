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
 scalar_t__ ESP_OK ; 
 scalar_t__ esp_event_loop_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * s_default_loop ; 

esp_err_t esp_event_loop_delete_default(void)
{
    if (!s_default_loop) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err;

    err = esp_event_loop_delete(s_default_loop);

    if (err != ESP_OK) {
        return err;
    }

    s_default_loop = NULL;

    return ESP_OK;
}