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
struct TYPE_3__ {int /*<<< orphan*/  engine_boots; } ;
struct TYPE_4__ {scalar_t__ auth_proto; int priv_proto; } ;
struct snmp_pdu {int /*<<< orphan*/  flags; int /*<<< orphan*/  msg_salt; TYPE_1__ engine; TYPE_2__ user; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ SNMP_AUTH_NOAUTH ; 
 int /*<<< orphan*/  SNMP_MSG_AUTH_FLAG ; 
 int /*<<< orphan*/  SNMP_MSG_PRIV_FLAG ; 
#define  SNMP_PRIV_AES 129 
#define  SNMP_PRIV_DES 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  random () ; 

void
snmp_pdu_init_secparams(struct snmp_pdu *pdu)
{
	int32_t rval;

	if (pdu->user.auth_proto != SNMP_AUTH_NOAUTH)
		pdu->flags |= SNMP_MSG_AUTH_FLAG;

	switch (pdu->user.priv_proto) {
	case SNMP_PRIV_DES:
		memcpy(pdu->msg_salt, &pdu->engine.engine_boots,
		    sizeof(pdu->engine.engine_boots));
		rval = random();
		memcpy(pdu->msg_salt + sizeof(pdu->engine.engine_boots), &rval,
		    sizeof(int32_t));
		pdu->flags |= SNMP_MSG_PRIV_FLAG;
		break;
	case SNMP_PRIV_AES:
		rval = random();
		memcpy(pdu->msg_salt, &rval, sizeof(int32_t));
		rval = random();
		memcpy(pdu->msg_salt + sizeof(int32_t), &rval, sizeof(int32_t));
		pdu->flags |= SNMP_MSG_PRIV_FLAG;
		break;
	default:
		break;
	}
}