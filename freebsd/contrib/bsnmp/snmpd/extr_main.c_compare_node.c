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
struct snmp_node {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int asn_compare_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
compare_node(const void *v1, const void *v2)
{
	const struct snmp_node *n1 = v1;
	const struct snmp_node *n2 = v2;

	return (asn_compare_oid(&n1->oid, &n2->oid));
}