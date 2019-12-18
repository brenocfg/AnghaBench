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
typedef  int u8 ;
struct tlsv1_record_layer {scalar_t__ read_cipher_suite; size_t iv_size; scalar_t__ tls_version; size_t hash_size; int* read_seq_num; int /*<<< orphan*/  read_mac_secret; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/  read_cbc; } ;
struct crypto_hash {int dummy; } ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int TLS_ALERT_BAD_RECORD_MAC ; 
 int TLS_ALERT_DECRYPTION_FAILED ; 
 int TLS_ALERT_INTERNAL_ERROR ; 
 int TLS_ALERT_PROTOCOL_VERSION ; 
 int TLS_ALERT_RECORD_OVERFLOW ; 
 int TLS_ALERT_UNEXPECTED_MESSAGE ; 
 int TLS_CONTENT_TYPE_ALERT ; 
 int TLS_CONTENT_TYPE_APPLICATION_DATA ; 
 int TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC ; 
 int TLS_CONTENT_TYPE_HANDSHAKE ; 
 scalar_t__ TLS_NULL_WITH_NULL_NULL ; 
 size_t TLS_RECORD_HEADER_LEN ; 
 size_t TLS_SEQ_NUM_LEN ; 
 scalar_t__ TLS_VERSION_1_1 ; 
 size_t WPA_GET_BE16 (int const*) ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int*,size_t) ; 
 scalar_t__ crypto_cipher_decrypt (int /*<<< orphan*/ ,int const*,int*,size_t) ; 
 scalar_t__ crypto_hash_finish (struct crypto_hash*,int*,size_t*) ; 
 struct crypto_hash* crypto_hash_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  crypto_hash_update (struct crypto_hash*,int const*,size_t) ; 
 int /*<<< orphan*/  inc_byte_array (int*,size_t) ; 
 scalar_t__ os_memcmp (int*,int*,size_t) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,size_t) ; 
 int /*<<< orphan*/  os_memmove (int*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int tlsv1_record_receive(struct tlsv1_record_layer *rl,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t *out_len, u8 *alert)
{
	size_t i, rlen, hlen;
	u8 padlen;
	struct crypto_hash *hmac = NULL;
	u8 len[2], hash[100];
	int force_mac_error = 0;
	u8 ct;

	if (in_len < TLS_RECORD_HEADER_LEN) {
		wpa_printf(MSG_DEBUG, "TLSv1: Too short record (in_len=%lu) - "
			   "need more data",
			   (unsigned long) in_len);
		wpa_hexdump(MSG_MSGDUMP, "TLSv1: Record Layer - Received",
			    in_data, in_len);
		return 0;
	}

	ct = in_data[0];
	rlen = WPA_GET_BE16(in_data + 3);
	wpa_printf(MSG_DEBUG, "TLSv1: Received content type %d version %d.%d "
		   "length %d", ct, in_data[1], in_data[2], (int) rlen);

	/*
	 * TLS v1.0 and v1.1 RFCs were not exactly clear on the use of the
	 * protocol version in record layer. As such, accept any {03,xx} value
	 * to remain compatible with existing implementations.
	 */
	if (in_data[1] != 0x03) {
		wpa_printf(MSG_DEBUG, "TLSv1: Unexpected protocol version "
			   "%u.%u", in_data[1], in_data[2]);
		*alert = TLS_ALERT_PROTOCOL_VERSION;
		return -1;
	}

	/* TLSCiphertext must not be more than 2^14+2048 bytes */
	if (TLS_RECORD_HEADER_LEN + rlen > 18432) {
		wpa_printf(MSG_DEBUG, "TLSv1: Record overflow (len=%lu)",
			   (unsigned long) (TLS_RECORD_HEADER_LEN + rlen));
		*alert = TLS_ALERT_RECORD_OVERFLOW;
		return -1;
	}

	in_data += TLS_RECORD_HEADER_LEN;
	in_len -= TLS_RECORD_HEADER_LEN;

	if (rlen > in_len) {
		wpa_printf(MSG_DEBUG, "TLSv1: Not all record data included "
			   "(rlen=%lu > in_len=%lu)",
			   (unsigned long) rlen, (unsigned long) in_len);
		return 0;
	}

	wpa_hexdump(MSG_MSGDUMP, "TLSv1: Record Layer - Received",
		    in_data, rlen);

	if (ct != TLS_CONTENT_TYPE_HANDSHAKE &&
	    ct != TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC &&
	    ct != TLS_CONTENT_TYPE_ALERT &&
	    ct != TLS_CONTENT_TYPE_APPLICATION_DATA) {
		wpa_printf(MSG_DEBUG, "TLSv1: Ignore record with unknown "
			   "content type 0x%x", ct);
		*alert = TLS_ALERT_UNEXPECTED_MESSAGE;
		return -1;
	}

	in_len = rlen;

	if (*out_len < in_len) {
		wpa_printf(MSG_DEBUG, "TLSv1: Not enough output buffer for "
			   "processing received record");
		*alert = TLS_ALERT_INTERNAL_ERROR;
		return -1;
	}

	if (rl->read_cipher_suite != TLS_NULL_WITH_NULL_NULL) {
		size_t plen;
		if ((int)crypto_cipher_decrypt(rl->read_cbc, in_data,
					                        out_data, in_len) < 0) {
			*alert = TLS_ALERT_DECRYPTION_FAILED;
			return -1;
		}
		
		plen = in_len;
		wpa_hexdump_key(MSG_MSGDUMP, "TLSv1: Record Layer - Decrypted "
				"data", out_data, plen);

		if (rl->iv_size) {
			/*
			 * TLS v1.0 defines different alert values for various
			 * failures. That may information to aid in attacks, so
			 * use the same bad_record_mac alert regardless of the
			 * issues.
			 *
			 * In addition, instead of returning immediately on
			 * error, run through the MAC check to make timing
			 * attacks more difficult.
			 */

			if (rl->tls_version >= TLS_VERSION_1_1) {
				/* Remove opaque IV[Cipherspec.block_length] */
				if (plen < rl->iv_size) {
					wpa_printf(MSG_DEBUG, "TLSv1.1: Not "
						   "enough room for IV");
					force_mac_error = 1;
					goto check_mac;
				}
				os_memmove(out_data, out_data + rl->iv_size,
					   plen - rl->iv_size);
				plen -= rl->iv_size;
			}

			/* Verify and remove padding */
			if (plen == 0) {
				wpa_printf(MSG_DEBUG, "TLSv1: Too short record"
					   " (no pad)");
				force_mac_error = 1;
				goto check_mac;
			}
			padlen = out_data[plen - 1];
			if (padlen >= plen) {
				wpa_printf(MSG_DEBUG, "TLSv1: Incorrect pad "
					   "length (%u, plen=%lu) in "
					   "received record",
					   padlen, (unsigned long) plen);
				force_mac_error = 1;
				goto check_mac;
			}
			for (i = plen - padlen - 1; i < plen - 1; i++) {
				if (out_data[i] != padlen) {
					wpa_hexdump(MSG_DEBUG,
						    "TLSv1: Invalid pad in "
						    "received record",
						    out_data + plen - padlen -
						    1, padlen + 1);
					force_mac_error = 1;
					goto check_mac;
				}
			}

			plen -= padlen + 1;

			wpa_hexdump_key(MSG_MSGDUMP, "TLSv1: Record Layer - "
					"Decrypted data with IV and padding "
					"removed", out_data, plen);
		}

	check_mac:
		if (plen < rl->hash_size) {
			wpa_printf(MSG_DEBUG, "TLSv1: Too short record; no "
				   "hash value");
			*alert = TLS_ALERT_BAD_RECORD_MAC;
			return -1;
		}

		plen -= rl->hash_size;

		hmac = crypto_hash_init(rl->hash_alg, rl->read_mac_secret, rl->hash_size);

		if (hmac == NULL) {
			wpa_printf(MSG_DEBUG, "TLSv1: Record Layer - Failed "
				   "to initialize HMAC");
			*alert = TLS_ALERT_INTERNAL_ERROR;
			return -1;
		}

		crypto_hash_update(hmac, rl->read_seq_num, TLS_SEQ_NUM_LEN);
		/* type + version + length + fragment */
		crypto_hash_update(hmac, in_data - TLS_RECORD_HEADER_LEN, 3);
		WPA_PUT_BE16(len, plen);
		crypto_hash_update(hmac, len, 2);
		crypto_hash_update(hmac, out_data, plen);
		
		hlen = sizeof(hash);
		if ((int)crypto_hash_finish(hmac, hash, &hlen) < 0) {
			wpa_printf(MSG_DEBUG, "TLSv1: Record Layer - Failed to calculate HMAC");
			*alert = TLS_ALERT_INTERNAL_ERROR;
			return -1;
		}
		
		if (hlen != rl->hash_size ||
		    os_memcmp(hash, out_data + plen, hlen) != 0 ||
		    force_mac_error) {
			wpa_printf(MSG_DEBUG, "TLSv1: Invalid HMAC value in "
				   "received message (force_mac_error=%d)",
				   force_mac_error);
			*alert = TLS_ALERT_BAD_RECORD_MAC;
			return -1;
		}

		*out_len = plen;
	} else {
		os_memcpy(out_data, in_data, in_len);
		*out_len = in_len;
	}

	/* TLSCompressed must not be more than 2^14+1024 bytes */
	if (TLS_RECORD_HEADER_LEN + *out_len > 17408) {
		wpa_printf(MSG_DEBUG, "TLSv1: Record overflow (len=%lu)",
			   (unsigned long) (TLS_RECORD_HEADER_LEN + *out_len));
		*alert = TLS_ALERT_RECORD_OVERFLOW;
		return -1;
	}

	inc_byte_array(rl->read_seq_num, TLS_SEQ_NUM_LEN);

	return TLS_RECORD_HEADER_LEN + rlen;
}