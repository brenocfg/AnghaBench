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
struct wps_parse_attr {int /*<<< orphan*/  authenticator; int /*<<< orphan*/  public_key_len; int /*<<< orphan*/  public_key; int /*<<< orphan*/  uuid_r; int /*<<< orphan*/  enrollee_nonce; int /*<<< orphan*/  registrar_nonce; } ;
struct wps_data {scalar_t__ state; int /*<<< orphan*/  peer_dev; int /*<<< orphan*/  config_error; int /*<<< orphan*/ * dev_password; TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
typedef  enum wps_process_res { ____Placeholder_wps_process_res } wps_process_res ;
struct TYPE_2__ {int ap_setup_locked; scalar_t__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ RECV_M2 ; 
 scalar_t__ SEND_M3 ; 
 void* SEND_WSC_NACK ; 
 int /*<<< orphan*/  WPS_CFG_SETUP_LOCKED ; 
 int WPS_CONTINUE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wps_process_authenticator (struct wps_data*,int /*<<< orphan*/ ,struct wpabuf const*) ; 
 scalar_t__ wps_process_device_attrs (int /*<<< orphan*/ *,struct wps_parse_attr*) ; 
 scalar_t__ wps_process_enrollee_nonce (struct wps_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_pubkey (struct wps_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_registrar_nonce (struct wps_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_uuid_r (struct wps_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum wps_process_res wps_process_m2(struct wps_data *wps,
					   const struct wpabuf *msg,
					   struct wps_parse_attr *attr)
{
	wpa_printf(MSG_DEBUG,  "WPS: Received M2");

	if (wps->state != RECV_M2) {
		wpa_printf(MSG_DEBUG,  "WPS: Unexpected state (%d) for "
			   "receiving M2", wps->state);
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}

	if (wps_process_registrar_nonce(wps, attr->registrar_nonce) ||
	    wps_process_enrollee_nonce(wps, attr->enrollee_nonce) ||
	    wps_process_uuid_r(wps, attr->uuid_r)) {
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}

	/*
	 * Stop here on an AP as an Enrollee if AP Setup is locked unless the
	 * special locked mode is used to allow protocol run up to M7 in order
	 * to support external Registrars that only learn the current AP
	 * configuration without changing it.
	 */
	if (wps->wps->ap &&
	    ((wps->wps->ap_setup_locked && wps->wps->ap_setup_locked != 2) ||
	     wps->dev_password == NULL)) {
		wpa_printf(MSG_DEBUG,  "WPS: AP Setup is locked - refuse "
			   "registration of a new Registrar");
		wps->config_error = WPS_CFG_SETUP_LOCKED;
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}

	if (wps_process_pubkey(wps, attr->public_key, attr->public_key_len) ||
	    wps_process_authenticator(wps, attr->authenticator, msg) ||
	    wps_process_device_attrs(&wps->peer_dev, attr)) {
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}

	wps->state = SEND_M3;
	return WPS_CONTINUE;
}