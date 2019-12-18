#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_2__ {scalar_t__ priv_proto; } ;
struct snmp_pdu {scalar_t__ version; size_t scoped_len; size_t context_engine_len; char* context_name; int /*<<< orphan*/  type; int /*<<< orphan*/  error_index; int /*<<< orphan*/  error_status; scalar_t__ context_engine; TYPE_1__ user; } ;
struct asn_buf {size_t asn_len; size_t asn_ptr; int /*<<< orphan*/  asn_cptr; } ;
typedef  enum snmp_ret { ____Placeholder_snmp_ret } snmp_ret ;
typedef  enum snmp_code { ____Placeholder_snmp_code } snmp_code ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  size_t asn_len_t ;

/* Variables and functions */
 int ASN_CLASS_CONTEXT ; 
 scalar_t__ ASN_ERR_OK ; 
 scalar_t__ ASN_ERR_STOPPED (int) ; 
 int ASN_TYPE_CONSTRUCTED ; 
 int ASN_TYPE_MASK ; 
 int ASN_TYPE_OCTETSTRING ; 
 int SNMP_CODE_OK ; 
 size_t SNMP_CONTEXT_NAME_SIZ ; 
 size_t SNMP_ENGINE_ID_SIZ ; 
 int /*<<< orphan*/  SNMP_PDU_RESPONSE ; 
 scalar_t__ SNMP_PRIV_NOPRIV ; 
 int SNMP_RET_IGN ; 
 int SNMP_RET_OK ; 
 scalar_t__ SNMP_V3 ; 
 scalar_t__ asn_get_header (struct asn_buf*,int*,size_t*) ; 
 scalar_t__ asn_get_octetstring (struct asn_buf*,int*,size_t*) ; 
 scalar_t__ asn_get_sequence (struct asn_buf*,size_t*) ; 
 int /*<<< orphan*/  memcpy (size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  snmp_error (char*) ; 
 int snmp_fix_encoding (struct asn_buf*,struct snmp_pdu*) ; 
 int snmp_parse_pdus_hdr (struct asn_buf*,struct snmp_pdu*,size_t*) ; 
 int /*<<< orphan*/  snmp_pdu_create_response (struct snmp_pdu const*,struct snmp_pdu*) ; 
 int snmp_pdu_decode_header (struct asn_buf*,struct snmp_pdu*) ; 
 int snmp_pdu_encode_header (struct asn_buf*,struct snmp_pdu*) ; 

enum snmp_ret
snmp_make_errresp(const struct snmp_pdu *pdu, struct asn_buf *pdu_b,
    struct asn_buf *resp_b)
{
	u_char type;
	asn_len_t len;
	struct snmp_pdu resp;
	enum asn_err err;
	enum snmp_code code;

	snmp_pdu_create_response(pdu, &resp);

	if ((code = snmp_pdu_decode_header(pdu_b, &resp)) != SNMP_CODE_OK)
		return (SNMP_RET_IGN);

	if (pdu->version == SNMP_V3) {
		if (resp.user.priv_proto != SNMP_PRIV_NOPRIV &&
		   (asn_get_header(pdu_b, &type, &resp.scoped_len) != ASN_ERR_OK
		   || type != ASN_TYPE_OCTETSTRING)) {
			snmp_error("cannot decode encrypted pdu");
			return (SNMP_RET_IGN);
		}

		if (asn_get_sequence(pdu_b, &len) != ASN_ERR_OK) {
			snmp_error("cannot decode scoped pdu header");
			return (SNMP_RET_IGN);
		}

		len = SNMP_ENGINE_ID_SIZ;
		if (asn_get_octetstring(pdu_b, (u_char *)resp.context_engine,
		    &len) != ASN_ERR_OK) {
			snmp_error("cannot decode msg context engine");
			return (SNMP_RET_IGN);
		}
		resp.context_engine_len = len;
		len = SNMP_CONTEXT_NAME_SIZ;
		if (asn_get_octetstring(pdu_b, (u_char *)resp.context_name,
		    &len) != ASN_ERR_OK) {
			snmp_error("cannot decode msg context name");
			return (SNMP_RET_IGN);
		}
		resp.context_name[len] = '\0';
	}


	if (asn_get_header(pdu_b, &type, &len) != ASN_ERR_OK) {
		snmp_error("cannot get pdu header");
		return (SNMP_RET_IGN);
	}

	if ((type & ~ASN_TYPE_MASK) !=
	    (ASN_TYPE_CONSTRUCTED | ASN_CLASS_CONTEXT)) {
		snmp_error("bad pdu header tag");
		return (SNMP_RET_IGN);
	}

	err = snmp_parse_pdus_hdr(pdu_b, &resp, &len);
	if (ASN_ERR_STOPPED(err))
		return (SNMP_RET_IGN);
	if (pdu_b->asn_len < len)
		return (SNMP_RET_IGN);
	pdu_b->asn_len = len;

	/* now we have the bindings left - construct new message */
	resp.error_status = pdu->error_status;
	resp.error_index = pdu->error_index;
	resp.type = SNMP_PDU_RESPONSE;

	code = snmp_pdu_encode_header(resp_b, &resp);
	if (code != SNMP_CODE_OK)
		return (SNMP_RET_IGN);

	if (pdu_b->asn_len > resp_b->asn_len)
		/* too short */
		return (SNMP_RET_IGN);
	(void)memcpy(resp_b->asn_ptr, pdu_b->asn_cptr, pdu_b->asn_len);
	resp_b->asn_len -= pdu_b->asn_len;
	resp_b->asn_ptr += pdu_b->asn_len;

	code = snmp_fix_encoding(resp_b, &resp);
	if (code != SNMP_CODE_OK)
		return (SNMP_RET_IGN);

	return (SNMP_RET_OK);
}