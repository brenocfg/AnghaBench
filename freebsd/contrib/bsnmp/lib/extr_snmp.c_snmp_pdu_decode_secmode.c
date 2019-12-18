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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u_char ;
struct TYPE_2__ {scalar_t__ auth_proto; scalar_t__ priv_proto; } ;
struct snmp_pdu {int flags; TYPE_1__ user; int /*<<< orphan*/  scoped_ptr; int /*<<< orphan*/  scoped_len; int /*<<< orphan*/  msg_digest; } ;
struct asn_buf {int /*<<< orphan*/  asn_ptr; } ;
typedef  enum snmp_code { ____Placeholder_snmp_code } snmp_code ;

/* Variables and functions */
 scalar_t__ ASN_ERR_OK ; 
 scalar_t__ ASN_TYPE_OCTETSTRING ; 
 scalar_t__ SNMP_AUTH_NOAUTH ; 
 int SNMP_CODE_BADDIGEST ; 
 int SNMP_CODE_BADSECLEVEL ; 
 int SNMP_CODE_FAILED ; 
 int SNMP_CODE_OK ; 
 int SNMP_MSG_AUTH_FLAG ; 
 int SNMP_MSG_PRIV_FLAG ; 
 scalar_t__ SNMP_PRIV_NOPRIV ; 
 int SNMP_USM_AUTH_SIZE ; 
 scalar_t__ asn_get_header (struct asn_buf*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snmp_error (char*) ; 
 int snmp_pdu_calc_digest (struct snmp_pdu*,int /*<<< orphan*/ *) ; 
 int snmp_pdu_decrypt (struct snmp_pdu*) ; 

enum snmp_code
snmp_pdu_decode_secmode(struct asn_buf *b, struct snmp_pdu *pdu)
{
	u_char type;
	enum snmp_code code;
	uint8_t	digest[SNMP_USM_AUTH_SIZE];

	if (pdu->user.auth_proto != SNMP_AUTH_NOAUTH &&
	    (pdu->flags & SNMP_MSG_AUTH_FLAG) == 0)
		return (SNMP_CODE_BADSECLEVEL);

	if ((code = snmp_pdu_calc_digest(pdu, digest)) !=
	    SNMP_CODE_OK)
		return (SNMP_CODE_FAILED);

	if (pdu->user.auth_proto != SNMP_AUTH_NOAUTH &&
	    memcmp(digest, pdu->msg_digest, sizeof(pdu->msg_digest)) != 0)
		return (SNMP_CODE_BADDIGEST);

	if (pdu->user.priv_proto != SNMP_PRIV_NOPRIV && (asn_get_header(b, &type,
	    &pdu->scoped_len) != ASN_ERR_OK || type != ASN_TYPE_OCTETSTRING)) {
		snmp_error("cannot decode encrypted pdu");
		return (SNMP_CODE_FAILED);
	}
	pdu->scoped_ptr = b->asn_ptr;

	if (pdu->user.priv_proto != SNMP_PRIV_NOPRIV &&
	    (pdu->flags & SNMP_MSG_PRIV_FLAG) == 0)
		return (SNMP_CODE_BADSECLEVEL);

	if ((code = snmp_pdu_decrypt(pdu)) != SNMP_CODE_OK)
		return (SNMP_CODE_FAILED);

	return (code);
}