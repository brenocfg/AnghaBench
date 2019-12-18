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
struct wps_data {int /*<<< orphan*/  wps; int /*<<< orphan*/  config_error; int /*<<< orphan*/  peer_hash1; int /*<<< orphan*/  authkey; int /*<<< orphan*/  dh_pubkey_r; int /*<<< orphan*/  dh_pubkey_e; int /*<<< orphan*/ * psk1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  WPS_AUTHKEY_LEN ; 
 int /*<<< orphan*/  WPS_CFG_DEV_PASSWORD_AUTH_FAILURE ; 
 int /*<<< orphan*/  WPS_HASH_LEN ; 
 size_t WPS_PSK_LEN ; 
 size_t WPS_SECRET_NONCE_LEN ; 
 int /*<<< orphan*/  hmac_sha256_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_head (int /*<<< orphan*/ ) ; 
 size_t wpabuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_pwd_auth_fail_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wps_process_e_snonce1(struct wps_data *wps, const u8 *e_snonce1)
{
	u8 hash[SHA256_MAC_LEN];
	const u8 *addr[4];
	size_t len[4];

	if (e_snonce1 == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No E-SNonce1 received");
		return -1;
	}

	wpa_hexdump_key(MSG_DEBUG, "WPS: E-SNonce1", e_snonce1,
			WPS_SECRET_NONCE_LEN);

	/* E-Hash1 = HMAC_AuthKey(E-S1 || PSK1 || PK_E || PK_R) */
	addr[0] = e_snonce1;
	len[0] = WPS_SECRET_NONCE_LEN;
	addr[1] = wps->psk1;
	len[1] = WPS_PSK_LEN;
	addr[2] = wpabuf_head(wps->dh_pubkey_e);
	len[2] = wpabuf_len(wps->dh_pubkey_e);
	addr[3] = wpabuf_head(wps->dh_pubkey_r);
	len[3] = wpabuf_len(wps->dh_pubkey_r);
	hmac_sha256_vector(wps->authkey, WPS_AUTHKEY_LEN, 4, addr, len, hash);
	if (os_memcmp(wps->peer_hash1, hash, WPS_HASH_LEN) != 0) {
		wpa_printf(MSG_DEBUG,  "WPS: E-Hash1 derived from E-S1 does "
			   "not match with the pre-committed value");
		wps->config_error = WPS_CFG_DEV_PASSWORD_AUTH_FAILURE;
		wps_pwd_auth_fail_event(wps->wps, 0, 1);
		return -1;
	}

	wpa_printf(MSG_DEBUG,  "WPS: Enrollee proved knowledge of the first "
		   "half of the device password");

	return 0;
}