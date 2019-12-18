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
struct TYPE_3__ {struct rt6_info* rt6_next; } ;
struct TYPE_4__ {TYPE_1__ dst; } ;
struct rt6_info {TYPE_2__ u; } ;
struct fib6_walker_t {struct rt6_info* leaf; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int rt6_dump_route (struct rt6_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib6_dump_node(struct fib6_walker_t *w)
{
	int res;
	struct rt6_info *rt;

	for (rt = w->leaf; rt; rt = rt->u.dst.rt6_next) {
		res = rt6_dump_route(rt, w->args);
		if (res < 0) {
			/* Frame is full, suspend walking */
			w->leaf = rt;
			return 1;
		}
		WARN_ON(res == 0);
	}
	w->leaf = NULL;
	return 0;
}