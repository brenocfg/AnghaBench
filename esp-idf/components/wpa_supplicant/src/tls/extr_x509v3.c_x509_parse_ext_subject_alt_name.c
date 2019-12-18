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
struct x509_certificate {int /*<<< orphan*/  subject; int /*<<< orphan*/  extensions_present; } ;
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; scalar_t__ length; int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  X509_EXT_SUBJECT_ALT_NAME ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,size_t,struct asn1_hdr*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int x509_parse_ext_alt_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int x509_parse_ext_subject_alt_name(struct x509_certificate *cert,
					   const u8 *pos, size_t len)
{
	struct asn1_hdr hdr;

	/* SubjectAltName ::= GeneralNames */

	if (asn1_get_next(pos, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "X509: Expected SEQUENCE in "
			   "SubjectAltName; found %d tag 0x%x",
			   hdr.class, hdr.tag);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "X509: SubjectAltName");
	cert->extensions_present |= X509_EXT_SUBJECT_ALT_NAME;

	if (hdr.length == 0)
		return 0;

	return x509_parse_ext_alt_name(&cert->subject, hdr.payload,
				       hdr.length);
}