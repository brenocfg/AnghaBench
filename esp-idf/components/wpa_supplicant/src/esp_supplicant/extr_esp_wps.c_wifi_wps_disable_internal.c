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
 int ESP_OK ; 
 int /*<<< orphan*/  WPS_STATUS_DISABLE ; 
 int /*<<< orphan*/  wifi_station_wps_deinit () ; 
 int /*<<< orphan*/  wps_set_status (int /*<<< orphan*/ ) ; 

int wifi_wps_disable_internal(void)
{
    wps_set_status(WPS_STATUS_DISABLE);
    wifi_station_wps_deinit();
    return ESP_OK;
}