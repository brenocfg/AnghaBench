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
struct x509_certificate {scalar_t__ not_after; scalar_t__ not_before; } ;
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; size_t length; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,size_t,struct asn1_hdr*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 scalar_t__ x509_parse_time (int /*<<< orphan*/ *,size_t,unsigned long,scalar_t__*) ; 

__attribute__((used)) static int x509_parse_validity(const u8 *buf, size_t len,
			       struct x509_certificate *cert, const u8 **next)
{
	struct asn1_hdr hdr;
	const u8 *pos;
	size_t plen;

	/*
	 * Validity ::= SEQUENCE {
	 *     notBefore      Time,
	 *     notAfter       Time
	 * }
	 *
	 * RFC 3280, 4.1.2.5:
	 * CAs conforming to this profile MUST always encode certificate
	 * validity dates through the year 2049 as UTCTime; certificate
	 * validity dates in 2050 or later MUST be encoded as GeneralizedTime.
	 */

	if (asn1_get_next(buf, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "X509: Expected SEQUENCE "
			   "(Validity) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		return -1;
	}
	pos = hdr.payload;
	plen = hdr.length;

	if (pos + plen > buf + len)
		return -1;

	*next = pos + plen;

	if (asn1_get_next(pos, plen, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    x509_parse_time(hdr.payload, hdr.length, hdr.tag,
			    &cert->not_before) < 0) {
		wpa_hexdump_ascii(MSG_DEBUG, "X509: Failed to parse notBefore "
				  "Time", hdr.payload, hdr.length);
		return -1;
	}

	pos = hdr.payload + hdr.length;
	plen = *next - pos;

	if (asn1_get_next(pos, plen, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    x509_parse_time(hdr.payload, hdr.length, hdr.tag,
			    &cert->not_after) < 0) {
		wpa_hexdump_ascii(MSG_DEBUG, "X509: Failed to parse notAfter "
				  "Time", hdr.payload, hdr.length);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "X509: Validity: notBefore: %lu notAfter: %lu",
		   (unsigned long) cert->not_before,
		   (unsigned long) cert->not_after);

	return 0;
}