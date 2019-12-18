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
struct tlsv1_client {int /*<<< orphan*/ * server_rsa_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int TLS_PRE_MASTER_SECRET_LEN ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,size_t) ; 
 int crypto_public_key_encrypt_pkcs1_v15 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_derive_keys (struct tlsv1_client*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tls_derive_pre_master_secret (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tlsv1_key_x_rsa(struct tlsv1_client *conn, u8 **pos, u8 *end)
{
	u8 pre_master_secret[TLS_PRE_MASTER_SECRET_LEN];
	size_t clen;
	int res;

	if (tls_derive_pre_master_secret(pre_master_secret) < 0 ||
	    tls_derive_keys(conn, pre_master_secret,
			    TLS_PRE_MASTER_SECRET_LEN)) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to derive keys");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	/* EncryptedPreMasterSecret */
	if (conn->server_rsa_key == NULL) {
		wpa_printf(MSG_DEBUG, "TLSv1: No server RSA key to "
			   "use for encrypting pre-master secret");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	/* RSA encrypted value is encoded with PKCS #1 v1.5 block type 2. */
	*pos += 2;
	clen = end - *pos;
	res = crypto_public_key_encrypt_pkcs1_v15(
		conn->server_rsa_key,
		pre_master_secret, TLS_PRE_MASTER_SECRET_LEN,
		*pos, &clen);
	os_memset(pre_master_secret, 0, TLS_PRE_MASTER_SECRET_LEN);
	if (res < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: RSA encryption failed");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	WPA_PUT_BE16(*pos - 2, clen);
	wpa_hexdump(MSG_MSGDUMP, "TLSv1: Encrypted pre_master_secret",
		    *pos, clen);
	*pos += clen;

	return 0;
}