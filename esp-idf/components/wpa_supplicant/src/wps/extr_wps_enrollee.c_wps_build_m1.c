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
typedef  int u16 ;
struct wps_data {scalar_t__ dev_password_len; int /*<<< orphan*/  state; TYPE_1__* wps; int /*<<< orphan*/  dev_pw_id; int /*<<< orphan*/  uuid_e; int /*<<< orphan*/  pbc_in_m1; int /*<<< orphan*/  nonce_e; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int config_methods; int /*<<< orphan*/  dev; scalar_t__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RECV_M2 ; 
 int /*<<< orphan*/  WPS_CALC_KEY_NO_CALC ; 
 int /*<<< orphan*/  WPS_CFG_NO_ERROR ; 
 int WPS_CONFIG_DISPLAY ; 
 int WPS_CONFIG_PHY_PUSHBUTTON ; 
 int WPS_CONFIG_PUSHBUTTON ; 
 int WPS_CONFIG_VIRT_PUSHBUTTON ; 
 int /*<<< orphan*/  WPS_M1 ; 
 int /*<<< orphan*/  WPS_NONCE_LEN ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_build_assoc_state (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_auth_type_flags (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_config_error (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_config_methods (struct wpabuf*,int) ; 
 scalar_t__ wps_build_conn_type_flags (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_dev_password_id (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_device_attrs (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_encr_type_flags (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_enrollee_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_mac_addr (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_msg_type (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_os_version (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_public_key (struct wps_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_rf_bands (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_uuid_e (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_vendor_ext_m1 (int /*<<< orphan*/ *,struct wpabuf*) ; 
 scalar_t__ wps_build_version (struct wpabuf*) ; 
 scalar_t__ wps_build_wfa_ext (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_wps_state (struct wps_data*,struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * wps_build_m1(struct wps_data *wps)
{
	struct wpabuf *msg;
	u16 config_methods;

	if (random_get_bytes(wps->nonce_e, WPS_NONCE_LEN) < 0)
		return NULL;
	wpa_hexdump(MSG_DEBUG, "WPS: Enrollee Nonce",
		    wps->nonce_e, WPS_NONCE_LEN);

	wpa_printf(MSG_DEBUG,  "WPS: Building Message M1");
	msg = wpabuf_alloc(1000);
	if (msg == NULL)
		return NULL;

	config_methods = wps->wps->config_methods;
	if (wps->wps->ap && !wps->pbc_in_m1 &&
	    (wps->dev_password_len != 0 ||
	     (config_methods & WPS_CONFIG_DISPLAY))) {
		/*
		 * These are the methods that the AP supports as an Enrollee
		 * for adding external Registrars, so remove PushButton.
		 *
		 * As a workaround for Windows 7 mechanism for probing WPS
		 * capabilities from M1, leave PushButton option if no PIN
		 * method is available or if WPS configuration enables PBC
		 * workaround.
		 */
		config_methods &= ~WPS_CONFIG_PUSHBUTTON;
#ifdef CONFIG_WPS2
		config_methods &= ~(WPS_CONFIG_VIRT_PUSHBUTTON |
				    WPS_CONFIG_PHY_PUSHBUTTON);
#endif /* CONFIG_WPS2 */
	}

	if (wps_build_version(msg) ||
	    wps_build_msg_type(msg, WPS_M1) ||
	    wps_build_uuid_e(msg, wps->uuid_e) ||
	    wps_build_mac_addr(wps, msg) ||
	    wps_build_enrollee_nonce(wps, msg) ||
	    wps_build_public_key(wps, msg, WPS_CALC_KEY_NO_CALC) ||
	    wps_build_auth_type_flags(wps, msg) ||
	    wps_build_encr_type_flags(wps, msg) ||
	    wps_build_conn_type_flags(wps, msg) ||
	    wps_build_config_methods(msg, config_methods) ||
	    wps_build_wps_state(wps, msg) ||
	    wps_build_device_attrs(&wps->wps->dev, msg) ||
	    wps_build_rf_bands(&wps->wps->dev, msg) ||
	    wps_build_assoc_state(wps, msg) ||
	    wps_build_dev_password_id(msg, wps->dev_pw_id) ||
	    wps_build_config_error(msg, WPS_CFG_NO_ERROR) ||
	    wps_build_os_version(&wps->wps->dev, msg) ||
	    wps_build_wfa_ext(msg, 0, NULL, 0) ||
	    wps_build_vendor_ext_m1(&wps->wps->dev, msg)) {
		wpabuf_free(msg);
		return NULL;
	}

	wps->state = RECV_M2;
	return msg;
}