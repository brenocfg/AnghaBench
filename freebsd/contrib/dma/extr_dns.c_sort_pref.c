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
struct TYPE_2__ {int ai_family; } ;
struct mx_hostentry {int pref; TYPE_1__ ai; } ;

/* Variables and functions */

__attribute__((used)) static int
sort_pref(const void *a, const void *b)
{
	const struct mx_hostentry *ha = a, *hb = b;
	int v;

	/* sort increasing by preference primarily */
	v = ha->pref - hb->pref;
	if (v != 0)
		return (v);

	/* sort PF_INET6 before PF_INET */
	v = - (ha->ai.ai_family - hb->ai.ai_family);
	return (v);
}