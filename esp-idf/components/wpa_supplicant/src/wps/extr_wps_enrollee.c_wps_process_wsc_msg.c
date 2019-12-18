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
struct wps_parse_attr {int* msg_type; int /*<<< orphan*/ * enrollee_nonce; } ;
struct wps_data {int /*<<< orphan*/  last_msg; int /*<<< orphan*/  error_indication; int /*<<< orphan*/  config_error; int /*<<< orphan*/  wps; int /*<<< orphan*/  state; int /*<<< orphan*/  nonce_e; } ;
struct wpabuf {int dummy; } ;
typedef  enum wps_process_res { ____Placeholder_wps_process_res } wps_process_res ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RECV_M2 ; 
 int /*<<< orphan*/  RECV_M4 ; 
 int /*<<< orphan*/  RECV_M6 ; 
 int /*<<< orphan*/  RECV_M8 ; 
 int /*<<< orphan*/  SEND_WSC_NACK ; 
 int WPS_CONTINUE ; 
 int WPS_FAILURE ; 
 int /*<<< orphan*/  WPS_IGNORE_STATE (int /*<<< orphan*/ ) ; 
#define  WPS_M2 132 
#define  WPS_M2D 131 
#define  WPS_M4 130 
#define  WPS_M6 129 
#define  WPS_M8 128 
 int /*<<< orphan*/  WPS_NONCE_LEN ; 
 int /*<<< orphan*/  os_free (struct wps_parse_attr*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_dup (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_fail_event (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 int wps_process_m2 (struct wps_data*,struct wpabuf const*,struct wps_parse_attr*) ; 
 int wps_process_m2d (struct wps_data*,struct wps_parse_attr*) ; 
 int wps_process_m4 (struct wps_data*,struct wpabuf const*,struct wps_parse_attr*) ; 
 int wps_process_m6 (struct wps_data*,struct wpabuf const*,struct wps_parse_attr*) ; 
 int wps_process_m8 (struct wps_data*,struct wpabuf const*,struct wps_parse_attr*) ; 
 int /*<<< orphan*/  wps_validate_m2 (struct wpabuf const*) ; 
 int /*<<< orphan*/  wps_validate_m2d (struct wpabuf const*) ; 
 int /*<<< orphan*/  wps_validate_m4 (struct wpabuf const*) ; 
 int /*<<< orphan*/  wps_validate_m6 (struct wpabuf const*) ; 
 int /*<<< orphan*/  wps_validate_m8 (struct wpabuf const*) ; 

__attribute__((used)) static enum wps_process_res wps_process_wsc_msg(struct wps_data *wps,
						const struct wpabuf *msg)
{
	struct wps_parse_attr *attr;
	enum wps_process_res ret = WPS_CONTINUE;

	wpa_printf(MSG_DEBUG,  "WPS: Received WSC_MSG");

	attr = (struct wps_parse_attr *)os_zalloc(sizeof(struct wps_parse_attr));
        if (attr == NULL) {
		ret = WPS_FAILURE;
		goto _out;
	}

	if (wps_parse_msg(msg, attr) < 0) {
		ret = WPS_FAILURE;
		goto _out;
	}

	if (attr->enrollee_nonce == NULL ||
	    os_memcmp(wps->nonce_e, attr->enrollee_nonce, WPS_NONCE_LEN) != 0) {
		wpa_printf(MSG_DEBUG,  "WPS: Mismatch in enrollee nonce");
		ret = WPS_FAILURE;
		goto _out;
	}

	if (attr->msg_type == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No Message Type attribute");
		wps->state = SEND_WSC_NACK;
		ret = WPS_CONTINUE;
		goto _out;
	}

	switch (*attr->msg_type) {
	case WPS_M2:
                WPS_IGNORE_STATE(RECV_M2);
		if (wps_validate_m2(msg) < 0) {
			ret = WPS_FAILURE;
			goto _out;
		}
		ret = wps_process_m2(wps, msg, attr);
		break;
	case WPS_M2D:
		if (wps_validate_m2d(msg) < 0) {
			ret = WPS_FAILURE;
			goto _out;
		}
		ret = wps_process_m2d(wps, attr);
		break;
	case WPS_M4:
                WPS_IGNORE_STATE(RECV_M4);
		if (wps_validate_m4(msg) < 0) {
			ret = WPS_FAILURE;
			goto _out;
		}
		ret = wps_process_m4(wps, msg, attr);
		if (ret == WPS_FAILURE || wps->state == SEND_WSC_NACK)
			wps_fail_event(wps->wps, WPS_M4, wps->config_error,
				       wps->error_indication);
		break;
	case WPS_M6:
                WPS_IGNORE_STATE(RECV_M6);
		if (wps_validate_m6(msg) < 0) {
			ret = WPS_FAILURE;
			goto _out;
		}
		ret = wps_process_m6(wps, msg, attr);
		if (ret == WPS_FAILURE || wps->state == SEND_WSC_NACK)
			wps_fail_event(wps->wps, WPS_M6, wps->config_error,
				       wps->error_indication);
		break;
	case WPS_M8:
                WPS_IGNORE_STATE(RECV_M8);
		if (wps_validate_m8(msg) < 0) {
			ret = WPS_FAILURE;
			goto _out;
		}
		ret = wps_process_m8(wps, msg, attr);
		if (ret == WPS_FAILURE || wps->state == SEND_WSC_NACK)
			wps_fail_event(wps->wps, WPS_M8, wps->config_error,
				       wps->error_indication);
		break;
	default:
		wpa_printf(MSG_DEBUG,  "WPS: Unsupported Message Type %d",
			   *attr->msg_type);
		ret = WPS_FAILURE;
		goto _out;
	}

	/*
	 * Save a copy of the last message for Authenticator derivation if we
	 * are continuing. However, skip M2D since it is not authenticated and
	 * neither is the ACK/NACK response frame. This allows the possibly
	 * following M2 to be processed correctly by using the previously sent
	 * M1 in Authenticator derivation.
	 */
	if (ret == WPS_CONTINUE && *attr->msg_type != WPS_M2D) {
		/* Save a copy of the last message for Authenticator derivation
		 */
		wpabuf_free(wps->last_msg);
		wps->last_msg = wpabuf_dup(msg);
	}

_out:
	if (attr)
		os_free(attr);

	return ret;
}