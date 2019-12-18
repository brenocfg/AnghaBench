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

/* Variables and functions */
 int /*<<< orphan*/  SIG_WPS_TIMER_MSG_TIMEOUT ; 
 int /*<<< orphan*/  wifi_station_wps_msg_timeout_internal () ; 
 int /*<<< orphan*/  wps_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wifi_station_wps_msg_timeout(void)
{
#ifdef USE_WPS_TASK
    wps_post(SIG_WPS_TIMER_MSG_TIMEOUT, 0);
    return;
#else
    wifi_station_wps_msg_timeout_internal();
#endif
}