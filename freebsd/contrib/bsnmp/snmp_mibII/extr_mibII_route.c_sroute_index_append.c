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
typedef  int u_int ;
struct sroute {int /*<<< orphan*/ * index; } ;
struct asn_oid {int len; int /*<<< orphan*/ * subs; } ;

/* Variables and functions */

__attribute__((used)) static void
sroute_index_append(struct asn_oid *oid, u_int sub, const struct sroute *s)
{
	int i;

	oid->len = sub + 13;
	for (i = 0; i < 13; i++)
		oid->subs[sub + i] = s->index[i];
}