#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {char* sec_name; } ;
struct TYPE_3__ {size_t engine_len; int /*<<< orphan*/  engine_time; int /*<<< orphan*/  engine_boots; int /*<<< orphan*/  engine_id; } ;
struct snmp_pdu {int flags; int /*<<< orphan*/ * digest_ptr; int /*<<< orphan*/  msg_salt; int /*<<< orphan*/  msg_digest; TYPE_2__ user; TYPE_1__ engine; } ;
struct asn_buf {int asn_len; int /*<<< orphan*/ * asn_ptr; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  size_t asn_len_t ;

/* Variables and functions */
 int ASN_ERR_FAILED ; 
 scalar_t__ ASN_ERR_OK ; 
 int /*<<< orphan*/ * ASN_MAXLENLEN ; 
 size_t SNMP_ADM_STR32_SIZ ; 
 size_t SNMP_ENGINE_ID_SIZ ; 
 int SNMP_MSG_AUTH_FLAG ; 
 int SNMP_MSG_PRIV_FLAG ; 
 int /*<<< orphan*/ * SNMP_USM_AUTH_SIZE ; 
 scalar_t__ asn_get_integer (struct asn_buf*,int /*<<< orphan*/ *) ; 
 scalar_t__ asn_get_octetstring (struct asn_buf*,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ asn_get_sequence (struct asn_buf*,size_t*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snmp_error (char*) ; 

__attribute__((used)) static enum asn_err
parse_secparams(struct asn_buf *b, struct snmp_pdu *pdu)
{
	asn_len_t octs_len;
	u_char buf[256]; /* XXX: calc max possible size here */
	struct asn_buf tb;

	memset(buf, 0, 256);
	tb.asn_ptr = buf;
	tb.asn_len = 256;
	u_int len = 256;

	if (asn_get_octetstring(b, buf, &len) != ASN_ERR_OK) {
		snmp_error("cannot parse usm header");
		return (ASN_ERR_FAILED);
	}
	tb.asn_len = len;

	if (asn_get_sequence(&tb, &octs_len) != ASN_ERR_OK) {
		snmp_error("cannot decode usm header");
		return (ASN_ERR_FAILED);
	}

	octs_len = SNMP_ENGINE_ID_SIZ;
	if (asn_get_octetstring(&tb, (u_char *)&pdu->engine.engine_id,
	    &octs_len) != ASN_ERR_OK) {
		snmp_error("cannot decode msg engine id");
		return (ASN_ERR_FAILED);
	}
	pdu->engine.engine_len = octs_len;

	if (asn_get_integer(&tb, &pdu->engine.engine_boots) != ASN_ERR_OK) {
		snmp_error("cannot decode msg engine boots");
		return (ASN_ERR_FAILED);
	}

	if (asn_get_integer(&tb, &pdu->engine.engine_time) != ASN_ERR_OK) {
		snmp_error("cannot decode msg engine time");
		return (ASN_ERR_FAILED);
	}

	octs_len = SNMP_ADM_STR32_SIZ - 1;
	if (asn_get_octetstring(&tb, (u_char *)&pdu->user.sec_name, &octs_len)
	    != ASN_ERR_OK) {
		snmp_error("cannot decode msg user name");
		return (ASN_ERR_FAILED);
	}
	pdu->user.sec_name[octs_len] = '\0';

	octs_len = sizeof(pdu->msg_digest);
	if (asn_get_octetstring(&tb, (u_char *)&pdu->msg_digest, &octs_len) !=
	    ASN_ERR_OK || ((pdu->flags & SNMP_MSG_AUTH_FLAG) != 0 &&
	    octs_len != sizeof(pdu->msg_digest))) {
		snmp_error("cannot decode msg authentication param");
		return (ASN_ERR_FAILED);
	}

	octs_len = sizeof(pdu->msg_salt);
	if (asn_get_octetstring(&tb, (u_char *)&pdu->msg_salt, &octs_len) !=
	    ASN_ERR_OK ||((pdu->flags & SNMP_MSG_PRIV_FLAG) != 0 &&
	    octs_len != sizeof(pdu->msg_salt))) {
		snmp_error("cannot decode msg authentication param");
		return (ASN_ERR_FAILED);
	}

	if ((pdu->flags & SNMP_MSG_AUTH_FLAG) != 0) {
		pdu->digest_ptr = b->asn_ptr - SNMP_USM_AUTH_SIZE;
		pdu->digest_ptr -= octs_len + ASN_MAXLENLEN;
	}

	return (ASN_ERR_OK);
}