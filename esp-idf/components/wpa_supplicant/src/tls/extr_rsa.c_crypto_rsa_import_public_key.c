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
struct crypto_rsa_key {int /*<<< orphan*/ * e; int /*<<< orphan*/ * n; } ;
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; int length; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,size_t,struct asn1_hdr*) ; 
 void* bignum_init () ; 
 int /*<<< orphan*/  crypto_rsa_free (struct crypto_rsa_key*) ; 
 int /*<<< orphan*/ * crypto_rsa_parse_integer (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

struct crypto_rsa_key *
crypto_rsa_import_public_key(const u8 *buf, size_t len)
{
	struct crypto_rsa_key *key;
	struct asn1_hdr hdr;
	const u8 *pos, *end;

	key = (struct crypto_rsa_key *)os_zalloc(sizeof(*key));
	if (key == NULL)
		return NULL;

	key->n = bignum_init();
	key->e = bignum_init();
	if (key->n == NULL || key->e == NULL) {
		crypto_rsa_free(key);
		return NULL;
	}

	/*
	 * PKCS #1, 7.1:
	 * RSAPublicKey ::= SEQUENCE {
	 *     modulus INTEGER, -- n
	 *     publicExponent INTEGER -- e
	 * }
	 */

	if (asn1_get_next(buf, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "RSA: Expected SEQUENCE "
			   "(public key) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		goto error;
	}
	pos = hdr.payload;
	end = pos + hdr.length;

	pos = crypto_rsa_parse_integer(pos, end, key->n);
	pos = crypto_rsa_parse_integer(pos, end, key->e);

	if (pos == NULL)
		goto error;

	if (pos != end) {
		wpa_hexdump(MSG_DEBUG,
			    "RSA: Extra data in public key SEQUENCE",
			    pos, end - pos);
		goto error;
	}

	return key;

error:
	crypto_rsa_free(key);
	return NULL;
}