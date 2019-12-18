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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int max_msg_size; } ;
struct snmp_pdu {scalar_t__ version; int identifier; int type; int security_model; int context_engine_len; int generic_trap; int specific_trap; int request_id; int error_status; int error_index; int /*<<< orphan*/ * vars_ptr; int /*<<< orphan*/  time_stamp; int /*<<< orphan*/  agent_addr; int /*<<< orphan*/  enterprise; int /*<<< orphan*/ * pdu_ptr; scalar_t__ community; scalar_t__ context_name; scalar_t__ context_engine; int /*<<< orphan*/ * scoped_ptr; int /*<<< orphan*/  flags; TYPE_1__ engine; int /*<<< orphan*/ * outer_ptr; } ;
struct asn_buf {int dummy; } ;
typedef  enum snmp_code { ____Placeholder_snmp_code } snmp_code ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;

/* Variables and functions */
 int ASN_CLASS_CONTEXT ; 
 scalar_t__ ASN_ERR_OK ; 
 int ASN_TYPE_CONSTRUCTED ; 
 int ASN_TYPE_SEQUENCE ; 
 int SNMP_CODE_BADVERS ; 
 int SNMP_CODE_FAILED ; 
 scalar_t__ SNMP_CODE_OK ; 
 int /*<<< orphan*/  SNMP_MSG_REPORT_FLAG ; 
 int SNMP_PDU_GETBULK ; 
 int SNMP_PDU_INFORM ; 
 int SNMP_PDU_REPORT ; 
 int SNMP_PDU_RESPONSE ; 
 int SNMP_PDU_TRAP ; 
 int SNMP_PDU_TRAP2 ; 
 int SNMP_SECMODEL_USM ; 
 scalar_t__ SNMP_V1 ; 
 scalar_t__ SNMP_V2c ; 
 scalar_t__ SNMP_V3 ; 
 scalar_t__ asn_commit_header (struct asn_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ asn_put_integer (struct asn_buf*,int) ; 
 scalar_t__ asn_put_ipaddress (struct asn_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ asn_put_objid (struct asn_buf*,int /*<<< orphan*/ *) ; 
 scalar_t__ asn_put_octetstring (struct asn_buf*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ asn_put_temp_header (struct asn_buf*,int,int /*<<< orphan*/ **) ; 
 scalar_t__ asn_put_timeticks (struct asn_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ pdu_encode_secparams (struct asn_buf*,struct snmp_pdu*) ; 
 int strlen (scalar_t__) ; 

enum snmp_code
snmp_pdu_encode_header(struct asn_buf *b, struct snmp_pdu *pdu)
{
	enum asn_err err;
	u_char *v3_hdr_ptr;

	if (asn_put_temp_header(b, (ASN_TYPE_SEQUENCE|ASN_TYPE_CONSTRUCTED),
	    &pdu->outer_ptr) != ASN_ERR_OK)
		return (SNMP_CODE_FAILED);

	if (pdu->version == SNMP_V1)
		err = asn_put_integer(b, 0);
	else if (pdu->version == SNMP_V2c)
		err = asn_put_integer(b, 1);
	else if (pdu->version == SNMP_V3)
		err = asn_put_integer(b, 3);
	else
		return (SNMP_CODE_BADVERS);
	if (err != ASN_ERR_OK)
		return (SNMP_CODE_FAILED);

	if (pdu->version == SNMP_V3) {
		if (asn_put_temp_header(b, (ASN_TYPE_SEQUENCE |
		    ASN_TYPE_CONSTRUCTED), &v3_hdr_ptr) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);

		if (asn_put_integer(b, pdu->identifier) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);

		if (asn_put_integer(b, pdu->engine.max_msg_size) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);

		if (pdu->type != SNMP_PDU_RESPONSE &&
		    pdu->type != SNMP_PDU_TRAP &&
		    pdu->type != SNMP_PDU_TRAP2 &&
		    pdu->type != SNMP_PDU_REPORT)
			pdu->flags |= SNMP_MSG_REPORT_FLAG;

		if (asn_put_octetstring(b, (u_char *)&pdu->flags, 1)
		    != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);

		if (asn_put_integer(b, pdu->security_model) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);

		if (asn_commit_header(b, v3_hdr_ptr, NULL) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);

		if (pdu->security_model != SNMP_SECMODEL_USM)
			return (SNMP_CODE_FAILED);

		if (pdu_encode_secparams(b, pdu) != SNMP_CODE_OK)
			return (SNMP_CODE_FAILED);

		/*  View-based Access Conntrol information */
		if (asn_put_temp_header(b, (ASN_TYPE_SEQUENCE |
		    ASN_TYPE_CONSTRUCTED), &pdu->scoped_ptr) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);

		if (asn_put_octetstring(b, (u_char *)pdu->context_engine,
		    pdu->context_engine_len) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);

		if (asn_put_octetstring(b, (u_char *)pdu->context_name,
		    strlen(pdu->context_name)) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);
	} else {
		if (asn_put_octetstring(b, (u_char *)pdu->community,
		    strlen(pdu->community)) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);
	}

	if (asn_put_temp_header(b, (ASN_TYPE_CONSTRUCTED | ASN_CLASS_CONTEXT |
	    pdu->type), &pdu->pdu_ptr) != ASN_ERR_OK)
		return (SNMP_CODE_FAILED);

	if (pdu->type == SNMP_PDU_TRAP) {
		if (pdu->version != SNMP_V1 ||
		    asn_put_objid(b, &pdu->enterprise) != ASN_ERR_OK ||
		    asn_put_ipaddress(b, pdu->agent_addr) != ASN_ERR_OK ||
		    asn_put_integer(b, pdu->generic_trap) != ASN_ERR_OK ||
		    asn_put_integer(b, pdu->specific_trap) != ASN_ERR_OK ||
		    asn_put_timeticks(b, pdu->time_stamp) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);
	} else {
		if (pdu->version == SNMP_V1 && (pdu->type == SNMP_PDU_GETBULK ||
		    pdu->type == SNMP_PDU_INFORM ||
		    pdu->type == SNMP_PDU_TRAP2 ||
		    pdu->type == SNMP_PDU_REPORT))
			return (SNMP_CODE_FAILED);

		if (asn_put_integer(b, pdu->request_id) != ASN_ERR_OK ||
		    asn_put_integer(b, pdu->error_status) != ASN_ERR_OK ||
		    asn_put_integer(b, pdu->error_index) != ASN_ERR_OK)
			return (SNMP_CODE_FAILED);
	}

	if (asn_put_temp_header(b, (ASN_TYPE_SEQUENCE|ASN_TYPE_CONSTRUCTED),
	    &pdu->vars_ptr) != ASN_ERR_OK)
		return (SNMP_CODE_FAILED);

	return (SNMP_CODE_OK);
}