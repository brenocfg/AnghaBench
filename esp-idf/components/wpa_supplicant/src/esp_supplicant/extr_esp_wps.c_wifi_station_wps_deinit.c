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
struct wps_sm {int /*<<< orphan*/ * wps; struct wps_sm* wps_ctx; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 int ESP_OK ; 
 int /*<<< orphan*/  WIFI_APPIE_WPS_AR ; 
 int /*<<< orphan*/  WIFI_APPIE_WPS_PR ; 
 int /*<<< orphan*/  esp_wifi_set_wps_cb_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_wifi_unset_appie_internal (int /*<<< orphan*/ ) ; 
 struct wps_sm* gWpsSm ; 
 int /*<<< orphan*/  os_free (struct wps_sm*) ; 
 int /*<<< orphan*/  wps_deinit () ; 
 int /*<<< orphan*/  wps_dev_deinit (int /*<<< orphan*/ *) ; 

int
wifi_station_wps_deinit(void)
{
    struct wps_sm *sm = gWpsSm;

    if (gWpsSm == NULL) {
        return ESP_FAIL;
    }

    esp_wifi_unset_appie_internal(WIFI_APPIE_WPS_PR);
    esp_wifi_unset_appie_internal(WIFI_APPIE_WPS_AR);
    esp_wifi_set_wps_cb_internal(NULL);

    if (sm->dev) {
        wps_dev_deinit(sm->dev);
        sm->dev = NULL;
    }
    if (sm->wps_ctx) {
        os_free(sm->wps_ctx);
        sm->wps_ctx = NULL;
    }
    if (sm->wps) {
        wps_deinit();
        sm->wps = NULL;
    }
    if (sm) {
        os_free(gWpsSm);
        gWpsSm = NULL;
    }

    return ESP_OK;
}