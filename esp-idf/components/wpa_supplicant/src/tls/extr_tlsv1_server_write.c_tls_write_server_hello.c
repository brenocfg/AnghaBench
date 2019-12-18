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
struct TYPE_2__ {int /*<<< orphan*/  tls_version; } ;
struct tlsv1_server {int (* session_ticket_cb ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int use_session_ticket; TYPE_1__ rl; int /*<<< orphan*/  verify; int /*<<< orphan*/  master_secret; int /*<<< orphan*/  server_random; int /*<<< orphan*/  client_random; int /*<<< orphan*/  session_ticket_len; scalar_t__ session_ticket; int /*<<< orphan*/  session_ticket_cb_ctx; int /*<<< orphan*/  cipher_suite; scalar_t__ session_id_len; int /*<<< orphan*/  session_id; } ;
struct os_time {int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  TLS_ALERT_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 scalar_t__ TLS_COMPRESSION_NULL ; 
 int /*<<< orphan*/  TLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  TLS_HANDSHAKE_TYPE_SERVER_HELLO ; 
 scalar_t__ TLS_RANDOM_LEN ; 
 int /*<<< orphan*/  TLS_RECORD_HEADER_LEN ; 
 scalar_t__ TLS_SESSION_ID_MAX_LEN ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_verify_hash_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tlsv1_record_send (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tlsv1_server_derive_keys (struct tlsv1_server*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_write_server_hello(struct tlsv1_server *conn,
				  u8 **msgpos, u8 *end)
{
	u8 *pos, *rhdr, *hs_start, *hs_length;
	struct os_time now;
	size_t rlen;

	pos = *msgpos;

	wpa_printf(MSG_DEBUG, "TLSv1: Send ServerHello");
	rhdr = pos;
	pos += TLS_RECORD_HEADER_LEN;

	os_get_time(&now);
	WPA_PUT_BE32(conn->server_random, now.sec);
	if (random_get_bytes(conn->server_random + 4, TLS_RANDOM_LEN - 4)) {
		wpa_printf(MSG_ERROR, "TLSv1: Could not generate "
			   "server_random");
		return -1;
	}
	wpa_hexdump(MSG_MSGDUMP, "TLSv1: server_random",
		    conn->server_random, TLS_RANDOM_LEN);

	conn->session_id_len = TLS_SESSION_ID_MAX_LEN;
	if (random_get_bytes(conn->session_id, conn->session_id_len)) {
		wpa_printf(MSG_ERROR, "TLSv1: Could not generate "
			   "session_id");
		return -1;
	}
	wpa_hexdump(MSG_MSGDUMP, "TLSv1: session_id",
		    conn->session_id, conn->session_id_len);

	/* opaque fragment[TLSPlaintext.length] */

	/* Handshake */
	hs_start = pos;
	/* HandshakeType msg_type */
	*pos++ = TLS_HANDSHAKE_TYPE_SERVER_HELLO;
	/* uint24 length (to be filled) */
	hs_length = pos;
	pos += 3;
	/* body - ServerHello */
	/* ProtocolVersion server_version */
	WPA_PUT_BE16(pos, conn->rl.tls_version);
	pos += 2;
	/* Random random: uint32 gmt_unix_time, opaque random_bytes */
	os_memcpy(pos, conn->server_random, TLS_RANDOM_LEN);
	pos += TLS_RANDOM_LEN;
	/* SessionID session_id */
	*pos++ = conn->session_id_len;
	os_memcpy(pos, conn->session_id, conn->session_id_len);
	pos += conn->session_id_len;
	/* CipherSuite cipher_suite */
	WPA_PUT_BE16(pos, conn->cipher_suite);
	pos += 2;
	/* CompressionMethod compression_method */
	*pos++ = TLS_COMPRESSION_NULL;

	if (conn->session_ticket && conn->session_ticket_cb) {
		int res = conn->session_ticket_cb(
			conn->session_ticket_cb_ctx,
			conn->session_ticket, conn->session_ticket_len,
			conn->client_random, conn->server_random,
			conn->master_secret);
		if (res < 0) {
			wpa_printf(MSG_DEBUG, "TLSv1: SessionTicket callback "
				   "indicated failure");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_HANDSHAKE_FAILURE);
			return -1;
		}
		conn->use_session_ticket = res;

		if (conn->use_session_ticket) {
			if (tlsv1_server_derive_keys(conn, NULL, 0) < 0) {
				wpa_printf(MSG_DEBUG, "TLSv1: Failed to "
					   "derive keys");
				tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
						   TLS_ALERT_INTERNAL_ERROR);
				return -1;
			}
		}

		/*
		 * RFC 4507 specifies that server would include an empty
		 * SessionTicket extension in ServerHello and a
		 * NewSessionTicket message after the ServerHello. However,
		 * EAP-FAST (RFC 4851), i.e., the only user of SessionTicket
		 * extension at the moment, does not use such extensions.
		 *
		 * TODO: Add support for configuring RFC 4507 behavior and make
		 * EAP-FAST disable it.
		 */
	}

	WPA_PUT_BE24(hs_length, pos - hs_length - 3);
	tls_verify_hash_add(&conn->verify, hs_start, pos - hs_start);

	if (tlsv1_record_send(&conn->rl, TLS_CONTENT_TYPE_HANDSHAKE,
			      rhdr, end - rhdr, hs_start, pos - hs_start,
			      &rlen) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to create TLS record");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	pos = rhdr + rlen;

	*msgpos = pos;

	return 0;
}