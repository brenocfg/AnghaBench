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
typedef  int u_char ;
struct snmp_context {TYPE_1__* scratch; } ;
struct TYPE_2__ {int int1; } ;

/* Variables and functions */

void
ip_rollback(struct snmp_context *ctx, u_char *valp)
{
	valp[0] = ctx->scratch->int1 >> 24;
	valp[1] = ctx->scratch->int1 >> 16;
	valp[2] = ctx->scratch->int1 >> 8;
	valp[3] = ctx->scratch->int1;
}