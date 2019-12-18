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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct tlsv1_server {size_t dh_secret_len; int /*<<< orphan*/ * dh_secret; TYPE_1__* cred; } ;
struct TYPE_2__ {size_t dh_p_len; int /*<<< orphan*/ * dh_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ crypto_mod_exp (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tlsv1_server_derive_keys (struct tlsv1_server*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_process_client_key_exchange_dh_anon(
	struct tlsv1_server *conn, const u8 *pos, const u8 *end)
{
	const u8 *dh_yc;
	u16 dh_yc_len;
	u8 *shared;
	size_t shared_len;
	int res;

	/*
	 * struct {
	 *   select (PublicValueEncoding) {
	 *     case implicit: struct { };
	 *     case explicit: opaque dh_Yc<1..2^16-1>;
	 *   } dh_public;
	 * } ClientDiffieHellmanPublic;
	 */

	wpa_hexdump(MSG_MSGDUMP, "TLSv1: ClientDiffieHellmanPublic",
		    pos, end - pos);

	if (end == pos) {
		wpa_printf(MSG_DEBUG, "TLSv1: Implicit public value encoding "
			   "not supported");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	if (end - pos < 3) {
		wpa_printf(MSG_DEBUG, "TLSv1: Invalid client public value "
			   "length");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	dh_yc_len = WPA_GET_BE16(pos);
	dh_yc = pos + 2;

	if (dh_yc + dh_yc_len > end) {
		wpa_printf(MSG_DEBUG, "TLSv1: Client public value overflow "
			   "(length %d)", dh_yc_len);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	wpa_hexdump(MSG_DEBUG, "TLSv1: DH Yc (client's public value)",
		    dh_yc, dh_yc_len);

	if (conn->cred == NULL || conn->cred->dh_p == NULL ||
	    conn->dh_secret == NULL) {
		wpa_printf(MSG_DEBUG, "TLSv1: No DH parameters available");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	shared_len = conn->cred->dh_p_len;
	shared = os_malloc(shared_len);
	if (shared == NULL) {
		wpa_printf(MSG_DEBUG, "TLSv1: Could not allocate memory for "
			   "DH");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	/* shared = Yc^secret mod p */
	if (crypto_mod_exp(dh_yc, dh_yc_len, conn->dh_secret,
					        conn->dh_secret_len,
					        conn->cred->dh_p, conn->cred->dh_p_len,
					        shared, &shared_len)) {
		os_free(shared);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
			TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	wpa_hexdump_key(MSG_DEBUG, "TLSv1: Shared secret from DH key exchange",
			shared, shared_len);

	os_memset(conn->dh_secret, 0, conn->dh_secret_len);
	os_free(conn->dh_secret);
	conn->dh_secret = NULL;

	res = tlsv1_server_derive_keys(conn, shared, shared_len);

	/* Clear the pre-master secret since it is not needed anymore */
	os_memset(shared, 0, shared_len);
	os_free(shared);

	if (res) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to derive keys");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	return 0;
}