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
typedef  size_t u_long ;
struct asn_oid {size_t len; scalar_t__* subs; } ;

/* Variables and functions */

int
asn_is_suboid(const struct asn_oid *o1, const struct asn_oid *o2)
{
	u_long i;

	for (i = 0; i < o1->len; i++)
		if (i >= o2->len || o1->subs[i] != o2->subs[i])
			return (0);
	return (1);
}