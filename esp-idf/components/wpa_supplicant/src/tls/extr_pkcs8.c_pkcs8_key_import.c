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
struct crypto_private_key {int dummy; } ;
struct bignum {int dummy; } ;
struct asn1_oid {int len; int* oid; } ;
struct asn1_hdr {scalar_t__ tag; int length; int /*<<< orphan*/ * payload; int /*<<< orphan*/  class; } ;
typedef  int /*<<< orphan*/  obuf ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_INTEGER ; 
 scalar_t__ ASN1_TAG_OCTETSTRING ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,int,struct asn1_hdr*) ; 
 scalar_t__ asn1_get_oid (int /*<<< orphan*/ *,int,struct asn1_oid*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  asn1_oid_to_str (struct asn1_oid*,char*,int) ; 
 scalar_t__ bignum_cmp_d (struct bignum*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bignum_deinit (struct bignum*) ; 
 struct bignum* bignum_init () ; 
 scalar_t__ bignum_set_unsigned_bin (struct bignum*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ crypto_rsa_import_private_key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

struct crypto_private_key * pkcs8_key_import(const u8 *buf, size_t len)
{
	struct asn1_hdr hdr;
	const u8 *pos, *end;
	struct bignum *zero;
	struct asn1_oid oid;
	char obuf[80];

	/* PKCS #8, Chapter 6 */

	/* PrivateKeyInfo ::= SEQUENCE */
	if (asn1_get_next(buf, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Does not start with PKCS #8 "
			   "header (SEQUENCE); assume PKCS #8 not used");
		return NULL;
	}
	pos = hdr.payload;
	end = pos + hdr.length;

	/* version Version (Version ::= INTEGER) */
	if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL || hdr.tag != ASN1_TAG_INTEGER) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Expected INTEGER - found "
			   "class %d tag 0x%x; assume PKCS #8 not used",
			   hdr.class, hdr.tag);
		return NULL;
	}

	zero = bignum_init();
	if (zero == NULL)
		return NULL;

	if (bignum_set_unsigned_bin(zero, hdr.payload, hdr.length) < 0) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Failed to parse INTEGER");
		bignum_deinit(zero);
		return NULL;
	}
	pos = hdr.payload + hdr.length;

	if (bignum_cmp_d(zero, 0) != 0) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Expected zero INTEGER in the "
			   "beginning of private key; not found; assume "
			   "PKCS #8 not used");
		bignum_deinit(zero);
		return NULL;
	}
	bignum_deinit(zero);

	/* privateKeyAlgorithm PrivateKeyAlgorithmIdentifier
	 * (PrivateKeyAlgorithmIdentifier ::= AlgorithmIdentifier) */
	if (asn1_get_next(pos, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Expected SEQUENCE "
			   "(AlgorithmIdentifier) - found class %d tag 0x%x; "
			   "assume PKCS #8 not used",
			   hdr.class, hdr.tag);
		return NULL;
	}

	if (asn1_get_oid(hdr.payload, hdr.length, &oid, &pos)) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Failed to parse OID "
			   "(algorithm); assume PKCS #8 not used");
		return NULL;
	}

	asn1_oid_to_str(&oid, obuf, sizeof(obuf));
	wpa_printf(MSG_DEBUG, "PKCS #8: algorithm=%s", obuf);

	if (oid.len != 7 ||
	    oid.oid[0] != 1 /* iso */ ||
	    oid.oid[1] != 2 /* member-body */ ||
	    oid.oid[2] != 840 /* us */ ||
	    oid.oid[3] != 113549 /* rsadsi */ ||
	    oid.oid[4] != 1 /* pkcs */ ||
	    oid.oid[5] != 1 /* pkcs-1 */ ||
	    oid.oid[6] != 1 /* rsaEncryption */) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Unsupported private key "
			   "algorithm %s", obuf);
		return NULL;
	}

	pos = hdr.payload + hdr.length;

	/* privateKey PrivateKey (PrivateKey ::= OCTET STRING) */
	if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_OCTETSTRING) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Expected OCTETSTRING "
			   "(privateKey) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		return NULL;
	}
	wpa_printf(MSG_DEBUG, "PKCS #8: Try to parse RSAPrivateKey");

	return (struct crypto_private_key *)
		crypto_rsa_import_private_key(hdr.payload, hdr.length);
}