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
struct snmp_context {TYPE_1__* scratch; } ;
struct asn_oid {int dummy; } ;
struct TYPE_2__ {scalar_t__ ptr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

void
oid_rollback(struct snmp_context *ctx, struct asn_oid *oid)
{
	*oid = *(struct asn_oid *)ctx->scratch->ptr1;
	free(ctx->scratch->ptr1);
}