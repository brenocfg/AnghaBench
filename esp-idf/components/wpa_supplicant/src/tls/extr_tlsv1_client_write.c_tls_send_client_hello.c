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
struct tlsv1_client {int num_cipher_suites; int client_hello_ext_len; int session_id_len; int* cipher_suites; int /*<<< orphan*/  state; int /*<<< orphan*/  rl; int /*<<< orphan*/  verify; int /*<<< orphan*/  client_hello_ext; int /*<<< orphan*/  session_id; int /*<<< orphan*/  client_random; } ;
struct os_time {int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  SERVER_HELLO ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_COMPRESSION_NULL ; 
 int /*<<< orphan*/  TLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  TLS_HANDSHAKE_TYPE_CLIENT_HELLO ; 
 int TLS_RANDOM_LEN ; 
 int TLS_RECORD_HEADER_LEN ; 
 int TLS_VERSION ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_verify_hash_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tlsv1_record_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

u8 * tls_send_client_hello(struct tlsv1_client *conn, size_t *out_len)
{
	u8 *hello, *end, *pos, *hs_length, *hs_start, *rhdr;
	struct os_time now;
	size_t len, i;

	wpa_printf(MSG_DEBUG, "TLSv1: Send ClientHello");
	*out_len = 0;

	os_get_time(&now);
	WPA_PUT_BE32(conn->client_random, now.sec);
	if (random_get_bytes(conn->client_random + 4, TLS_RANDOM_LEN - 4)) {
		wpa_printf(MSG_ERROR, "TLSv1: Could not generate "
			   "client_random");
		return NULL;
	}
	wpa_hexdump(MSG_MSGDUMP, "TLSv1: client_random",
		    conn->client_random, TLS_RANDOM_LEN);

	len = 100 + conn->num_cipher_suites * 2 + conn->client_hello_ext_len;
	hello = os_malloc(len);
	if (hello == NULL)
		return NULL;
	end = hello + len;

	rhdr = hello;
	pos = rhdr + TLS_RECORD_HEADER_LEN;

	/* opaque fragment[TLSPlaintext.length] */

	/* Handshake */
	hs_start = pos;
	/* HandshakeType msg_type */
	*pos++ = TLS_HANDSHAKE_TYPE_CLIENT_HELLO;
	/* uint24 length (to be filled) */
	hs_length = pos;
	pos += 3;
	/* body - ClientHello */
	/* ProtocolVersion client_version */
	WPA_PUT_BE16(pos, TLS_VERSION);
	pos += 2;
	/* Random random: uint32 gmt_unix_time, opaque random_bytes */
	os_memcpy(pos, conn->client_random, TLS_RANDOM_LEN);
	pos += TLS_RANDOM_LEN;
	/* SessionID session_id */
	*pos++ = conn->session_id_len;
	os_memcpy(pos, conn->session_id, conn->session_id_len);
	pos += conn->session_id_len;
	/* CipherSuite cipher_suites<2..2^16-1> */
	WPA_PUT_BE16(pos, 2 * conn->num_cipher_suites);
	pos += 2;
	for (i = 0; i < conn->num_cipher_suites; i++) {
		WPA_PUT_BE16(pos, conn->cipher_suites[i]);
		pos += 2;
	}
	/* CompressionMethod compression_methods<1..2^8-1> */
	*pos++ = 1;
	*pos++ = TLS_COMPRESSION_NULL;

	if (conn->client_hello_ext) {
		os_memcpy(pos, conn->client_hello_ext,
			  conn->client_hello_ext_len);
		pos += conn->client_hello_ext_len;
	}

	WPA_PUT_BE24(hs_length, pos - hs_length - 3);
	tls_verify_hash_add(&conn->verify, hs_start, pos - hs_start);

	if (tlsv1_record_send(&conn->rl, TLS_CONTENT_TYPE_HANDSHAKE,
			      rhdr, end - rhdr, hs_start, pos - hs_start,
			      out_len) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to create TLS record");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_INTERNAL_ERROR);
		os_free(hello);
		return NULL;
	}

	conn->state = SERVER_HELLO;

	return hello;
}