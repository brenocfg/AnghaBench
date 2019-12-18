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
struct snmp_value {int /*<<< orphan*/  var; } ;
struct snmp_node {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 scalar_t__ asn_is_suboid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct snmp_node* tree ; 
 int tree_size ; 

__attribute__((used)) static struct snmp_node *
find_subnode(const struct snmp_value *value)
{
	struct snmp_node *tp;

	for (tp = tree; tp < tree + tree_size; tp++) {
		if (asn_is_suboid(&value->var, &tp->oid))
			return (tp);
	}
	return (NULL);
}