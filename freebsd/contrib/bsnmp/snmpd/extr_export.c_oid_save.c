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
struct asn_oid {int dummy; } ;
struct TYPE_4__ {struct asn_oid oid; } ;
struct snmp_value {TYPE_2__ v; } ;
struct snmp_context {TYPE_1__* scratch; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ptr1; } ;

/* Variables and functions */
 int SNMP_ERR_RES_UNAVAIL ; 
 int /*<<< orphan*/ * malloc (int) ; 

int
oid_save(struct snmp_value *value, struct snmp_context *ctx,
    struct asn_oid *oid)
{
	if ((ctx->scratch->ptr1 = malloc(sizeof(struct asn_oid))) == NULL)
		return (SNMP_ERR_RES_UNAVAIL);
	*(struct asn_oid *)ctx->scratch->ptr1 = *oid;
	*oid = value->v.oid;

	return (0);
}