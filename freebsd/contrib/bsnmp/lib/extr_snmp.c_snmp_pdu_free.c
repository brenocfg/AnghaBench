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
typedef  size_t u_int ;
struct snmp_pdu {size_t nbindings; int /*<<< orphan*/ * bindings; } ;

/* Variables and functions */
 int /*<<< orphan*/  snmp_value_free (int /*<<< orphan*/ *) ; 

void
snmp_pdu_free(struct snmp_pdu *pdu)
{
	u_int i;

	for (i = 0; i < pdu->nbindings; i++)
		snmp_value_free(&pdu->bindings[i]);
	pdu->nbindings = 0;
}