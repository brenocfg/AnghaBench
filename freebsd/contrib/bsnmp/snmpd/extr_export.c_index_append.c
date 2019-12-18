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
typedef  int /*<<< orphan*/  u_int ;
struct asn_oid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  index_append_off (struct asn_oid*,int /*<<< orphan*/ ,struct asn_oid const*,int /*<<< orphan*/ ) ; 

void
index_append(struct asn_oid *var, u_int sub, const struct asn_oid *idx)
{
	index_append_off(var, sub, idx, 0);
}