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
struct asn1_ctx {scalar_t__ error; int /*<<< orphan*/  pointer; } ;
struct TCP_Server_Info {int sec_mskerberos; int sec_kerberosu2u; int sec_kerberos; int sec_ntlmssp; } ;

/* Variables and functions */
 unsigned int ASN1_APL ; 
 unsigned int ASN1_CON ; 
 unsigned int ASN1_CTX ; 
 unsigned int ASN1_EOC ; 
 scalar_t__ ASN1_ERR_DEC_EMPTY ; 
 unsigned int ASN1_GENSTR ; 
 unsigned int ASN1_OJI ; 
 unsigned int ASN1_PRI ; 
 unsigned int ASN1_SEQ ; 
 unsigned int ASN1_UNI ; 
 int /*<<< orphan*/  KRB5U2U_OID ; 
 int /*<<< orphan*/  KRB5U2U_OID_LEN ; 
 int /*<<< orphan*/  KRB5_OID ; 
 int /*<<< orphan*/  KRB5_OID_LEN ; 
 int /*<<< orphan*/  MSKRB5_OID ; 
 int /*<<< orphan*/  MSKRB5_OID_LEN ; 
 int /*<<< orphan*/  NTLMSSP_OID ; 
 int /*<<< orphan*/  NTLMSSP_OID_LEN ; 
 int /*<<< orphan*/  SPNEGO_OID ; 
 int /*<<< orphan*/  SPNEGO_OID_LEN ; 
 int /*<<< orphan*/  asn1_eoc_decode (struct asn1_ctx*,unsigned char*) ; 
 unsigned int asn1_header_decode (struct asn1_ctx*,unsigned char**,unsigned int*,unsigned int*,unsigned int*) ; 
 int asn1_oid_decode (struct asn1_ctx*,unsigned char*,unsigned long**,unsigned int*) ; 
 int /*<<< orphan*/  asn1_open (struct asn1_ctx*,unsigned char*,int) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int compare_oid (unsigned long*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 

int
decode_negTokenInit(unsigned char *security_blob, int length,
		    struct TCP_Server_Info *server)
{
	struct asn1_ctx ctx;
	unsigned char *end;
	unsigned char *sequence_end;
	unsigned long *oid = NULL;
	unsigned int cls, con, tag, oidlen, rc;

	/* cifs_dump_mem(" Received SecBlob ", security_blob, length); */

	asn1_open(&ctx, security_blob, length);

	/* GSSAPI header */
	if (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) {
		cFYI(1, "Error decoding negTokenInit header");
		return 0;
	} else if ((cls != ASN1_APL) || (con != ASN1_CON)
		   || (tag != ASN1_EOC)) {
		cFYI(1, "cls = %d con = %d tag = %d", cls, con, tag);
		return 0;
	}

	/* Check for SPNEGO OID -- remember to free obj->oid */
	rc = asn1_header_decode(&ctx, &end, &cls, &con, &tag);
	if (rc) {
		if ((tag == ASN1_OJI) && (con == ASN1_PRI) &&
		    (cls == ASN1_UNI)) {
			rc = asn1_oid_decode(&ctx, end, &oid, &oidlen);
			if (rc) {
				rc = compare_oid(oid, oidlen, SPNEGO_OID,
						 SPNEGO_OID_LEN);
				kfree(oid);
			}
		} else
			rc = 0;
	}

	/* SPNEGO OID not present or garbled -- bail out */
	if (!rc) {
		cFYI(1, "Error decoding negTokenInit header");
		return 0;
	}

	/* SPNEGO */
	if (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) {
		cFYI(1, "Error decoding negTokenInit");
		return 0;
	} else if ((cls != ASN1_CTX) || (con != ASN1_CON)
		   || (tag != ASN1_EOC)) {
		cFYI(1, "cls = %d con = %d tag = %d end = %p (%d) exit 0",
		     cls, con, tag, end, *end);
		return 0;
	}

	/* negTokenInit */
	if (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) {
		cFYI(1, "Error decoding negTokenInit");
		return 0;
	} else if ((cls != ASN1_UNI) || (con != ASN1_CON)
		   || (tag != ASN1_SEQ)) {
		cFYI(1, "cls = %d con = %d tag = %d end = %p (%d) exit 1",
		     cls, con, tag, end, *end);
		return 0;
	}

	/* sequence */
	if (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) {
		cFYI(1, "Error decoding 2nd part of negTokenInit");
		return 0;
	} else if ((cls != ASN1_CTX) || (con != ASN1_CON)
		   || (tag != ASN1_EOC)) {
		cFYI(1, "cls = %d con = %d tag = %d end = %p (%d) exit 0",
		     cls, con, tag, end, *end);
		return 0;
	}

	/* sequence of */
	if (asn1_header_decode
	    (&ctx, &sequence_end, &cls, &con, &tag) == 0) {
		cFYI(1, "Error decoding 2nd part of negTokenInit");
		return 0;
	} else if ((cls != ASN1_UNI) || (con != ASN1_CON)
		   || (tag != ASN1_SEQ)) {
		cFYI(1, "cls = %d con = %d tag = %d end = %p (%d) exit 1",
		     cls, con, tag, end, *end);
		return 0;
	}

	/* list of security mechanisms */
	while (!asn1_eoc_decode(&ctx, sequence_end)) {
		rc = asn1_header_decode(&ctx, &end, &cls, &con, &tag);
		if (!rc) {
			cFYI(1, "Error decoding negTokenInit hdr exit2");
			return 0;
		}
		if ((tag == ASN1_OJI) && (con == ASN1_PRI)) {
			if (asn1_oid_decode(&ctx, end, &oid, &oidlen)) {

				cFYI(1, "OID len = %d oid = 0x%lx 0x%lx "
					"0x%lx 0x%lx", oidlen, *oid,
					*(oid + 1), *(oid + 2), *(oid + 3));

				if (compare_oid(oid, oidlen, MSKRB5_OID,
						MSKRB5_OID_LEN))
					server->sec_mskerberos = true;
				else if (compare_oid(oid, oidlen, KRB5U2U_OID,
						     KRB5U2U_OID_LEN))
					server->sec_kerberosu2u = true;
				else if (compare_oid(oid, oidlen, KRB5_OID,
						     KRB5_OID_LEN))
					server->sec_kerberos = true;
				else if (compare_oid(oid, oidlen, NTLMSSP_OID,
						     NTLMSSP_OID_LEN))
					server->sec_ntlmssp = true;

				kfree(oid);
			}
		} else {
			cFYI(1, "Should be an oid what is going on?");
		}
	}

	/* mechlistMIC */
	if (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) {
		/* Check if we have reached the end of the blob, but with
		   no mechListMic (e.g. NTLMSSP instead of KRB5) */
		if (ctx.error == ASN1_ERR_DEC_EMPTY)
			goto decode_negtoken_exit;
		cFYI(1, "Error decoding last part negTokenInit exit3");
		return 0;
	} else if ((cls != ASN1_CTX) || (con != ASN1_CON)) {
		/* tag = 3 indicating mechListMIC */
		cFYI(1, "Exit 4 cls = %d con = %d tag = %d end = %p (%d)",
			cls, con, tag, end, *end);
		return 0;
	}

	/* sequence */
	if (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) {
		cFYI(1, "Error decoding last part negTokenInit exit5");
		return 0;
	} else if ((cls != ASN1_UNI) || (con != ASN1_CON)
		   || (tag != ASN1_SEQ)) {
		cFYI(1, "cls = %d con = %d tag = %d end = %p (%d)",
			cls, con, tag, end, *end);
	}

	/* sequence of */
	if (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) {
		cFYI(1, "Error decoding last part negTokenInit exit 7");
		return 0;
	} else if ((cls != ASN1_CTX) || (con != ASN1_CON)) {
		cFYI(1, "Exit 8 cls = %d con = %d tag = %d end = %p (%d)",
			cls, con, tag, end, *end);
		return 0;
	}

	/* general string */
	if (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) {
		cFYI(1, "Error decoding last part negTokenInit exit9");
		return 0;
	} else if ((cls != ASN1_UNI) || (con != ASN1_PRI)
		   || (tag != ASN1_GENSTR)) {
		cFYI(1, "Exit10 cls = %d con = %d tag = %d end = %p (%d)",
			cls, con, tag, end, *end);
		return 0;
	}
	cFYI(1, "Need to call asn1_octets_decode() function for %s",
		ctx.pointer);	/* is this UTF-8 or ASCII? */
decode_negtoken_exit:
	return 1;
}