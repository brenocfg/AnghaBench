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
typedef  int /*<<< orphan*/  system_event_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 scalar_t__ esp_event_send_legacy (int /*<<< orphan*/ *) ; 
 scalar_t__ esp_event_send_to_default_loop (int /*<<< orphan*/ *) ; 

esp_err_t esp_event_send(system_event_t *event)
{
    // send the event to the new style event loop
    esp_err_t err = esp_event_send_to_default_loop(event);
    if (err != ESP_OK) {
        return err;
    }

    // send the event to the legacy event loop
    err = esp_event_send_legacy(event);
    if (err != ESP_OK) {
        return err;
    }

    return ESP_OK;
}