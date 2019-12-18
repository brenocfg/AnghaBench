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
typedef  scalar_t__ u16 ;
struct wps_data {scalar_t__ config_error; int /*<<< orphan*/  state; TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  registrar; scalar_t__ ap_setup_locked; scalar_t__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RECV_M2D_ACK ; 
 scalar_t__ WPS_CFG_NO_ERROR ; 
 scalar_t__ WPS_CFG_SETUP_LOCKED ; 
 int /*<<< orphan*/  WPS_M2D ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_build_assoc_state (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_auth_type_flags (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_config_error (struct wpabuf*,scalar_t__) ; 
 scalar_t__ wps_build_config_methods_r (int /*<<< orphan*/ ,struct wpabuf*) ; 
 scalar_t__ wps_build_conn_type_flags (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_device_attrs (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_encr_type_flags (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_enrollee_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_msg_type (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_os_version (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_registrar_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_rf_bands (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_uuid_r (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_version (struct wpabuf*) ; 
 scalar_t__ wps_build_wfa_ext (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * wps_build_m2d(struct wps_data *wps)
{
	struct wpabuf *msg;
	u16 err = wps->config_error;

	wpa_printf(MSG_DEBUG,  "WPS: Building Message M2D");
	msg = wpabuf_alloc(1000);
	if (msg == NULL)
		return NULL;

	if (wps->wps->ap && wps->wps->ap_setup_locked &&
	    err == WPS_CFG_NO_ERROR)
		err = WPS_CFG_SETUP_LOCKED;

	if (wps_build_version(msg) ||
	    wps_build_msg_type(msg, WPS_M2D) ||
	    wps_build_enrollee_nonce(wps, msg) ||
	    wps_build_registrar_nonce(wps, msg) ||
	    wps_build_uuid_r(wps, msg) ||
	    wps_build_auth_type_flags(wps, msg) ||
	    wps_build_encr_type_flags(wps, msg) ||
	    wps_build_conn_type_flags(wps, msg) ||
	    wps_build_config_methods_r(wps->wps->registrar, msg) ||
	    wps_build_device_attrs(&wps->wps->dev, msg) ||
	    wps_build_rf_bands(&wps->wps->dev, msg) ||
	    wps_build_assoc_state(wps, msg) ||
	    wps_build_config_error(msg, err) ||
	    wps_build_os_version(&wps->wps->dev, msg) ||
	    wps_build_wfa_ext(msg, 0, NULL, 0)) {
		wpabuf_free(msg);
		return NULL;
	}

	wps->state = RECV_M2D_ACK;
	return msg;
}