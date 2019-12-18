#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct rtable* rt_next; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct rtable {TYPE_2__ u; } ;
struct TYPE_6__ {struct rtable* chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  rt_free (struct rtable*) ; 
 int /*<<< orphan*/  rt_hash_lock_addr (unsigned int) ; 
 unsigned int rt_hash_mask ; 
 TYPE_3__* rt_hash_table ; 
 int /*<<< orphan*/  rt_is_expired (struct rtable*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt_do_flush(int process_context)
{
	unsigned int i;
	struct rtable *rth, *next;
	struct rtable * tail;

	for (i = 0; i <= rt_hash_mask; i++) {
		if (process_context && need_resched())
			cond_resched();
		rth = rt_hash_table[i].chain;
		if (!rth)
			continue;

		spin_lock_bh(rt_hash_lock_addr(i));
#ifdef CONFIG_NET_NS
		{
		struct rtable ** prev, * p;

		rth = rt_hash_table[i].chain;

		/* defer releasing the head of the list after spin_unlock */
		for (tail = rth; tail; tail = tail->u.dst.rt_next)
			if (!rt_is_expired(tail))
				break;
		if (rth != tail)
			rt_hash_table[i].chain = tail;

		/* call rt_free on entries after the tail requiring flush */
		prev = &rt_hash_table[i].chain;
		for (p = *prev; p; p = next) {
			next = p->u.dst.rt_next;
			if (!rt_is_expired(p)) {
				prev = &p->u.dst.rt_next;
			} else {
				*prev = next;
				rt_free(p);
			}
		}
		}
#else
		rth = rt_hash_table[i].chain;
		rt_hash_table[i].chain = NULL;
		tail = NULL;
#endif
		spin_unlock_bh(rt_hash_lock_addr(i));

		for (; rth != tail; rth = next) {
			next = rth->u.dst.rt_next;
			rt_free(rth);
		}
	}
}