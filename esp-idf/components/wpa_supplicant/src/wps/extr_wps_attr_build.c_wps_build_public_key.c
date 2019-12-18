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
typedef  scalar_t__ wps_key_mode_t ;
struct wps_data {int dev_pw_id; struct wpabuf* dh_pubkey_e; struct wpabuf* dh_pubkey_r; scalar_t__ registrar; struct wpabuf* dh_privkey; int /*<<< orphan*/ * dh_ctx; TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int ap_nfc_dev_pw_id; scalar_t__ ap_nfc_dh_pubkey; scalar_t__ ap_nfc_dh_privkey; scalar_t__ ap; scalar_t__ dh_pubkey; int /*<<< orphan*/ * dh_ctx; scalar_t__ dh_privkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_PUBLIC_KEY ; 
 int DEV_PW_DEFAULT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPS_CALC_KEY_NO_CALC ; 
 scalar_t__ WPS_CALC_KEY_PRE_CALC ; 
 int /*<<< orphan*/  dh5_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dh5_init (struct wpabuf**,struct wpabuf**) ; 
 int /*<<< orphan*/ * dh5_init_fixed (struct wpabuf*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 void* wpabuf_dup (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_zeropad (struct wpabuf*,int) ; 

int wps_build_public_key(struct wps_data *wps, struct wpabuf *msg, wps_key_mode_t mode)
{
	struct wpabuf *pubkey;

	if (mode != WPS_CALC_KEY_NO_CALC) {

		wpa_printf(MSG_DEBUG,  "WPS:  * Public Key");
		wpabuf_free(wps->dh_privkey);
		if (wps->dev_pw_id != DEV_PW_DEFAULT && wps->wps->dh_privkey) {
			wpa_printf(MSG_DEBUG,  "WPS: Using pre-configured DH keys");
			wps->dh_privkey = wpabuf_dup(wps->wps->dh_privkey);
			wps->dh_ctx = wps->wps->dh_ctx;
			wps->wps->dh_ctx = NULL;
			pubkey = wpabuf_dup(wps->wps->dh_pubkey);
#ifdef CONFIG_WPS_NFC
		} else if (wps->dev_pw_id >= 0x10 && wps->wps->ap &&
				wps->dev_pw_id == wps->wps->ap_nfc_dev_pw_id) {
			wpa_printf(MSG_DEBUG,  "WPS: Using NFC password token DH keys");
			wps->dh_privkey = wpabuf_dup(wps->wps->ap_nfc_dh_privkey);
			pubkey = wpabuf_dup(wps->wps->ap_nfc_dh_pubkey);
			wps->dh_ctx = dh5_init_fixed(wps->dh_privkey, pubkey);
#endif /* CONFIG_WPS_NFC */
		} else {
			wpa_printf(MSG_DEBUG,  "WPS: Generate new DH keys");
			wps->dh_privkey = NULL;
			dh5_free(wps->dh_ctx);

			wpa_printf(MSG_DEBUG, "build public key start\n");

			wps->dh_ctx = dh5_init(&wps->dh_privkey, &pubkey);

			wpa_printf(MSG_DEBUG, "build public key finish\n");

			pubkey = wpabuf_zeropad(pubkey, 192);
		}
		if (wps->dh_ctx == NULL || wps->dh_privkey == NULL || pubkey == NULL) {
			wpa_printf(MSG_DEBUG,  "WPS: Failed to initialize "
					"Diffie-Hellman handshake");
			wpabuf_free(pubkey);
			return -1;
		}
		wpa_hexdump_buf_key(MSG_DEBUG, "WPS: DH Private Key", wps->dh_privkey);
		wpa_hexdump_buf(MSG_DEBUG, "WPS: DH own Public Key", pubkey);

		if (wps->registrar) {
			wpabuf_free(wps->dh_pubkey_r);
			wps->dh_pubkey_r = pubkey;
		} else {
			wpabuf_free(wps->dh_pubkey_e);
			wps->dh_pubkey_e = pubkey;
		}

	}

	if (mode != WPS_CALC_KEY_PRE_CALC) {
		if (wps->registrar)
			pubkey = wps->dh_pubkey_r;
		else
			pubkey = wps->dh_pubkey_e;

		wpabuf_put_be16(msg, ATTR_PUBLIC_KEY);
		wpabuf_put_be16(msg, wpabuf_len(pubkey));
		wpabuf_put_buf(msg, pubkey);
	}

	return 0;
}