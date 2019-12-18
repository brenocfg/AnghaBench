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
struct TYPE_3__ {int /*<<< orphan*/ * octets; } ;
struct TYPE_4__ {TYPE_1__ octetstring; } ;
struct snmp_value {scalar_t__ syntax; TYPE_2__ v; } ;

/* Variables and functions */
 scalar_t__ SNMP_SYNTAX_NULL ; 
 scalar_t__ SNMP_SYNTAX_OCTETSTRING ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
snmp_value_free(struct snmp_value *value)
{

	if (value->syntax == SNMP_SYNTAX_OCTETSTRING) {
		free(value->v.octetstring.octets);
		value->v.octetstring.octets = NULL;
	}
	value->syntax = SNMP_SYNTAX_NULL;
}