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
typedef  scalar_t__ u8 ;
struct tlsv1_client {int state; int /*<<< orphan*/  verify; } ;

/* Variables and functions */
#define  ACK_FINISHED 135 
 int FAILED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  SERVER_CERTIFICATE 134 
#define  SERVER_CERTIFICATE_REQUEST 133 
#define  SERVER_CHANGE_CIPHER_SPEC 132 
#define  SERVER_FINISHED 131 
#define  SERVER_HELLO 130 
#define  SERVER_HELLO_DONE 129 
#define  SERVER_KEY_EXCHANGE 128 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 scalar_t__ TLS_CONTENT_TYPE_ALERT ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 scalar_t__ const TLS_HANDSHAKE_TYPE_HELLO_REQUEST ; 
 size_t WPA_GET_BE24 (scalar_t__ const*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_process_application_data (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*,scalar_t__**,size_t*) ; 
 int /*<<< orphan*/  tls_process_certificate (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_certificate_request (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_server_change_cipher_spec (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_server_finished (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_server_hello (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_server_hello_done (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_server_key_exchange (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_verify_hash_add (int /*<<< orphan*/ *,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int tlsv1_client_process_handshake(struct tlsv1_client *conn, u8 ct,
				   const u8 *buf, size_t *len,
				   u8 **out_data, size_t *out_len)
{
	if (ct == TLS_CONTENT_TYPE_ALERT) {
		if (*len < 2) {
			wpa_printf(MSG_DEBUG, "TLSv1: Alert underflow");
			tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
				  TLS_ALERT_DECODE_ERROR);
			return -1;
		}
		wpa_printf(MSG_DEBUG, "TLSv1: Received alert %d:%d",
			   buf[0], buf[1]);
		*len = 2;
		conn->state = FAILED;
		return -1;
	}

	if (ct == TLS_CONTENT_TYPE_HANDSHAKE && *len >= 4 &&
	    buf[0] == TLS_HANDSHAKE_TYPE_HELLO_REQUEST) {
		size_t hr_len = WPA_GET_BE24(buf + 1);
		if (hr_len > *len - 4) {
			wpa_printf(MSG_DEBUG, "TLSv1: HelloRequest underflow");
			tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
				  TLS_ALERT_DECODE_ERROR);
			return -1;
		}
		wpa_printf(MSG_DEBUG, "TLSv1: Ignored HelloRequest");
		*len = 4 + hr_len;
		return 0;
	}

	switch (conn->state) {
	case SERVER_HELLO:
		if (tls_process_server_hello(conn, ct, buf, len))
			return -1;
		break;
	case SERVER_CERTIFICATE:
		if (tls_process_certificate(conn, ct, buf, len))
			return -1;
		break;
	case SERVER_KEY_EXCHANGE:
		if (tls_process_server_key_exchange(conn, ct, buf, len))
			return -1;
		break;
	case SERVER_CERTIFICATE_REQUEST:
		if (tls_process_certificate_request(conn, ct, buf, len))
			return -1;
		break;
	case SERVER_HELLO_DONE:
		if (tls_process_server_hello_done(conn, ct, buf, len))
			return -1;
		break;
	case SERVER_CHANGE_CIPHER_SPEC:
		if (tls_process_server_change_cipher_spec(conn, ct, buf, len))
			return -1;
		break;
	case SERVER_FINISHED:
		if (tls_process_server_finished(conn, ct, buf, len)) {
			printf("[debug] server finish process fall \n");
			return -1;
		}
		break;
	case ACK_FINISHED:
		if (out_data &&
		    tls_process_application_data(conn, ct, buf, len, out_data,
						 out_len))
			return -1;
		break;
	default:
		wpa_printf(MSG_DEBUG, "TLSv1: Unexpected state %d "
			   "while processing received message",
			   conn->state);
		return -1;
	}

	if (ct == TLS_CONTENT_TYPE_HANDSHAKE) {
		tls_verify_hash_add(&conn->verify, buf, *len);
	}

	return 0;
}