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
typedef  int /*<<< orphan*/  br_rsa_public_key ;
typedef  int /*<<< orphan*/  br_rsa_private_key ;

/* Variables and functions */
 size_t br_asn1_encode_length (unsigned char*,size_t) ; 
 size_t br_encode_rsa_raw_der (unsigned char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void const*,size_t) ; 
 int len_of_len (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

size_t
br_encode_rsa_pkcs8_der(void *dest, const br_rsa_private_key *sk,
	const br_rsa_public_key *pk, const void *d, size_t dlen)
{
	/*
	 * ASN.1 format:
	 *
	 *   OneAsymmetricKey ::= SEQUENCE {
	 *     version                   Version,
	 *     privateKeyAlgorithm       PrivateKeyAlgorithmIdentifier,
	 *     privateKey                PrivateKey,
	 *     attributes            [0] Attributes OPTIONAL,
	 *     ...,
	 *     [[2: publicKey        [1] PublicKey OPTIONAL ]],
	 *     ...
	 *   }
	 *
	 * We don't include attributes or public key. The 'version' field
	 * is an INTEGER that we will set to 0 (meaning 'v1', compatible
	 * with previous versions of PKCS#8). The 'privateKeyAlgorithm'
	 * structure is an AlgorithmIdentifier whose OID should be
	 * rsaEncryption, with NULL parameters. The 'privateKey' is an
	 * OCTET STRING, whose value is the "raw DER" encoding of the
	 * key pair.
	 *
	 * Since the private key value comes last, this function really
	 * adds a header, which is mostly fixed (only some lengths have
	 * to be modified.
	 */

	/*
	 * Concatenation of:
	 *  - DER encoding of an INTEGER of value 0 (the 'version' field)
	 *  - DER encoding of a PrivateKeyAlgorithmIdentifier that uses
	 *    the rsaEncryption OID, and NULL parameters
	 *  - An OCTET STRING tag
	 */
	static const unsigned char PK8_HEAD[] = {
		0x02, 0x01, 0x00,
		0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
		0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00,
		0x04
	};

	size_t len_raw, len_seq;

	len_raw = br_encode_rsa_raw_der(NULL, sk, pk, d, dlen);
	len_seq = (sizeof PK8_HEAD) + len_of_len(len_raw) + len_raw;
	if (dest == NULL) {
		return 1 + len_of_len(len_seq) + len_seq;
	} else {
		unsigned char *buf;
		size_t lenlen;

		buf = dest;
		*buf ++ = 0x30;  /* SEQUENCE tag */
		lenlen = br_asn1_encode_length(buf, len_seq);
		buf += lenlen;

		/* version, privateKeyAlgorithm, privateKey tag */
		memcpy(buf, PK8_HEAD, sizeof PK8_HEAD);
		buf += sizeof PK8_HEAD;

		/* privateKey */
		buf += br_asn1_encode_length(buf, len_raw);
		br_encode_rsa_raw_der(buf, sk, pk, d, dlen);

		return 1 + lenlen + len_seq;
	}
}