#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct asn_oid {int dummy; } ;
struct TYPE_2__ {struct asn_oid oid; } ;
struct snmp_value {TYPE_1__ v; } ;

/* Variables and functions */
 int SNMP_ERR_NOERROR ; 

int
oid_get(struct snmp_value *value, const struct asn_oid *oid)
{
	value->v.oid = *oid;
	return (SNMP_ERR_NOERROR);
}