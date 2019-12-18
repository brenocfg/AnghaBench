#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; } ;
struct snmp_value {TYPE_1__ var; } ;
struct snmp_node {scalar_t__ type; TYPE_1__ oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIND ; 
 scalar_t__ SNMP_NODE_LEAF ; 
 scalar_t__ TR (int /*<<< orphan*/ ) ; 
 scalar_t__ asn_compare_oid (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ asn_is_suboid (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asn_oid2str_r (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidbuf ; 
 int /*<<< orphan*/  snmp_debug (char*,...) ; 
 struct snmp_node* tree ; 
 int tree_size ; 

__attribute__((used)) static struct snmp_node *
next_node(const struct snmp_value *value, int *pnext)
{
	struct snmp_node *tp;

	if (TR(FIND))
		snmp_debug("next: searching %s",
		    asn_oid2str_r(&value->var, oidbuf));

	*pnext = 0;
	for (tp = tree; tp < tree + tree_size; tp++) {
		if (asn_is_suboid(&tp->oid, &value->var)) {
			/* the tree OID is a sub-oid of the requested OID. */
			if (tp->type == SNMP_NODE_LEAF) {
				if (tp->oid.len == value->var.len) {
					/* request for scalar type */
					if (TR(FIND))
						snmp_debug("next: found scalar %s",
						    asn_oid2str_r(&tp->oid, oidbuf));
					return (tp);
				}
				/* try next */
			} else {
				if (TR(FIND))
					snmp_debug("next: found column %s",
					    asn_oid2str_r(&tp->oid, oidbuf));
				return (tp);
			}
		} else if (asn_is_suboid(&value->var, &tp->oid) ||
		    asn_compare_oid(&tp->oid, &value->var) >= 0) {
			if (TR(FIND))
				snmp_debug("next: found %s",
				    asn_oid2str_r(&tp->oid, oidbuf));
			*pnext = 1;
			return (tp);
		}
	}

	if (TR(FIND))
		snmp_debug("next: failed");

	return (NULL);
}