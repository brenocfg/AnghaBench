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
typedef  int u_char ;
struct TYPE_4__ {int* ipaddress; } ;
struct snmp_value {TYPE_2__ v; } ;
struct snmp_context {TYPE_1__* scratch; } ;
struct TYPE_3__ {int int1; } ;

/* Variables and functions */

int
ip_save(struct snmp_value *value, struct snmp_context *ctx, u_char *valp)
{
	ctx->scratch->int1 = (valp[0] << 24) | (valp[1] << 16) | (valp[2] << 8)
	    | valp[3];

	valp[0] = value->v.ipaddress[0];
	valp[1] = value->v.ipaddress[1];
	valp[2] = value->v.ipaddress[2];
	valp[3] = value->v.ipaddress[3];

	return (0);
}