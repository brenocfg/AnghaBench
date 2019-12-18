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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct wpa_ie_hdr {int len; int /*<<< orphan*/ * version; int /*<<< orphan*/ * oui; int /*<<< orphan*/  elem_id; } ;
struct wpa_auth_config {int wpa_group; int wpa_pairwise; int wpa_key_mgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RSN_SELECTOR_PUT (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 scalar_t__ WPA_AUTH_KEY_MGMT_PSK_OVER_802_1X ; 
 scalar_t__ WPA_AUTH_KEY_MGMT_UNSPEC_802_1X ; 
 int WPA_KEY_MGMT_IEEE8021X ; 
 int WPA_KEY_MGMT_PSK ; 
 scalar_t__ WPA_OUI_TYPE ; 
 int /*<<< orphan*/  WPA_PROTO_WPA ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (int /*<<< orphan*/ *,int) ; 
 int WPA_SELECTOR_LEN ; 
 int WPA_VERSION ; 
 int wpa_cipher_put_suites (int /*<<< orphan*/ *,int) ; 
 scalar_t__ wpa_cipher_to_suite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int wpa_write_wpa_ie(struct wpa_auth_config *conf, u8 *buf, size_t len)
{
	struct wpa_ie_hdr *hdr;
	int num_suites;
	u8 *pos, *count;
	u32 suite;

	hdr = (struct wpa_ie_hdr *) buf;
	hdr->elem_id = WLAN_EID_VENDOR_SPECIFIC;
	RSN_SELECTOR_PUT(hdr->oui, WPA_OUI_TYPE);
	WPA_PUT_LE16(hdr->version, WPA_VERSION);
	pos = (u8 *) (hdr + 1);

	suite = wpa_cipher_to_suite(WPA_PROTO_WPA, conf->wpa_group);
	if (suite == 0) {
		wpa_printf( MSG_DEBUG, "Invalid group cipher (%d).",
			   conf->wpa_group);
		return -1;
	}
	RSN_SELECTOR_PUT(pos, suite);
	pos += WPA_SELECTOR_LEN;

	count = pos;
	pos += 2;

	num_suites = wpa_cipher_put_suites(pos, conf->wpa_pairwise);
	if (num_suites == 0) {
		wpa_printf( MSG_DEBUG, "Invalid pairwise cipher (%d).",
			   conf->wpa_pairwise);
		return -1;
	}
	pos += num_suites * WPA_SELECTOR_LEN;
	WPA_PUT_LE16(count, num_suites);

	num_suites = 0;
	count = pos;
	pos += 2;

	if (conf->wpa_key_mgmt & WPA_KEY_MGMT_IEEE8021X) {
		RSN_SELECTOR_PUT(pos, WPA_AUTH_KEY_MGMT_UNSPEC_802_1X);
		pos += WPA_SELECTOR_LEN;
		num_suites++;
	}
	if (conf->wpa_key_mgmt & WPA_KEY_MGMT_PSK) {
		RSN_SELECTOR_PUT(pos, WPA_AUTH_KEY_MGMT_PSK_OVER_802_1X);
		pos += WPA_SELECTOR_LEN;
		num_suites++;
	}

	if (num_suites == 0) {
		wpa_printf( MSG_DEBUG, "Invalid key management type (%d).",
			   conf->wpa_key_mgmt);
		return -1;
	}
	WPA_PUT_LE16(count, num_suites);

	/* WPA Capabilities; use defaults, so no need to include it */

	hdr->len = (pos - buf) - 2;

	return pos - buf;
}