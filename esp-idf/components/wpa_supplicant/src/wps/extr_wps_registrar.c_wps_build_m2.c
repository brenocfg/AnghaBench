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
struct wps_data {int int_reg; int /*<<< orphan*/  state; TYPE_1__* wps; int /*<<< orphan*/  dev_pw_id; int /*<<< orphan*/  uuid_r; int /*<<< orphan*/  nonce_r; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RECV_M3 ; 
 int /*<<< orphan*/  WPS_CALC_KEY_NORMAL ; 
 int /*<<< orphan*/  WPS_CFG_NO_ERROR ; 
 int /*<<< orphan*/  WPS_M2 ; 
 int /*<<< orphan*/  WPS_NONCE_LEN ; 
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_build_assoc_state (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_auth_type_flags (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_authenticator (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_config_error (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_config_methods_r (int /*<<< orphan*/ ,struct wpabuf*) ; 
 scalar_t__ wps_build_conn_type_flags (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_dev_password_id (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_device_attrs (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_encr_type_flags (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_enrollee_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_msg_type (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_os_version (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_public_key (struct wps_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_registrar_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_rf_bands (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_uuid_r (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_version (struct wpabuf*) ; 
 scalar_t__ wps_build_wfa_ext (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_derive_keys (struct wps_data*) ; 

__attribute__((used)) static struct wpabuf * wps_build_m2(struct wps_data *wps)
{
	struct wpabuf *msg;

	if (random_get_bytes(wps->nonce_r, WPS_NONCE_LEN) < 0)
		return NULL;
	wpa_hexdump(MSG_DEBUG, "WPS: Registrar Nonce",
		    wps->nonce_r, WPS_NONCE_LEN);
	wpa_hexdump(MSG_DEBUG, "WPS: UUID-R", wps->uuid_r, WPS_UUID_LEN);

	wpa_printf(MSG_DEBUG,  "WPS: Building Message M2");
	msg = wpabuf_alloc(1000);
	if (msg == NULL)
		return NULL;

	if (wps_build_version(msg) ||
	    wps_build_msg_type(msg, WPS_M2) ||
	    wps_build_enrollee_nonce(wps, msg) ||
	    wps_build_registrar_nonce(wps, msg) ||
	    wps_build_uuid_r(wps, msg) ||
	    wps_build_public_key(wps, msg, WPS_CALC_KEY_NORMAL) ||
	    wps_derive_keys(wps) ||
	    wps_build_auth_type_flags(wps, msg) ||
	    wps_build_encr_type_flags(wps, msg) ||
	    wps_build_conn_type_flags(wps, msg) ||
	    wps_build_config_methods_r(wps->wps->registrar, msg) ||
	    wps_build_device_attrs(&wps->wps->dev, msg) ||
	    wps_build_rf_bands(&wps->wps->dev, msg) ||
	    wps_build_assoc_state(wps, msg) ||
	    wps_build_config_error(msg, WPS_CFG_NO_ERROR) ||
	    wps_build_dev_password_id(msg, wps->dev_pw_id) ||
	    wps_build_os_version(&wps->wps->dev, msg) ||
	    wps_build_wfa_ext(msg, 0, NULL, 0) ||
	    wps_build_authenticator(wps, msg)) {
		wpabuf_free(msg);
		return NULL;
	}

	wps->int_reg = 1;
	wps->state = RECV_M3;
	return msg;
}