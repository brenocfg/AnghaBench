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
struct wps_data {int /*<<< orphan*/  authkey; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  WPS_AUTHKEY_LEN ; 
 int WPS_KWA_LEN ; 
 int /*<<< orphan*/  hmac_sha256 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 

int wps_process_key_wrap_auth(struct wps_data *wps, struct wpabuf *msg,
			      const u8 *key_wrap_auth)
{
	u8 hash[SHA256_MAC_LEN];
	const u8 *head;
	size_t len;

	if (key_wrap_auth == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No KWA in decrypted attribute");
		return -1;
	}

	head = wpabuf_head(msg);
	len = wpabuf_len(msg) - 4 - WPS_KWA_LEN;
	if (head + len != key_wrap_auth - 4) {
		wpa_printf(MSG_DEBUG,  "WPS: KWA not in the end of the "
			   "decrypted attribute");
		return -1;
	}

	hmac_sha256(wps->authkey, WPS_AUTHKEY_LEN, head, len, hash);
	if (os_memcmp(hash, key_wrap_auth, WPS_KWA_LEN) != 0) {
		wpa_printf(MSG_DEBUG,  "WPS: Invalid KWA");
		return -1;
	}

	return 0;
}