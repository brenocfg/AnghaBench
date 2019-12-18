#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wps_parse_attr {scalar_t__* msg_type; int /*<<< orphan*/ * enrollee_nonce; int /*<<< orphan*/ * registrar_nonce; } ;
struct wps_data {scalar_t__ state; TYPE_1__* wps; int /*<<< orphan*/ * uuid_e; int /*<<< orphan*/  p2p_dev_addr; scalar_t__ pbc; int /*<<< orphan*/  dev_password_len; int /*<<< orphan*/  dev_password; int /*<<< orphan*/  mac_addr_e; int /*<<< orphan*/ * new_psk; int /*<<< orphan*/  new_psk_len; int /*<<< orphan*/  er; int /*<<< orphan*/  peer_dev; int /*<<< orphan*/  nonce_e; int /*<<< orphan*/  nonce_r; scalar_t__ ext_reg; } ;
struct wps_credential {int auth_type; int encr_type; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct wpabuf {int dummy; } ;
typedef  enum wps_process_res { ____Placeholder_wps_process_res } wps_process_res ;
typedef  int /*<<< orphan*/  cred ;
struct TYPE_9__ {int /*<<< orphan*/  pbc_ignore_uuid; int /*<<< orphan*/  pbc_ignore_start; int /*<<< orphan*/  disable_auto_conf; } ;
struct TYPE_8__ {scalar_t__ wps_state; TYPE_2__* registrar; scalar_t__ ap; int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* cred_cb ) (int /*<<< orphan*/ ,struct wps_credential*) ;int /*<<< orphan*/  ssid_len; int /*<<< orphan*/ * ssid; scalar_t__ wps_upnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ RECV_DONE ; 
 int WPS_AUTH_WPA2PSK ; 
 int WPS_AUTH_WPAPSK ; 
 int WPS_DONE ; 
 int WPS_ENCR_AES ; 
 int WPS_ENCR_TKIP ; 
 int WPS_FAILURE ; 
 int /*<<< orphan*/  WPS_NONCE_LEN ; 
 scalar_t__ WPS_STATE_CONFIGURED ; 
 scalar_t__ WPS_STATE_NOT_CONFIGURED ; 
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 scalar_t__ WPS_WSC_DONE ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_get_time (int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct wps_credential*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct wps_credential*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wps_cb_new_psk (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_cb_reg_success (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_device_store (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 int /*<<< orphan*/  wps_registrar_pbc_completed (TYPE_2__*) ; 
 int /*<<< orphan*/  wps_registrar_pin_completed (TYPE_2__*) ; 
 int /*<<< orphan*/  wps_registrar_remove_pbc_session (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_sta_cred_cb (struct wps_data*) ; 
 int /*<<< orphan*/  wps_success_event (TYPE_1__*) ; 

__attribute__((used)) static enum wps_process_res wps_process_wsc_done(struct wps_data *wps,
						 const struct wpabuf *msg)
{
	struct wps_parse_attr attr;

	wpa_printf(MSG_DEBUG,  "WPS: Received WSC_Done");

	if (wps->state != RECV_DONE && (!wps->ext_reg)){
		wpa_printf(MSG_DEBUG,  "WPS: Unexpected state (%d) for "
			   "receiving WSC_Done", wps->state);
		return WPS_FAILURE;
	}

	if (wps_parse_msg(msg, &attr) < 0)
		return WPS_FAILURE;

	if (attr.msg_type == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No Message Type attribute");
		return WPS_FAILURE;
	}

	if (*attr.msg_type != WPS_WSC_DONE) {
		wpa_printf(MSG_DEBUG,  "WPS: Invalid Message Type %d",
			   *attr.msg_type);
		return WPS_FAILURE;
	}

#ifdef CONFIG_WPS_UPNP
	if (wps->wps->wps_upnp && wps->ext_reg) {
		wpa_printf(MSG_DEBUG,  "WPS: Negotiation using external "
			   "Registrar completed successfully");
		wps_device_store(wps->wps->registrar, &wps->peer_dev,
				 wps->uuid_e);
		return WPS_DONE;
	}
#endif /* CONFIG_WPS_UPNP */

	if (attr.registrar_nonce == NULL ||
	    os_memcmp(wps->nonce_r, attr.registrar_nonce, WPS_NONCE_LEN) != 0)
	{
		wpa_printf(MSG_DEBUG,  "WPS: Mismatch in registrar nonce");
		return WPS_FAILURE;
	}

	if (attr.enrollee_nonce == NULL ||
	    os_memcmp(wps->nonce_e, attr.enrollee_nonce, WPS_NONCE_LEN) != 0) {
		wpa_printf(MSG_DEBUG,  "WPS: Mismatch in enrollee nonce");
		return WPS_FAILURE;
	}

	wpa_printf(MSG_DEBUG,  "WPS: Negotiation completed successfully");
	wps_device_store(wps->wps->registrar, &wps->peer_dev,
			 wps->uuid_e);

	if (wps->wps->wps_state == WPS_STATE_NOT_CONFIGURED && wps->new_psk &&
	    wps->wps->ap && !wps->wps->registrar->disable_auto_conf) {
		struct wps_credential cred;

		wpa_printf(MSG_DEBUG,  "WPS: Moving to Configured state based "
			   "on first Enrollee connection");

		os_memset(&cred, 0, sizeof(cred));
		os_memcpy(cred.ssid, wps->wps->ssid, wps->wps->ssid_len);
		cred.ssid_len = wps->wps->ssid_len;
		cred.auth_type = WPS_AUTH_WPAPSK | WPS_AUTH_WPA2PSK;
		cred.encr_type = WPS_ENCR_TKIP | WPS_ENCR_AES;
		os_memcpy(cred.key, wps->new_psk, wps->new_psk_len);
		cred.key_len = wps->new_psk_len;

		wps->wps->wps_state = WPS_STATE_CONFIGURED;
		wpa_hexdump_ascii_key(MSG_DEBUG,
				      "WPS: Generated random passphrase",
				      wps->new_psk, wps->new_psk_len);
		if (wps->wps->cred_cb)
			wps->wps->cred_cb(wps->wps->cb_ctx, &cred);

		os_free(wps->new_psk);
		wps->new_psk = NULL;
	}

	if (!wps->wps->ap && !wps->er)
		wps_sta_cred_cb(wps);

	if (wps->new_psk) {
		if (wps_cb_new_psk(wps->wps->registrar, wps->mac_addr_e,
				   wps->new_psk, wps->new_psk_len)) {
			wpa_printf(MSG_DEBUG,  "WPS: Failed to configure the "
				   "new PSK");
		}
		os_free(wps->new_psk);
		wps->new_psk = NULL;
	}

	wps_cb_reg_success(wps->wps->registrar, wps->mac_addr_e, wps->uuid_e,
			   wps->dev_password, wps->dev_password_len);

	if (wps->pbc) {
		wps_registrar_remove_pbc_session(wps->wps->registrar,
						 wps->uuid_e,
						 wps->p2p_dev_addr);
		wps_registrar_pbc_completed(wps->wps->registrar);
		os_get_time(&wps->wps->registrar->pbc_ignore_start);
		os_memcpy(wps->wps->registrar->pbc_ignore_uuid, wps->uuid_e,
			  WPS_UUID_LEN);
	} else {
#ifdef CONFIG_WPS_PIN
		wps_registrar_pin_completed(wps->wps->registrar);
#endif
	}
	/* TODO: maintain AuthorizedMACs somewhere separately for each ER and
	 * merge them into APs own list.. */

	wps_success_event(wps->wps);

	return WPS_DONE;
}