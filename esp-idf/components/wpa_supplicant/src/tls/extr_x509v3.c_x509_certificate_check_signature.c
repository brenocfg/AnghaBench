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
typedef  int /*<<< orphan*/  const u8 ;
struct TYPE_4__ {int len; int* oid; } ;
struct TYPE_3__ {TYPE_2__ oid; } ;
struct x509_certificate {size_t sign_value_len; TYPE_1__ signature; int /*<<< orphan*/  tbs_cert_len; int /*<<< orphan*/  tbs_cert_start; int /*<<< orphan*/  sign_value; int /*<<< orphan*/  public_key_len; int /*<<< orphan*/  public_key; } ;
struct crypto_public_key {int dummy; } ;
struct asn1_oid {int* oid; } ;
struct asn1_hdr {scalar_t__ tag; size_t length; int /*<<< orphan*/  const* payload; int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_OCTETSTRING ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,int,struct asn1_hdr*) ; 
 scalar_t__ asn1_get_oid (int /*<<< orphan*/  const*,size_t,struct asn1_oid*,int /*<<< orphan*/  const**) ; 
 scalar_t__ crypto_public_key_decrypt_pkcs1 (struct crypto_public_key*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*,size_t*) ; 
 int /*<<< orphan*/  crypto_public_key_free (struct crypto_public_key*) ; 
 struct crypto_public_key* crypto_public_key_import (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md5_vector (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* os_malloc (size_t) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  sha1_vector (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sha256_vector (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  x509_digest_oid (struct asn1_oid*) ; 
 int /*<<< orphan*/  x509_pkcs_oid (TYPE_2__*) ; 
 scalar_t__ x509_sha1_oid (struct asn1_oid*) ; 
 scalar_t__ x509_sha256_oid (struct asn1_oid*) ; 

int x509_certificate_check_signature(struct x509_certificate *issuer,
				     struct x509_certificate *cert)
{
	struct crypto_public_key *pk;
	u8 *data;
	const u8 *pos, *end, *next, *da_end;
	size_t data_len;
	struct asn1_hdr hdr;
	struct asn1_oid oid;
	u8 hash[32];
	size_t hash_len;

	if (!x509_pkcs_oid(&cert->signature.oid) ||
	    cert->signature.oid.len != 7 ||
	    cert->signature.oid.oid[5] != 1 /* pkcs-1 */) {
		wpa_printf(MSG_DEBUG, "X509: Unrecognized signature "
			   "algorithm");
		return -1;
	}

	pk = crypto_public_key_import(issuer->public_key,
				      issuer->public_key_len);
	if (pk == NULL)
		return -1;

	data_len = cert->sign_value_len;
	data = os_malloc(data_len);
	if (data == NULL) {
		crypto_public_key_free(pk);
		return -1;
	}

	if (crypto_public_key_decrypt_pkcs1(pk, cert->sign_value,
					    cert->sign_value_len, data,
					    &data_len) < 0) {
		wpa_printf(MSG_DEBUG, "X509: Failed to decrypt signature");
		crypto_public_key_free(pk);
		os_free(data);
		return -1;
	}
	crypto_public_key_free(pk);

	wpa_hexdump(MSG_MSGDUMP, "X509: Signature data D", data, data_len);

	/*
	 * PKCS #1 v1.5, 10.1.2:
	 *
	 * DigestInfo ::= SEQUENCE {
	 *     digestAlgorithm DigestAlgorithmIdentifier,
	 *     digest Digest
	 * }
	 *
	 * DigestAlgorithmIdentifier ::= AlgorithmIdentifier
	 *
	 * Digest ::= OCTET STRING
	 *
	 */
	if (asn1_get_next(data, data_len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "X509: Expected SEQUENCE "
			   "(DigestInfo) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		os_free(data);
		return -1;
	}

	pos = hdr.payload;
	end = pos + hdr.length;

	/*
	 * X.509:
	 * AlgorithmIdentifier ::= SEQUENCE {
	 *     algorithm            OBJECT IDENTIFIER,
	 *     parameters           ANY DEFINED BY algorithm OPTIONAL
	 * }
	 */

	if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "X509: Expected SEQUENCE "
			   "(AlgorithmIdentifier) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		os_free(data);
		return -1;
	}
	da_end = hdr.payload + hdr.length;

	if (asn1_get_oid(hdr.payload, hdr.length, &oid, &next)) {
		wpa_printf(MSG_DEBUG, "X509: Failed to parse digestAlgorithm");
		os_free(data);
		return -1;
	}

	if (x509_sha1_oid(&oid)) {
		if (cert->signature.oid.oid[6] !=
		    5 /* sha-1WithRSAEncryption */) {
			wpa_printf(MSG_DEBUG, "X509: digestAlgorithm SHA1 "
				   "does not match with certificate "
				   "signatureAlgorithm (%lu)",
				   cert->signature.oid.oid[6]);
			os_free(data);
			return -1;
		}
		goto skip_digest_oid;
	}

	if (x509_sha256_oid(&oid)) {
		if (cert->signature.oid.oid[6] !=
		    11 /* sha2561WithRSAEncryption */) {
			wpa_printf(MSG_DEBUG, "X509: digestAlgorithm SHA256 "
				   "does not match with certificate "
				   "signatureAlgorithm (%lu)",
				   cert->signature.oid.oid[6]);
			os_free(data);
			return -1;
		}
		goto skip_digest_oid;
	}

	if (!x509_digest_oid(&oid)) {
		wpa_printf(MSG_DEBUG, "X509: Unrecognized digestAlgorithm");
		os_free(data);
		return -1;
	}
	switch (oid.oid[5]) {
	case 5: /* md5 */
		if (cert->signature.oid.oid[6] != 4 /* md5WithRSAEncryption */)
		{
			wpa_printf(MSG_DEBUG, "X509: digestAlgorithm MD5 does "
				   "not match with certificate "
				   "signatureAlgorithm (%lu)",
				   cert->signature.oid.oid[6]);
			os_free(data);
			return -1;
		}
		break;
	case 2: /* md2 */
	case 4: /* md4 */
	default:
		wpa_printf(MSG_DEBUG, "X509: Unsupported digestAlgorithm "
			   "(%lu)", oid.oid[5]);
		os_free(data);
		return -1;
	}

skip_digest_oid:
	/* Digest ::= OCTET STRING */
	pos = da_end;
	end = data + data_len;

	if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_OCTETSTRING) {
		wpa_printf(MSG_DEBUG, "X509: Expected OCTETSTRING "
			   "(Digest) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		os_free(data);
		return -1;
	}
	wpa_hexdump(MSG_MSGDUMP, "X509: Decrypted Digest",
		    hdr.payload, hdr.length);

	switch (cert->signature.oid.oid[6]) {
	case 4: /* md5WithRSAEncryption */
		md5_vector(1, &cert->tbs_cert_start, &cert->tbs_cert_len,
			   hash);
		hash_len = 16;
		wpa_hexdump(MSG_MSGDUMP, "X509: Certificate hash (MD5)",
			    hash, hash_len);
		break;
	case 5: /* sha-1WithRSAEncryption */
		sha1_vector(1, &cert->tbs_cert_start, &cert->tbs_cert_len,
			    hash);
		hash_len = 20;
		wpa_hexdump(MSG_MSGDUMP, "X509: Certificate hash (SHA1)",
			    hash, hash_len);
		break;
	case 11: /* sha256WithRSAEncryption */
		sha256_vector(1, &cert->tbs_cert_start, &cert->tbs_cert_len,
				                    hash);
		hash_len = 32;
		wpa_hexdump(MSG_MSGDUMP, "X509: Certificate hash (SHA256)",
			    hash, hash_len);
		break;
	case 2: /* md2WithRSAEncryption */
	case 12: /* sha384WithRSAEncryption */
	case 13: /* sha512WithRSAEncryption */
	default:
		wpa_printf(MSG_INFO, "X509: Unsupported certificate signature "
			   "algorithm (%lu)", cert->signature.oid.oid[6]);
		os_free(data);
		return -1;
	}

	if (hdr.length != hash_len ||
	    os_memcmp(hdr.payload, hash, hdr.length) != 0) {
		wpa_printf(MSG_INFO, "X509: Certificate Digest does not match "
			   "with calculated tbsCertificate hash");
		os_free(data);
		return -1;
	}

	os_free(data);

	wpa_printf(MSG_DEBUG, "X509: Certificate Digest matches with "
		   "calculated tbsCertificate hash");

	return 0;
}