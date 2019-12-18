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
struct memcg_stock_pcp {int /*<<< orphan*/  charge; struct mem_cgroup* cached; } ;
struct mem_cgroup {int /*<<< orphan*/  memsw; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 scalar_t__ do_swap_account ; 
 int /*<<< orphan*/  res_counter_uncharge (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drain_stock(struct memcg_stock_pcp *stock)
{
	struct mem_cgroup *old = stock->cached;

	if (stock->charge) {
		res_counter_uncharge(&old->res, stock->charge);
		if (do_swap_account)
			res_counter_uncharge(&old->memsw, stock->charge);
	}
	stock->cached = NULL;
	stock->charge = 0;
}