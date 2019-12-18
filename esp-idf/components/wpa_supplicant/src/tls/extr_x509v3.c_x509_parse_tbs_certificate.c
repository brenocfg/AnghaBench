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
typedef  int /*<<< orphan*/  const u8 ;
struct x509_certificate {unsigned long version; int serial_number; int /*<<< orphan*/  subject; int /*<<< orphan*/  issuer; int /*<<< orphan*/  signature; } ;
struct asn1_hdr {int tag; int length; int /*<<< orphan*/  const* payload; int /*<<< orphan*/  class; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_CLASS_CONTEXT_SPECIFIC ; 
 int /*<<< orphan*/  ASN1_CLASS_UNIVERSAL ; 
 int ASN1_TAG_INTEGER ; 
 int ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 unsigned long X509_CERT_V1 ; 
 unsigned long X509_CERT_V2 ; 
 unsigned long X509_CERT_V3 ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,int,struct asn1_hdr*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  x509_name_string (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ x509_parse_algorithm_identifier (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 scalar_t__ x509_parse_extensions (struct x509_certificate*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ x509_parse_name (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 scalar_t__ x509_parse_public_key (int /*<<< orphan*/  const*,int,struct x509_certificate*,int /*<<< orphan*/  const**) ; 
 scalar_t__ x509_parse_validity (int /*<<< orphan*/  const*,int,struct x509_certificate*,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int x509_parse_tbs_certificate(const u8 *buf, size_t len,
				      struct x509_certificate *cert,
				      const u8 **next)
{
	struct asn1_hdr hdr;
	const u8 *pos, *end;
	size_t left;
	char sbuf[128];
	unsigned long value;

	/* tbsCertificate TBSCertificate ::= SEQUENCE */
	if (asn1_get_next(buf, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "X509: tbsCertificate did not start "
			   "with a valid SEQUENCE - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		return -1;
	}
	pos = hdr.payload;
	end = *next = pos + hdr.length;

	/*
	 * version [0]  EXPLICIT Version DEFAULT v1
	 * Version  ::=  INTEGER  {  v1(0), v2(1), v3(2)  }
	 */
	if (asn1_get_next(pos, end - pos, &hdr) < 0)
		return -1;
	pos = hdr.payload;

	if (hdr.class == ASN1_CLASS_CONTEXT_SPECIFIC) {
		if (asn1_get_next(pos, end - pos, &hdr) < 0)
			return -1;

		if (hdr.class != ASN1_CLASS_UNIVERSAL ||
		    hdr.tag != ASN1_TAG_INTEGER) {
			wpa_printf(MSG_DEBUG, "X509: No INTEGER tag found for "
				   "version field - found class %d tag 0x%x",
				   hdr.class, hdr.tag);
			return -1;
		}
		if (hdr.length != 1) {
			wpa_printf(MSG_DEBUG, "X509: Unexpected version field "
				   "length %u (expected 1)", hdr.length);
			return -1;
		}
		pos = hdr.payload;
		left = hdr.length;
		value = 0;
		while (left) {
			value <<= 8;
			value |= *pos++;
			left--;
		}

		cert->version = value;
		if (cert->version != X509_CERT_V1 &&
		    cert->version != X509_CERT_V2 &&
		    cert->version != X509_CERT_V3) {
			wpa_printf(MSG_DEBUG, "X509: Unsupported version %d",
				   cert->version + 1);
			return -1;
		}

		if (asn1_get_next(pos, end - pos, &hdr) < 0)
			return -1;
	} else
		cert->version = X509_CERT_V1;
	wpa_printf(MSG_DEBUG, "X509: Version X.509v%d", cert->version + 1);

	/* serialNumber CertificateSerialNumber ::= INTEGER */
	if (hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_INTEGER) {
		wpa_printf(MSG_DEBUG, "X509: No INTEGER tag found for "
			   "serialNumber; class=%d tag=0x%x",
			   hdr.class, hdr.tag);
		return -1;
	}

	pos = hdr.payload;
	left = hdr.length;
	while (left) {
		cert->serial_number <<= 8;
		cert->serial_number |= *pos++;
		left--;
	}
	wpa_printf(MSG_DEBUG, "X509: serialNumber %lu", cert->serial_number);

	/* signature AlgorithmIdentifier */
	if (x509_parse_algorithm_identifier(pos, end - pos, &cert->signature,
					    &pos))
		return -1;

	/* issuer Name */
	if (x509_parse_name(pos, end - pos, &cert->issuer, &pos))
		return -1;
	x509_name_string(&cert->issuer, sbuf, sizeof(sbuf));
	wpa_printf(MSG_DEBUG, "X509: issuer %s", sbuf);

	/* validity Validity */
	if (x509_parse_validity(pos, end - pos, cert, &pos))
		return -1;

	/* subject Name */
	if (x509_parse_name(pos, end - pos, &cert->subject, &pos))
		return -1;
	x509_name_string(&cert->subject, sbuf, sizeof(sbuf));
	wpa_printf(MSG_DEBUG, "X509: subject %s", sbuf);

	/* subjectPublicKeyInfo SubjectPublicKeyInfo */
	if (x509_parse_public_key(pos, end - pos, cert, &pos))
		return -1;

	if (pos == end)
		return 0;

	if (cert->version == X509_CERT_V1)
		return 0;

	if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_CONTEXT_SPECIFIC) {
		wpa_printf(MSG_DEBUG, "X509: Expected Context-Specific"
			   " tag to parse optional tbsCertificate "
			   "field(s); parsed class %d tag 0x%x",
			   hdr.class, hdr.tag);
		return -1;
	}

	if (hdr.tag == 1) {
		/* issuerUniqueID  [1]  IMPLICIT UniqueIdentifier OPTIONAL */
		wpa_printf(MSG_DEBUG, "X509: issuerUniqueID");
		/* TODO: parse UniqueIdentifier ::= BIT STRING */

		if (hdr.payload + hdr.length == end)
			return 0;

		if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
		    hdr.class != ASN1_CLASS_CONTEXT_SPECIFIC) {
			wpa_printf(MSG_DEBUG, "X509: Expected Context-Specific"
				   " tag to parse optional tbsCertificate "
				   "field(s); parsed class %d tag 0x%x",
				   hdr.class, hdr.tag);
			return -1;
		}
	}

	if (hdr.tag == 2) {
		/* subjectUniqueID [2]  IMPLICIT UniqueIdentifier OPTIONAL */
		wpa_printf(MSG_DEBUG, "X509: subjectUniqueID");
		/* TODO: parse UniqueIdentifier ::= BIT STRING */

		if (hdr.payload + hdr.length == end)
			return 0;

		if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
		    hdr.class != ASN1_CLASS_CONTEXT_SPECIFIC) {
			wpa_printf(MSG_DEBUG, "X509: Expected Context-Specific"
				   " tag to parse optional tbsCertificate "
				   "field(s); parsed class %d tag 0x%x",
				   hdr.class, hdr.tag);
			return -1;
		}
	}

	if (hdr.tag != 3) {
		wpa_printf(MSG_DEBUG, "X509: Ignored unexpected "
			   "Context-Specific tag %d in optional "
			   "tbsCertificate fields", hdr.tag);
		return 0;
	}

	/* extensions      [3]  EXPLICIT Extensions OPTIONAL */

	if (cert->version != X509_CERT_V3) {
		wpa_printf(MSG_DEBUG, "X509: X.509%d certificate and "
			   "Extensions data which are only allowed for "
			   "version 3", cert->version + 1);
		return -1;
	}

	if (x509_parse_extensions(cert, hdr.payload, hdr.length) < 0)
		return -1;

	pos = hdr.payload + hdr.length;
	if (pos < end) {
		wpa_hexdump(MSG_DEBUG,
			    "X509: Ignored extra tbsCertificate data",
			    pos, end - pos);
	}

	return 0;
}