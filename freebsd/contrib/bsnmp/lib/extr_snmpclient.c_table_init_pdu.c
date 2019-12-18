#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;
struct snmp_table {TYPE_1__ table; TYPE_1__ last_change; } ;
struct snmp_pdu {int error_index; size_t nbindings; scalar_t__ version; TYPE_2__* bindings; int /*<<< orphan*/  error_status; } ;
struct TYPE_6__ {scalar_t__ version; } ;
struct TYPE_5__ {void* syntax; TYPE_1__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_PDU_GETBULK ; 
 int /*<<< orphan*/  SNMP_PDU_GETNEXT ; 
 void* SNMP_SYNTAX_NULL ; 
 scalar_t__ SNMP_V1 ; 
 TYPE_3__ snmp_client ; 
 int /*<<< orphan*/  snmp_pdu_create (struct snmp_pdu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
table_init_pdu(const struct snmp_table *descr, struct snmp_pdu *pdu)
{
	if (snmp_client.version == SNMP_V1)
		snmp_pdu_create(pdu, SNMP_PDU_GETNEXT);
	else {
		snmp_pdu_create(pdu, SNMP_PDU_GETBULK);
		pdu->error_index = 10;
	}
	if (descr->last_change.len != 0) {
		pdu->bindings[pdu->nbindings].syntax = SNMP_SYNTAX_NULL;
		pdu->bindings[pdu->nbindings].var = descr->last_change;
		pdu->nbindings++;
		if (pdu->version != SNMP_V1)
			pdu->error_status++;
	}
	pdu->bindings[pdu->nbindings].var = descr->table;
	pdu->bindings[pdu->nbindings].syntax = SNMP_SYNTAX_NULL;
	pdu->nbindings++;
}