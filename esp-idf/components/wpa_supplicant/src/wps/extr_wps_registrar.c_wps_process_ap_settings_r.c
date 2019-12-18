#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wps_parse_attr {int dummy; } ;
struct TYPE_6__ {scalar_t__ cred_attr_len; int /*<<< orphan*/ * cred_attr; } ;
struct wps_data {TYPE_2__ cred; int /*<<< orphan*/  ap_settings_cb_ctx; int /*<<< orphan*/  (* ap_settings_cb ) (int /*<<< orphan*/ ,TYPE_2__*) ;TYPE_1__* wps; scalar_t__ new_ap_settings; scalar_t__ er; } ;
struct wpabuf {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  registrar; scalar_t__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 struct wpabuf* wps_build_ap_cred (struct wps_data*) ; 
 int /*<<< orphan*/  wps_cred_update (TYPE_2__*,scalar_t__) ; 
 scalar_t__ wps_process_ap_settings (struct wps_parse_attr*,TYPE_2__*) ; 
 int /*<<< orphan*/  wps_registrar_pin_completed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_sta_cred_cb (struct wps_data*) ; 

__attribute__((used)) static int wps_process_ap_settings_r(struct wps_data *wps,
				     struct wps_parse_attr *attr)
{
	struct wpabuf *msg;

	if (wps->wps->ap || wps->er)
		return 0;

	/* AP Settings Attributes in M7 when Enrollee is an AP */
	if (wps_process_ap_settings(attr, &wps->cred) < 0)
		return -1;

	wpa_printf(MSG_INFO, "WPS: Received old AP configuration from AP");

	if (wps->new_ap_settings) {
		wpa_printf(MSG_INFO, "WPS: Update AP configuration based on "
			   "new settings");
		wps_cred_update(&wps->cred, wps->new_ap_settings);
		return 0;
	} else {
#ifdef CONFIG_WPS_PIN
		/*
		 * Use the AP PIN only to receive the current AP settings, not
		 * to reconfigure the AP.
		 */

		/*
		 * Clear selected registrar here since we do not get to
		 * WSC_Done in this protocol run.
		 */
		wps_registrar_pin_completed(wps->wps->registrar);
#endif
		msg = wps_build_ap_cred(wps);
		if (msg == NULL)
			return -1;
		wps->cred.cred_attr = wpabuf_head(msg);
		wps->cred.cred_attr_len = wpabuf_len(msg);

		if (wps->ap_settings_cb) {
			wps->ap_settings_cb(wps->ap_settings_cb_ctx,
					    &wps->cred);
			wpabuf_free(msg);
			return 1;
		}
		wps_sta_cred_cb(wps);

		wps->cred.cred_attr = NULL;
		wps->cred.cred_attr_len = 0;
		wpabuf_free(msg);

		return 1;
	}
}