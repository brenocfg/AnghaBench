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
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SC_EVENT ; 
 int /*<<< orphan*/  SC_EVENT_GOT_SSID_PSWD ; 
 int /*<<< orphan*/  esp_event_handler_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_smartconfig_internal_stop () ; 
 int /*<<< orphan*/  handler_got_ssid_passwd ; 
 int /*<<< orphan*/  sc_send_ack_stop () ; 

esp_err_t esp_smartconfig_stop(void)
{
    esp_err_t err = ESP_OK;

    err = esp_smartconfig_internal_stop();
    if (err == ESP_OK) {
        sc_send_ack_stop();
        esp_event_handler_unregister(SC_EVENT, SC_EVENT_GOT_SSID_PSWD, handler_got_ssid_passwd);
    }
    return err;
}