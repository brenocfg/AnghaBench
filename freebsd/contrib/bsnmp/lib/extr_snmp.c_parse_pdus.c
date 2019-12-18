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
struct snmp_value {int dummy; } ;
struct snmp_pdu {scalar_t__ nbindings; struct snmp_value* bindings; } ;
struct asn_buf {scalar_t__ asn_len; } ;
typedef  scalar_t__ int32_t ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  scalar_t__ asn_len_t ;

/* Variables and functions */
 int ASN_ERR_FAILED ; 
 int ASN_ERR_OK ; 
 scalar_t__ ASN_ERR_STOPPED (int) ; 
 scalar_t__ SNMP_MAX_BINDINGS ; 
 int get_var_binding (struct asn_buf*,struct snmp_value*) ; 
 int /*<<< orphan*/  snmp_error (char*,scalar_t__) ; 
 int snmp_parse_pdus_hdr (struct asn_buf*,struct snmp_pdu*,scalar_t__*) ; 

__attribute__((used)) static enum asn_err
parse_pdus(struct asn_buf *b, struct snmp_pdu *pdu, int32_t *ip)
{
	asn_len_t len, trailer;
	struct snmp_value *v;
	enum asn_err err, err1;

	err = snmp_parse_pdus_hdr(b, pdu, &len);
	if (ASN_ERR_STOPPED(err))
		return (err);

	trailer = b->asn_len - len;

	v = pdu->bindings;
	err = ASN_ERR_OK;
	while (b->asn_len != 0) {
		if (pdu->nbindings == SNMP_MAX_BINDINGS) {
			snmp_error("too many bindings (> %u) in PDU",
			    SNMP_MAX_BINDINGS);
			return (ASN_ERR_FAILED);
		}
		err1 = get_var_binding(b, v);
		if (ASN_ERR_STOPPED(err1))
			return (ASN_ERR_FAILED);
		if (err1 != ASN_ERR_OK && err == ASN_ERR_OK) {
			err = err1;
			*ip = pdu->nbindings + 1;
		}
		pdu->nbindings++;
		v++;
	}

	b->asn_len = trailer;

	return (err);
}