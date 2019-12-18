#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; scalar_t__* subs; } ;
struct snmp_value {TYPE_1__ var; } ;
struct TYPE_7__ {int len; } ;
struct snmp_node {scalar_t__ type; TYPE_2__ oid; } ;
typedef  enum snmp_syntax { ____Placeholder_snmp_syntax } snmp_syntax ;

/* Variables and functions */
 int /*<<< orphan*/  FIND ; 
 scalar_t__ SNMP_NODE_LEAF ; 
 int SNMP_SYNTAX_NOSUCHINSTANCE ; 
 int SNMP_SYNTAX_NOSUCHOBJECT ; 
 scalar_t__ TR (int /*<<< orphan*/ ) ; 
 scalar_t__ asn_compare_oid (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ asn_is_suboid (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asn_oid2str_r (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidbuf ; 
 int /*<<< orphan*/  snmp_debug (char*,...) ; 
 struct snmp_node* tree ; 
 int tree_size ; 

__attribute__((used)) static struct snmp_node *
find_node(const struct snmp_value *value, enum snmp_syntax *errp)
{
	struct snmp_node *tp;

	if (TR(FIND))
		snmp_debug("find: searching %s",
		    asn_oid2str_r(&value->var, oidbuf));

	/*
	 * If we have an exact match (the entry in the table is a
	 * sub-oid from the variable) we have found what we are for.
	 * If the table oid is higher than the variable, there is no match.
	 */
	for (tp = tree; tp < tree + tree_size; tp++) {
		if (asn_is_suboid(&tp->oid, &value->var))
			goto found;
		if (asn_compare_oid(&tp->oid, &value->var) >= 0)
			break;
	}

	if (TR(FIND))
		snmp_debug("find: no match");
	*errp = SNMP_SYNTAX_NOSUCHOBJECT;
	return (NULL);

  found:
	/* leafs must have a 0 instance identifier */
	if (tp->type == SNMP_NODE_LEAF &&
	    (value->var.len != tp->oid.len + 1 ||
	     value->var.subs[tp->oid.len] != 0)) {
		if (TR(FIND))
			snmp_debug("find: bad leaf index");
		*errp = SNMP_SYNTAX_NOSUCHINSTANCE;
		return (NULL);
	}
	if (TR(FIND))
		snmp_debug("find: found %s",
		    asn_oid2str_r(&value->var, oidbuf));
	return (tp);
}