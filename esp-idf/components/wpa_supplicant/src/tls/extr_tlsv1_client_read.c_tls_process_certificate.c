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
typedef  scalar_t__ u8 ;
struct x509_certificate {struct x509_certificate* next; } ;
struct tlsv1_client {int /*<<< orphan*/  state; int /*<<< orphan*/  disable_time_checks; TYPE_1__* cred; int /*<<< orphan*/  server_rsa_key; } ;
struct TYPE_2__ {int /*<<< orphan*/  trusted_certs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SERVER_KEY_EXCHANGE ; 
 int TLS_ALERT_BAD_CERTIFICATE ; 
 int TLS_ALERT_CERTIFICATE_EXPIRED ; 
 int TLS_ALERT_CERTIFICATE_REVOKED ; 
 int TLS_ALERT_CERTIFICATE_UNKNOWN ; 
 int TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int TLS_ALERT_UNEXPECTED_MESSAGE ; 
 int TLS_ALERT_UNKNOWN_CA ; 
 int TLS_ALERT_UNSUPPORTED_CERTIFICATE ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_CERTIFICATE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_CERTIFICATE_REQUEST ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_SERVER_HELLO_DONE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_SERVER_KEY_EXCHANGE ; 
 size_t WPA_GET_BE24 (scalar_t__ const*) ; 
#define  X509_VALIDATE_BAD_CERTIFICATE 133 
#define  X509_VALIDATE_CERTIFICATE_EXPIRED 132 
#define  X509_VALIDATE_CERTIFICATE_REVOKED 131 
#define  X509_VALIDATE_CERTIFICATE_UNKNOWN 130 
#define  X509_VALIDATE_UNKNOWN_CA 129 
#define  X509_VALIDATE_UNSUPPORTED_CERTIFICATE 128 
 int /*<<< orphan*/  crypto_public_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tls_parse_cert (scalar_t__ const*,size_t,int /*<<< orphan*/ *) ; 
 int tls_process_certificate_request (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int tls_process_server_hello_done (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int tls_process_server_key_exchange (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  x509_certificate_chain_free (struct x509_certificate*) ; 
 scalar_t__ x509_certificate_chain_validate (int /*<<< orphan*/ ,struct x509_certificate*,int*,int /*<<< orphan*/ ) ; 
 struct x509_certificate* x509_certificate_parse (scalar_t__ const*,size_t) ; 

__attribute__((used)) static int tls_process_certificate(struct tlsv1_client *conn, u8 ct,
				   const u8 *in_data, size_t *in_len)
{
	const u8 *pos, *end;
	size_t left, len, list_len, cert_len, idx;
	u8 type;
	struct x509_certificate *chain = NULL, *last = NULL, *cert;
	int reason;

	if (ct != TLS_CONTENT_TYPE_HANDSHAKE) {
		wpa_printf(MSG_DEBUG, "TLSv1: Expected Handshake; "
			   "received content type 0x%x", ct);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	pos = in_data;
	left = *in_len;

	if (left < 4) {
		wpa_printf(MSG_DEBUG, "TLSv1: Too short Certificate message "
			   "(len=%lu)", (unsigned long) left);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	type = *pos++;
	len = WPA_GET_BE24(pos);
	pos += 3;
	left -= 4;

	if (len > left) {
		wpa_printf(MSG_DEBUG, "TLSv1: Unexpected Certificate message "
			   "length (len=%lu != left=%lu)",
			   (unsigned long) len, (unsigned long) left);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	if (type == TLS_HANDSHAKE_TYPE_SERVER_KEY_EXCHANGE)
		return tls_process_server_key_exchange(conn, ct, in_data,
						       in_len);
	if (type == TLS_HANDSHAKE_TYPE_CERTIFICATE_REQUEST)
		return tls_process_certificate_request(conn, ct, in_data,
						       in_len);
	if (type == TLS_HANDSHAKE_TYPE_SERVER_HELLO_DONE)
		return tls_process_server_hello_done(conn, ct, in_data,
						     in_len);
	if (type != TLS_HANDSHAKE_TYPE_CERTIFICATE) {
		wpa_printf(MSG_DEBUG, "TLSv1: Received unexpected handshake "
			   "message %d (expected Certificate/"
			   "ServerKeyExchange/CertificateRequest/"
			   "ServerHelloDone)", type);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "TLSv1: Received Certificate (certificate_list len %lu)",
		   (unsigned long) len);

	/*
	 * opaque ASN.1Cert<2^24-1>;
	 *
	 * struct {
	 *     ASN.1Cert certificate_list<1..2^24-1>;
	 * } Certificate;
	 */

	end = pos + len;

	if (end - pos < 3) {
		wpa_printf(MSG_DEBUG, "TLSv1: Too short Certificate "
			   "(left=%lu)", (unsigned long) left);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	list_len = WPA_GET_BE24(pos);
	pos += 3;

	if ((size_t) (end - pos) != list_len) {
		wpa_printf(MSG_DEBUG, "TLSv1: Unexpected certificate_list "
			   "length (len=%lu left=%lu)",
			   (unsigned long) list_len,
			   (unsigned long) (end - pos));
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	idx = 0;
	while (pos < end) {
		if (end - pos < 3) {
			wpa_printf(MSG_DEBUG, "TLSv1: Failed to parse "
				   "certificate_list");
			tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
				  TLS_ALERT_DECODE_ERROR);
			x509_certificate_chain_free(chain);
			return -1;
		}

		cert_len = WPA_GET_BE24(pos);
		pos += 3;

		if ((size_t) (end - pos) < cert_len) {
			wpa_printf(MSG_DEBUG, "TLSv1: Unexpected certificate "
				   "length (len=%lu left=%lu)",
				   (unsigned long) cert_len,
				   (unsigned long) (end - pos));
			tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
				  TLS_ALERT_DECODE_ERROR);
			x509_certificate_chain_free(chain);
			return -1;
		}

		wpa_printf(MSG_DEBUG, "TLSv1: Certificate %lu (len %lu)",
			   (unsigned long) idx, (unsigned long) cert_len);

		if (idx == 0) {
			crypto_public_key_free(conn->server_rsa_key);
			if (tls_parse_cert(pos, cert_len,
					   &conn->server_rsa_key)) {
				wpa_printf(MSG_DEBUG, "TLSv1: Failed to parse "
					   "the certificate");
				tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
					  TLS_ALERT_BAD_CERTIFICATE);
				x509_certificate_chain_free(chain);
				return -1;
			}
		}

		cert = x509_certificate_parse(pos, cert_len);
		if (cert == NULL) {
			wpa_printf(MSG_DEBUG, "TLSv1: Failed to parse "
				   "the certificate");
			tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
				  TLS_ALERT_BAD_CERTIFICATE);
			x509_certificate_chain_free(chain);
			return -1;
		}

		if (last == NULL)
			chain = cert;
		else
			last->next = cert;
		last = cert;

		idx++;
		pos += cert_len;
	}

	if (conn->cred &&
	    x509_certificate_chain_validate(conn->cred->trusted_certs, chain,
					    &reason, conn->disable_time_checks)
	    < 0) {
		int tls_reason;
		wpa_printf(MSG_DEBUG, "TLSv1: Server certificate chain "
			   "validation failed (reason=%d)", reason);
		switch (reason) {
		case X509_VALIDATE_BAD_CERTIFICATE:
			tls_reason = TLS_ALERT_BAD_CERTIFICATE;
			break;
		case X509_VALIDATE_UNSUPPORTED_CERTIFICATE:
			tls_reason = TLS_ALERT_UNSUPPORTED_CERTIFICATE;
			break;
		case X509_VALIDATE_CERTIFICATE_REVOKED:
			tls_reason = TLS_ALERT_CERTIFICATE_REVOKED;
			break;
		case X509_VALIDATE_CERTIFICATE_EXPIRED:
			tls_reason = TLS_ALERT_CERTIFICATE_EXPIRED;
			break;
		case X509_VALIDATE_CERTIFICATE_UNKNOWN:
			tls_reason = TLS_ALERT_CERTIFICATE_UNKNOWN;
			break;
		case X509_VALIDATE_UNKNOWN_CA:
			tls_reason = TLS_ALERT_UNKNOWN_CA;
			break;
		default:
			tls_reason = TLS_ALERT_BAD_CERTIFICATE;
			break;
		}
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, tls_reason);
		x509_certificate_chain_free(chain);
		return -1;
	}

	x509_certificate_chain_free(chain);

	*in_len = end - in_data;
	conn->state = SERVER_KEY_EXCHANGE;

	return 0;
}