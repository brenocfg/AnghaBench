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
typedef  char u8 ;
struct wps_credential {int ssid_len; int auth_type; int encr_type; int key_len; struct wps_credential* mac_addr; struct wps_credential* key; struct wps_credential* ssid; } ;
struct wps_data {char* use_cred; int auth_type; int encr_type; char* mac_addr_e; char* new_psk; int new_psk_len; TYPE_2__* wps; struct wps_credential cred; scalar_t__ use_psk_key; } ;
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  r ;
typedef  int /*<<< orphan*/  dummy ;
struct TYPE_4__ {char* ssid; int ssid_len; scalar_t__ wps_state; char* network_key; int network_key_len; TYPE_1__* registrar; scalar_t__ psk_set; scalar_t__ ap; } ;
struct TYPE_3__ {struct wpabuf* extra_cred; int /*<<< orphan*/  disable_auto_conf; scalar_t__ skip_cred_build; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CRED ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPS_AUTH_SHARED ; 
 int WPS_AUTH_WPA2PSK ; 
 int WPS_AUTH_WPAPSK ; 
 int WPS_ENCR_AES ; 
 int WPS_ENCR_NONE ; 
 int WPS_ENCR_TKIP ; 
 int WPS_ENCR_WEP ; 
 scalar_t__ WPS_STATE_NOT_CONFIGURED ; 
 int WPS_WIFI_AUTH_OPEN ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (struct wps_credential*,char*,int) ; 
 int /*<<< orphan*/  os_memset (struct wps_credential*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ random_get_bytes (char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 scalar_t__ wps_build_credential (struct wpabuf*,struct wps_credential*) ; 
 scalar_t__ wps_testing_dummy_cred ; 

int wps_build_cred(struct wps_data *wps, struct wpabuf *msg)
{
	struct wpabuf *cred;

	if (wps->wps->registrar->skip_cred_build)
		goto skip_cred_build;

	wpa_printf(MSG_DEBUG,  "WPS:  * Credential");
	if (wps->use_cred) {
		os_memcpy(&wps->cred, wps->use_cred, sizeof(wps->cred));
		goto use_provided;
	}
	os_memset(&wps->cred, 0, sizeof(wps->cred));

	os_memcpy(wps->cred.ssid, wps->wps->ssid, wps->wps->ssid_len);
	wps->cred.ssid_len = wps->wps->ssid_len;

	/* Select the best authentication and encryption type */
	if (wps->auth_type & WPS_AUTH_WPA2PSK)
		wps->auth_type = WPS_AUTH_WPA2PSK;
	else if (wps->auth_type & WPS_AUTH_WPAPSK)
		wps->auth_type = WPS_AUTH_WPAPSK;
	else if (wps->auth_type & WPS_WIFI_AUTH_OPEN)
		wps->auth_type = WPS_WIFI_AUTH_OPEN;
	else if (wps->auth_type & WPS_AUTH_SHARED)
		wps->auth_type = WPS_AUTH_SHARED;
	else {
		wpa_printf(MSG_DEBUG,  "WPS: Unsupported auth_type 0x%x",
			   wps->auth_type);
		return -1;
	}
	wps->cred.auth_type = wps->auth_type;

	if (wps->auth_type == WPS_AUTH_WPA2PSK ||
	    wps->auth_type == WPS_AUTH_WPAPSK) {
		if (wps->encr_type & WPS_ENCR_AES)
			wps->encr_type = WPS_ENCR_AES;
		else if (wps->encr_type & WPS_ENCR_TKIP)
			wps->encr_type = WPS_ENCR_TKIP;
		else {
			wpa_printf(MSG_DEBUG,  "WPS: No suitable encryption "
				   "type for WPA/WPA2");
			return -1;
		}
	} else {
		if (wps->encr_type & WPS_ENCR_WEP)
			wps->encr_type = WPS_ENCR_WEP;
		else if (wps->encr_type & WPS_ENCR_NONE)
			wps->encr_type = WPS_ENCR_NONE;
		else {
			wpa_printf(MSG_DEBUG,  "WPS: No suitable encryption "
				   "type for non-WPA/WPA2 mode");
			return -1;
		}
	}
	wps->cred.encr_type = wps->encr_type;
	/*
	 * Set MAC address in the Credential to be the Enrollee's MAC address
	 */
	os_memcpy(wps->cred.mac_addr, wps->mac_addr_e, ETH_ALEN);

	if (wps->wps->wps_state == WPS_STATE_NOT_CONFIGURED && wps->wps->ap &&
	    !wps->wps->registrar->disable_auto_conf) {
		u8 r[16];
		/* Generate a random passphrase */
		if (random_get_bytes(r, sizeof(r)) < 0)
			return -1;
		os_free(wps->new_psk);
		if (wps->new_psk == NULL)
			return -1;
		wps->new_psk_len--; /* remove newline */
		while (wps->new_psk_len &&
		       wps->new_psk[wps->new_psk_len - 1] == '=')
			wps->new_psk_len--;
		wpa_hexdump_ascii_key(MSG_DEBUG, "WPS: Generated passphrase",
				      wps->new_psk, wps->new_psk_len);
		os_memcpy(wps->cred.key, wps->new_psk, wps->new_psk_len);
		wps->cred.key_len = wps->new_psk_len;
	} else if (wps->use_psk_key && wps->wps->psk_set) {
		char hex[65];
		wpa_printf(MSG_DEBUG,  "WPS: Use PSK format for Network Key");
		os_memcpy(wps->cred.key, hex, 32 * 2);
		wps->cred.key_len = 32 * 2;
	} else if (wps->wps->network_key) {
		os_memcpy(wps->cred.key, wps->wps->network_key,
			  wps->wps->network_key_len);
		wps->cred.key_len = wps->wps->network_key_len;
	} else if (wps->auth_type & (WPS_AUTH_WPAPSK | WPS_AUTH_WPA2PSK)) {
		char hex[65];
		/* Generate a random per-device PSK */
		os_free(wps->new_psk);
		wps->new_psk_len = 32;
		wps->new_psk = (u8 *)os_malloc(wps->new_psk_len);
		if (wps->new_psk == NULL)
			return -1;
		if (random_get_bytes(wps->new_psk, wps->new_psk_len) < 0) {
			os_free(wps->new_psk);
			wps->new_psk = NULL;
			return -1;
		}
		wpa_hexdump_key(MSG_DEBUG, "WPS: Generated per-device PSK",
				wps->new_psk, wps->new_psk_len);
		os_memcpy(wps->cred.key, hex, wps->new_psk_len * 2);
		wps->cred.key_len = wps->new_psk_len * 2;
	}

use_provided:
#ifdef CONFIG_WPS_TESTING
	if (wps_testing_dummy_cred)
		cred = wpabuf_alloc(200);
	else
		cred = NULL;
	if (cred) {
		struct wps_credential dummy;
		wpa_printf(MSG_DEBUG,  "WPS: Add dummy credential");
		os_memset(&dummy, 0, sizeof(dummy));
		os_memcpy(dummy.ssid, "dummy", 5);
		dummy.ssid_len = 5;
		dummy.auth_type = WPS_AUTH_WPA2PSK;
		dummy.encr_type = WPS_ENCR_AES;
		os_memcpy(dummy.key, "dummy psk", 9);
		dummy.key_len = 9;
		os_memcpy(dummy.mac_addr, wps->mac_addr_e, ETH_ALEN);
		wps_build_credential(cred, &dummy);
		wpa_hexdump_buf(MSG_DEBUG, "WPS: Dummy Credential", cred);

		wpabuf_put_be16(msg, ATTR_CRED);
		wpabuf_put_be16(msg, wpabuf_len(cred));
		wpabuf_put_buf(msg, cred);

		wpabuf_free(cred);
	}
#endif /* CONFIG_WPS_TESTING */

	cred = wpabuf_alloc(200);
	if (cred == NULL)
		return -1;

	if (wps_build_credential(cred, &wps->cred)) {
		wpabuf_free(cred);
		return -1;
	}

	wpabuf_put_be16(msg, ATTR_CRED);
	wpabuf_put_be16(msg, wpabuf_len(cred));
	wpabuf_put_buf(msg, cred);
	wpabuf_free(cred);

skip_cred_build:
	if (wps->wps->registrar->extra_cred) {
		wpa_printf(MSG_DEBUG,  "WPS:  * Credential (pre-configured)");
		wpabuf_put_buf(msg, wps->wps->registrar->extra_cred);
	}

	return 0;
}