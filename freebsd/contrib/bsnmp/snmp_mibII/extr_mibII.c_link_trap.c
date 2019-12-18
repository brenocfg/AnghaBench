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
struct TYPE_3__ {int /*<<< orphan*/  integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * subs; } ;
struct snmp_value {TYPE_1__ v; int /*<<< orphan*/  syntax; TYPE_2__ var; } ;
struct mibif {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_SYNTAX_INTEGER ; 
 TYPE_2__ oid_ifIndex ; 
 int /*<<< orphan*/  oid_linkDown ; 
 int /*<<< orphan*/  oid_linkUp ; 
 int /*<<< orphan*/  snmp_send_trap (int /*<<< orphan*/ *,struct snmp_value*,struct snmp_value*) ; 

__attribute__((used)) static void
link_trap(struct mibif *ifp, int up)
{
	struct snmp_value ifindex;

	ifindex.var = oid_ifIndex;
	ifindex.var.subs[ifindex.var.len++] = ifp->index;
	ifindex.syntax = SNMP_SYNTAX_INTEGER;
	ifindex.v.integer = ifp->index;

	snmp_send_trap(up ? &oid_linkUp : &oid_linkDown, &ifindex,
	    (struct snmp_value *)NULL);
}