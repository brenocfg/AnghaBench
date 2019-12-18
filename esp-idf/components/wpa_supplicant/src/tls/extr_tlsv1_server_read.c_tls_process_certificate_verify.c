#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ tls_version; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sha1_cert; int /*<<< orphan*/ * md5_cert; int /*<<< orphan*/ * sha256_cert; } ;
struct tlsv1_server {int /*<<< orphan*/  state; TYPE_2__ rl; int /*<<< orphan*/ * client_rsa_key; TYPE_1__ verify; scalar_t__ verify_peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_CIPHER_SPEC ; 
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int SHA1_MAC_LEN ; 
 size_t SHA256_MAC_LEN ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_DECRYPT_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_ALERT_UNEXPECTED_MESSAGE ; 
 scalar_t__ TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_CERTIFICATE_VERIFY ; 
 scalar_t__ const TLS_HASH_ALG_SHA256 ; 
 scalar_t__ const TLS_SIGN_ALG_RSA ; 
 scalar_t__ TLS_VERSION_1_2 ; 
 int WPA_GET_BE16 (scalar_t__ const*) ; 
 size_t WPA_GET_BE24 (scalar_t__ const*) ; 
 scalar_t__ crypto_hash_finish (int /*<<< orphan*/ *,scalar_t__*,size_t*) ; 
 scalar_t__ crypto_public_key_decrypt_pkcs1 (int /*<<< orphan*/ *,scalar_t__ const*,int,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  os_free (scalar_t__*) ; 
 scalar_t__* os_malloc (int) ; 
 scalar_t__ os_memcmp (scalar_t__*,...) ; 
 int /*<<< orphan*/  os_memmove (scalar_t__*,scalar_t__*,size_t) ; 
 int tls_process_change_cipher_spec (struct tlsv1_server*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_process_certificate_verify(struct tlsv1_server *conn, u8 ct,
					  const u8 *in_data, size_t *in_len)
{
	const u8 *pos, *end;
	size_t left, len;
	u8 type;
	size_t hlen, buflen;
	u8 hash[MD5_MAC_LEN + SHA1_MAC_LEN], *hpos, *buf;
	enum { SIGN_ALG_RSA, SIGN_ALG_DSA } alg = SIGN_ALG_RSA;
	u16 slen;

	if (ct == TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC) {
		if (conn->verify_peer) {
			wpa_printf(MSG_DEBUG, "TLSv1: Client did not include "
				   "CertificateVerify");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_UNEXPECTED_MESSAGE);
			return -1;
		}

		return tls_process_change_cipher_spec(conn, ct, in_data,
						      in_len);
	}

	if (ct != TLS_CONTENT_TYPE_HANDSHAKE) {
		wpa_printf(MSG_DEBUG, "TLSv1: Expected Handshake; "
			   "received content type 0x%x", ct);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	pos = in_data;
	left = *in_len;

	if (left < 4) {
		wpa_printf(MSG_DEBUG, "TLSv1: Too short CertificateVerify "
			   "message (len=%lu)", (unsigned long) left);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	type = *pos++;
	len = WPA_GET_BE24(pos);
	pos += 3;
	left -= 4;

	if (len > left) {
		wpa_printf(MSG_DEBUG, "TLSv1: Unexpected CertificateVerify "
			   "message length (len=%lu != left=%lu)",
			   (unsigned long) len, (unsigned long) left);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	end = pos + len;

	if (type != TLS_HANDSHAKE_TYPE_CERTIFICATE_VERIFY) {
		wpa_printf(MSG_DEBUG, "TLSv1: Received unexpected handshake "
			   "message %d (expected CertificateVerify)", type);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "TLSv1: Received CertificateVerify");

	/*
	 * struct {
	 *   Signature signature;
	 * } CertificateVerify;
	 */

	hpos = hash;

#ifdef CONFIG_TLSV12
	if (conn->rl.tls_version == TLS_VERSION_1_2) {
		/*
		 * RFC 5246, 4.7:
		 * TLS v1.2 adds explicit indication of the used signature and
		 * hash algorithms.
		 *
		 * struct {
		 *   HashAlgorithm hash;
		 *   SignatureAlgorithm signature;
		 * } SignatureAndHashAlgorithm;
		 */
		if (end - pos < 2) {
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_DECODE_ERROR);
			return -1;
		}
		if (pos[0] != TLS_HASH_ALG_SHA256 ||
		    pos[1] != TLS_SIGN_ALG_RSA) {
			wpa_printf(MSG_DEBUG, "TLSv1.2: Unsupported hash(%u)/"
				   "signature(%u) algorithm",
				   pos[0], pos[1]);
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_INTERNAL_ERROR);
			return -1;
		}
		pos += 2;

		hlen = SHA256_MAC_LEN;
		if (conn->verify.sha256_cert == NULL ||
			crypto_hash_finish(conn->verify.sha256_cert, hpos, &hlen) <
			0) {
			conn->verify.sha256_cert = NULL;
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
								TLS_ALERT_INTERNAL_ERROR);
			return -1;
		}
		conn->verify.sha256_cert = NULL;
	} else {
#endif /* CONFIG_TLSV12 */

	if (alg == SIGN_ALG_RSA) {
		hlen = MD5_MAC_LEN;
		if (conn->verify.md5_cert == NULL ||
		    crypto_hash_finish(conn->verify.md5_cert, hpos, &hlen) < 0)
		{
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_INTERNAL_ERROR);
			conn->verify.md5_cert = NULL;
			crypto_hash_finish(conn->verify.sha1_cert, NULL, NULL);
			conn->verify.sha1_cert = NULL;
			return -1;
		}
		hpos += MD5_MAC_LEN;
	} else
		crypto_hash_finish(conn->verify.md5_cert, NULL, NULL);

	conn->verify.md5_cert = NULL;
	hlen = SHA1_MAC_LEN;
	if (conn->verify.sha1_cert == NULL ||
	    crypto_hash_finish(conn->verify.sha1_cert, hpos, &hlen) < 0) {
		conn->verify.sha1_cert = NULL;
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	conn->verify.sha1_cert = NULL;

	if (alg == SIGN_ALG_RSA)
		hlen += MD5_MAC_LEN;

#ifdef CONFIG_TLSV12
	}
#endif /* CONFIG_TLSV12 */

	wpa_hexdump(MSG_MSGDUMP, "TLSv1: CertificateVerify hash", hash, hlen);

	if (end - pos < 2) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}
	slen = WPA_GET_BE16(pos);
	pos += 2;
	if (end - pos < slen) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	wpa_hexdump(MSG_MSGDUMP, "TLSv1: Signature", pos, end - pos);
	if (conn->client_rsa_key == NULL) {
		wpa_printf(MSG_DEBUG, "TLSv1: No client public key to verify "
			   "signature");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	buflen = end - pos;
	buf = os_malloc(end - pos);
	if (crypto_public_key_decrypt_pkcs1(conn->client_rsa_key,
					    pos, end - pos, buf, &buflen) < 0)
	{
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to decrypt signature");
		os_free(buf);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECRYPT_ERROR);
		return -1;
	}

	wpa_hexdump_key(MSG_MSGDUMP, "TLSv1: Decrypted Signature",
			buf, buflen);

#ifdef CONFIG_TLSV12
	if (conn->rl.tls_version >= TLS_VERSION_1_2) {
		/*
		 * RFC 3447, A.2.4 RSASSA-PKCS1-v1_5
		 *
		 * DigestInfo ::= SEQUENCE {
		 *   digestAlgorithm DigestAlgorithm,
		 *   digest OCTET STRING
		 * }
		 *
		 * SHA-256 OID: sha256WithRSAEncryption ::= {pkcs-1 11}
		 *
		 * DER encoded DigestInfo for SHA256 per RFC 3447:
		 * 30 31 30 0d 06 09 60 86 48 01 65 03 04 02 01 05 00 04 20 ||
		 * H
		 */
		if (buflen >= 19 + 32 &&
		    os_memcmp(buf, "\x30\x31\x30\x0d\x06\x09\x60\x86\x48\x01"
			      "\x65\x03\x04\x02\x01\x05\x00\x04\x20", 19) == 0)
		{
			wpa_printf(MSG_DEBUG, "TLSv1.2: DigestAlgorithn = "
				   "SHA-256");
			os_memmove(buf, buf + 19, buflen - 19);
			buflen -= 19;
		} else {
			wpa_printf(MSG_DEBUG, "TLSv1.2: Unrecognized "
				   "DigestInfo");
			os_free(buf);
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_DECRYPT_ERROR);
			return -1;
		}
	}
#endif /* CONFIG_TLSV12 */

	if (buflen != hlen || os_memcmp(buf, hash, buflen) != 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Invalid Signature in "
			   "CertificateVerify - did not match with calculated "
			   "hash");
		os_free(buf);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECRYPT_ERROR);
		return -1;
	}

	os_free(buf);

	*in_len = end - in_data;

	conn->state = CHANGE_CIPHER_SPEC;

	return 0;
}