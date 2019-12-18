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
struct TYPE_2__ {unsigned long (* get_tick ) () ;} ;

/* Variables and functions */
 size_t MASTER ; 
 unsigned long NUM_ITERS ; 
 size_t SLAVE ; 
 unsigned long* go ; 
 int /*<<< orphan*/  membar_safe (char*) ; 
 int /*<<< orphan*/  rmb () ; 
 unsigned long stub1 () ; 
 unsigned long stub2 () ; 
 TYPE_1__* tick_ops ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline long get_delta (long *rt, long *master)
{
	unsigned long best_t0 = 0, best_t1 = ~0UL, best_tm = 0;
	unsigned long tcenter, t0, t1, tm;
	unsigned long i;

	for (i = 0; i < NUM_ITERS; i++) {
		t0 = tick_ops->get_tick();
		go[MASTER] = 1;
		membar_safe("#StoreLoad");
		while (!(tm = go[SLAVE]))
			rmb();
		go[SLAVE] = 0;
		wmb();
		t1 = tick_ops->get_tick();

		if (t1 - t0 < best_t1 - best_t0)
			best_t0 = t0, best_t1 = t1, best_tm = tm;
	}

	*rt = best_t1 - best_t0;
	*master = best_tm - best_t0;

	/* average best_t0 and best_t1 without overflow: */
	tcenter = (best_t0/2 + best_t1/2);
	if (best_t0 % 2 + best_t1 % 2 == 2)
		tcenter++;
	return tcenter - best_tm;
}