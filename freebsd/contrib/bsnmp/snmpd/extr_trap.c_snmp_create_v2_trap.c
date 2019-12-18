#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snmp_pdu {int nbindings; TYPE_2__* bindings; int /*<<< orphan*/  error_status; scalar_t__ error_index; int /*<<< orphan*/  request_id; int /*<<< orphan*/  type; int /*<<< orphan*/  version; int /*<<< orphan*/  community; } ;
struct asn_oid {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; scalar_t__* subs; } ;
struct TYPE_5__ {struct asn_oid oid; scalar_t__ uint32; } ;
struct TYPE_6__ {TYPE_1__ v; int /*<<< orphan*/  syntax; TYPE_3__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  SNMP_PDU_TRAP2 ; 
 int /*<<< orphan*/  SNMP_SYNTAX_OID ; 
 int /*<<< orphan*/  SNMP_SYNTAX_TIMETICKS ; 
 int /*<<< orphan*/  SNMP_V2c ; 
 scalar_t__ get_ticks () ; 
 int /*<<< orphan*/  memset (struct snmp_pdu*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ oid_snmpTrapOID ; 
 TYPE_3__ oid_sysUpTime ; 
 int /*<<< orphan*/  reqid_next (int /*<<< orphan*/ ) ; 
 scalar_t__ start_tick ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_reqid ; 

__attribute__((used)) static void
snmp_create_v2_trap(struct snmp_pdu *pdu, char *com,
    const struct asn_oid *trap_oid)
{
	memset(pdu, 0, sizeof(*pdu));
	strlcpy(pdu->community, com, sizeof(pdu->community));

	pdu->version = SNMP_V2c;
	pdu->type = SNMP_PDU_TRAP2;
	pdu->request_id = reqid_next(trap_reqid);
	pdu->error_index = 0;
	pdu->error_status = SNMP_ERR_NOERROR;

	pdu->bindings[0].var = oid_sysUpTime;
	pdu->bindings[0].var.subs[pdu->bindings[0].var.len++] = 0;
	pdu->bindings[0].syntax = SNMP_SYNTAX_TIMETICKS;
	pdu->bindings[0].v.uint32 = get_ticks() - start_tick;

	pdu->bindings[1].var = oid_snmpTrapOID;
	pdu->bindings[1].var.subs[pdu->bindings[1].var.len++] = 0;
	pdu->bindings[1].syntax = SNMP_SYNTAX_OID;
	pdu->bindings[1].v.oid = *trap_oid;

	pdu->nbindings = 2;
}