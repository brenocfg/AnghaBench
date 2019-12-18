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
typedef  scalar_t__ u32 ;
struct rt6_info {TYPE_1__* rt6i_node; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {scalar_t__ fn_sernum; } ;

/* Variables and functions */

__attribute__((used)) static struct dst_entry *ip6_dst_check(struct dst_entry *dst, u32 cookie)
{
	struct rt6_info *rt;

	rt = (struct rt6_info *) dst;

	if (rt && rt->rt6i_node && (rt->rt6i_node->fn_sernum == cookie))
		return dst;

	return NULL;
}