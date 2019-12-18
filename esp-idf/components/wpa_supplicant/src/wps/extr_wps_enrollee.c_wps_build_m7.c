#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wps_data {int /*<<< orphan*/  state; int /*<<< orphan*/  uuid_r; int /*<<< orphan*/  peer_dev; TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {scalar_t__ registrar; scalar_t__ ap; scalar_t__ ap_settings_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RECV_M8 ; 
 int /*<<< orphan*/  WPS_M7 ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_build_ap_settings (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_authenticator (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_e_snonce2 (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_encr_settings (struct wps_data*,struct wpabuf*,struct wpabuf*) ; 
 scalar_t__ wps_build_key_wrap_auth (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_msg_type (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_registrar_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_version (struct wpabuf*) ; 
 scalar_t__ wps_build_wfa_ext (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_device_store (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * wps_build_m7(struct wps_data *wps)
{
	struct wpabuf *msg, *plain;

	wpa_printf(MSG_DEBUG,  "WPS: Building Message M7");

	plain = wpabuf_alloc(500 + wps->wps->ap_settings_len);
	if (plain == NULL)
		return NULL;

	msg = wpabuf_alloc(1000 + wps->wps->ap_settings_len);
	if (msg == NULL) {
		wpabuf_free(plain);
		return NULL;
	}

	if (wps_build_version(msg) ||
	    wps_build_msg_type(msg, WPS_M7) ||
	    wps_build_registrar_nonce(wps, msg) ||
	    wps_build_e_snonce2(wps, plain) ||
	    (wps->wps->ap && wps_build_ap_settings(wps, plain)) ||
	    wps_build_key_wrap_auth(wps, plain) ||
	    wps_build_encr_settings(wps, msg, plain) ||
	    wps_build_wfa_ext(msg, 0, NULL, 0) ||
	    wps_build_authenticator(wps, msg)) {
		wpabuf_free(plain);
		wpabuf_free(msg);
		return NULL;
	}
	wpabuf_free(plain);

	if (wps->wps->ap && wps->wps->registrar) {
		/*
		 * If the Registrar is only learning our current configuration,
		 * it may not continue protocol run to successful completion.
		 * Store information here to make sure it remains available.
		 */
		wps_device_store(wps->wps->registrar, &wps->peer_dev,
				 wps->uuid_r);
	}

	wps->state = RECV_M8;
	return msg;
}