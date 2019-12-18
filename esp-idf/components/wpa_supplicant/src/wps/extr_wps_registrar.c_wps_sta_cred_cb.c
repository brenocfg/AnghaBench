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
struct TYPE_4__ {int auth_type; int encr_type; } ;
struct wps_data {TYPE_2__ cred; TYPE_1__* wps; } ;
struct TYPE_3__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* cred_cb ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPS_AUTH_WPA2PSK ; 
 int WPS_AUTH_WPAPSK ; 
 int WPS_ENCR_AES ; 
 int WPS_ENCR_TKIP ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wps_sta_cred_cb(struct wps_data *wps)
{
	/*
	 * Update credential to only include a single authentication and
	 * encryption type in case the AP configuration includes more than one
	 * option.
	 */
	if (wps->cred.auth_type & WPS_AUTH_WPA2PSK)
		wps->cred.auth_type = WPS_AUTH_WPA2PSK;
	else if (wps->cred.auth_type & WPS_AUTH_WPAPSK)
		wps->cred.auth_type = WPS_AUTH_WPAPSK;
	if (wps->cred.encr_type & WPS_ENCR_AES)
		wps->cred.encr_type = WPS_ENCR_AES;
	else if (wps->cred.encr_type & WPS_ENCR_TKIP)
		wps->cred.encr_type = WPS_ENCR_TKIP;
	wpa_printf(MSG_DEBUG,  "WPS: Update local configuration based on the "
		   "AP configuration");
	if (wps->wps->cred_cb)
		wps->wps->cred_cb(wps->wps->cb_ctx, &wps->cred);
}