#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;
struct wps_sm {TYPE_2__ config; TYPE_1__* wps; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ RECV_M2 ; 
 int /*<<< orphan*/  WPS_FAIL_REASON_RECV_M2D ; 
 scalar_t__ WPS_FINISHED ; 
 struct wps_sm* gWpsSm ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_add_discard_ap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_finish () ; 
 int /*<<< orphan*/  wps_stop_process (int /*<<< orphan*/ ) ; 

void
wifi_station_wps_msg_timeout_internal(void)
{
    struct wps_sm *sm = gWpsSm;

    if (!sm) {
        return;
    }

    if (sm->wps->state == WPS_FINISHED) {
        wpa_printf(MSG_DEBUG, "wps msg timeout WPS_FINISHED");
        wps_finish();
    } else if (sm->wps->state == RECV_M2) {
        wpa_printf(MSG_DEBUG, "wps msg timeout RECV_M2");
        wpa_printf(MSG_DEBUG, "wps recev m2/m2d timeout------>");
        wps_add_discard_ap(sm->config.bssid);
        wps_stop_process(WPS_FAIL_REASON_RECV_M2D);
    }
}