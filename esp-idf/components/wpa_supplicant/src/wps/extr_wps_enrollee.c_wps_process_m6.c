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
struct wps_parse_attr {int /*<<< orphan*/  r_snonce2; int /*<<< orphan*/  key_wrap_auth; int /*<<< orphan*/ * version2; int /*<<< orphan*/  encr_settings_len; int /*<<< orphan*/  encr_settings; int /*<<< orphan*/  authenticator; int /*<<< orphan*/  enrollee_nonce; } ;
struct wps_data {scalar_t__ state; TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
typedef  enum wps_process_res { ____Placeholder_wps_process_res } wps_process_res ;
struct TYPE_2__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ RECV_M6 ; 
 scalar_t__ SEND_M7 ; 
 void* SEND_WSC_NACK ; 
 int WPS_CONTINUE ; 
 int /*<<< orphan*/  WPS_EV_AP_PIN_SUCCESS ; 
 int /*<<< orphan*/  os_free (struct wps_parse_attr*) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct wpabuf* wps_decrypt_encr_settings (struct wps_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_parse_msg (struct wpabuf*,struct wps_parse_attr*) ; 
 scalar_t__ wps_process_authenticator (struct wps_data*,int /*<<< orphan*/ ,struct wpabuf const*) ; 
 scalar_t__ wps_process_enrollee_nonce (struct wps_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_key_wrap_auth (struct wps_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_r_snonce2 (struct wps_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_m6_encr (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum wps_process_res wps_process_m6(struct wps_data *wps,
					   const struct wpabuf *msg,
					   struct wps_parse_attr *attr)
{
	struct wpabuf *decrypted;
	struct wps_parse_attr *eattr;
	enum wps_process_res res;

	wpa_printf(MSG_DEBUG,  "WPS: Received M6");

	eattr = (struct wps_parse_attr *)os_zalloc(sizeof(struct wps_parse_attr));
        if (eattr == NULL) {
		wps->state = SEND_WSC_NACK;
		res = WPS_CONTINUE;
		goto _out;
	}

	if (wps->state != RECV_M6) {
		wpa_printf(MSG_DEBUG,  "WPS: Unexpected state (%d) for "
			   "receiving M6", wps->state);
		wps->state = SEND_WSC_NACK;
		res = WPS_CONTINUE;
		goto _out;
	}

	if (wps_process_enrollee_nonce(wps, attr->enrollee_nonce) ||
	    wps_process_authenticator(wps, attr->authenticator, msg)) {
		wps->state = SEND_WSC_NACK;
		res = WPS_CONTINUE;
		goto _out;
	}

	decrypted = wps_decrypt_encr_settings(wps, attr->encr_settings,
					      attr->encr_settings_len);
	if (decrypted == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: Failed to decrypted Encrypted "
			   "Settings attribute");
		wps->state = SEND_WSC_NACK;
		res = WPS_CONTINUE;
		goto _out;
	}

	if (wps_validate_m6_encr(decrypted, attr->version2 != NULL) < 0) {
		wpabuf_free(decrypted);
		wps->state = SEND_WSC_NACK;
		res = WPS_CONTINUE;
		goto _out;
	}

	wpa_printf(MSG_DEBUG,  "WPS: Processing decrypted Encrypted Settings "
		   "attribute");
	if (wps_parse_msg(decrypted, eattr) < 0 ||
	    wps_process_key_wrap_auth(wps, decrypted, eattr->key_wrap_auth) ||
	    wps_process_r_snonce2(wps, eattr->r_snonce2)) {
		wpabuf_free(decrypted);
		wps->state = SEND_WSC_NACK;
		res = WPS_CONTINUE;
		goto _out;
	}
	wpabuf_free(decrypted);

	if (wps->wps->ap)
		wps->wps->event_cb(wps->wps->cb_ctx, WPS_EV_AP_PIN_SUCCESS,
				   NULL);

	wps->state = SEND_M7;
	res = WPS_CONTINUE;
_out:
	if (eattr)
		os_free(eattr);
	return res;
}