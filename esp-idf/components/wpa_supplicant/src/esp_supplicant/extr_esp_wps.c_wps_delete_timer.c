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
struct wps_sm {int /*<<< orphan*/  wps_eapol_start_timer; int /*<<< orphan*/  wps_scan_timer; int /*<<< orphan*/  wps_msg_timeout_timer; int /*<<< orphan*/  wps_timeout_timer; int /*<<< orphan*/  wps_success_cb_timer; } ;

/* Variables and functions */
 int ESP_OK ; 
 int /*<<< orphan*/  esp_wifi_disarm_sta_connection_timer_internal () ; 
 int /*<<< orphan*/  ets_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ets_timer_done (int /*<<< orphan*/ *) ; 
 struct wps_sm* gWpsSm ; 

int wps_delete_timer(void)
{
    struct wps_sm *sm = gWpsSm;

    if (!sm) {
        return ESP_OK;
    }

    ets_timer_disarm(&sm->wps_success_cb_timer);
    ets_timer_disarm(&sm->wps_timeout_timer);
    ets_timer_disarm(&sm->wps_msg_timeout_timer);
    ets_timer_disarm(&sm->wps_scan_timer);
    ets_timer_disarm(&sm->wps_eapol_start_timer);
    ets_timer_done(&sm->wps_success_cb_timer);
    ets_timer_done(&sm->wps_timeout_timer);
    ets_timer_done(&sm->wps_msg_timeout_timer);
    ets_timer_done(&sm->wps_scan_timer);
    ets_timer_done(&sm->wps_eapol_start_timer);
    esp_wifi_disarm_sta_connection_timer_internal();
    return ESP_OK;
}