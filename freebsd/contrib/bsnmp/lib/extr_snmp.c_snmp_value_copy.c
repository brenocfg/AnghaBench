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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * octets; } ;
struct TYPE_4__ {TYPE_1__ octetstring; } ;
struct snmp_value {scalar_t__ syntax; TYPE_2__ v; int /*<<< orphan*/  var; } ;

/* Variables and functions */
 scalar_t__ SNMP_SYNTAX_OCTETSTRING ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
snmp_value_copy(struct snmp_value *to, const struct snmp_value *from)
{
	to->var = from->var;
	to->syntax = from->syntax;

	if (from->syntax == SNMP_SYNTAX_OCTETSTRING) {
		if ((to->v.octetstring.len = from->v.octetstring.len) == 0)
			to->v.octetstring.octets = NULL;
		else {
			to->v.octetstring.octets = malloc(to->v.octetstring.len);
			if (to->v.octetstring.octets == NULL)
				return (-1);
			(void)memcpy(to->v.octetstring.octets,
			    from->v.octetstring.octets, to->v.octetstring.len);
		}
	} else
		to->v = from->v;
	return (0);
}