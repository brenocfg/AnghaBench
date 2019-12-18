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
struct snmp_pdu {scalar_t__ version; int flags; int context_engine_len; int /*<<< orphan*/  context_name; int /*<<< orphan*/ * context_engine; int /*<<< orphan*/  security_model; int /*<<< orphan*/  identifier; int /*<<< orphan*/  user; int /*<<< orphan*/  engine; int /*<<< orphan*/  request_id; int /*<<< orphan*/  type; int /*<<< orphan*/  community; } ;

/* Variables and functions */
 int SNMP_MSG_AUTODISCOVER ; 
 int /*<<< orphan*/  SNMP_PDU_REPORT ; 
 int /*<<< orphan*/  SNMP_PDU_RESPONSE ; 
 scalar_t__ SNMP_V3 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct snmp_pdu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snmp_pdu_init_secparams (struct snmp_pdu*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
snmp_pdu_create_response(const struct snmp_pdu *pdu, struct snmp_pdu *resp)
{
	memset(resp, 0, sizeof(*resp));
	strcpy(resp->community, pdu->community);
	resp->version = pdu->version;
	if (pdu->flags & SNMP_MSG_AUTODISCOVER)
		resp->type = SNMP_PDU_REPORT; /* RFC 3414.4 */
	else
		resp->type = SNMP_PDU_RESPONSE;
	resp->request_id = pdu->request_id;
	resp->version = pdu->version;

	if (resp->version != SNMP_V3)
		return;

	memcpy(&resp->engine, &pdu->engine, sizeof(pdu->engine));
	memcpy(&resp->user, &pdu->user, sizeof(pdu->user));
	snmp_pdu_init_secparams(resp);
	resp->identifier = pdu->identifier;
	resp->security_model = pdu->security_model;
	resp->context_engine_len = pdu->context_engine_len;
	memcpy(resp->context_engine, pdu->context_engine,
	    resp->context_engine_len);
	strlcpy(resp->context_name, pdu->context_name,
	    sizeof(resp->context_name));
}