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
struct tlsv1_server {int /*<<< orphan*/  state; scalar_t__ use_session_ticket; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_CIPHER_SPEC ; 
 int /*<<< orphan*/  CLIENT_CERTIFICATE ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int tls_server_cert_chain_der_len (struct tlsv1_server*) ; 
 scalar_t__ tls_write_server_certificate (struct tlsv1_server*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_server_certificate_request (struct tlsv1_server*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_server_change_cipher_spec (struct tlsv1_server*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_server_finished (struct tlsv1_server*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_server_hello (struct tlsv1_server*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_server_hello_done (struct tlsv1_server*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_server_key_exchange (struct tlsv1_server*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 * tls_send_server_hello(struct tlsv1_server *conn, size_t *out_len)
{
	u8 *msg, *end, *pos;
	size_t msglen;

	*out_len = 0;

	msglen = 1000 + tls_server_cert_chain_der_len(conn);

	msg = os_malloc(msglen);
	if (msg == NULL)
		return NULL;

	pos = msg;
	end = msg + msglen;

	if (tls_write_server_hello(conn, &pos, end) < 0) {
		os_free(msg);
		return NULL;
	}

	if (conn->use_session_ticket) {
		/* Abbreviated handshake using session ticket; RFC 4507 */
		if (tls_write_server_change_cipher_spec(conn, &pos, end) < 0 ||
		    tls_write_server_finished(conn, &pos, end) < 0) {
			os_free(msg);
			return NULL;
		}

		*out_len = pos - msg;

		conn->state = CHANGE_CIPHER_SPEC;

		return msg;
	}

	/* Full handshake */
	if (tls_write_server_certificate(conn, &pos, end) < 0 ||
	    tls_write_server_key_exchange(conn, &pos, end) < 0 ||
	    tls_write_server_certificate_request(conn, &pos, end) < 0 ||
	    tls_write_server_hello_done(conn, &pos, end) < 0) {
		os_free(msg);
		return NULL;
	}

	*out_len = pos - msg;

	conn->state = CLIENT_CERTIFICATE;

	return msg;
}