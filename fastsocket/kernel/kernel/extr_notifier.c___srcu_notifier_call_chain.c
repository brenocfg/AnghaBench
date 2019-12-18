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
struct srcu_notifier_head {int /*<<< orphan*/  srcu; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int notifier_call_chain (int /*<<< orphan*/ *,unsigned long,void*,int,int*) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

int __srcu_notifier_call_chain(struct srcu_notifier_head *nh,
			       unsigned long val, void *v,
			       int nr_to_call, int *nr_calls)
{
	int ret;
	int idx;

	idx = srcu_read_lock(&nh->srcu);
	ret = notifier_call_chain(&nh->head, val, v, nr_to_call, nr_calls);
	srcu_read_unlock(&nh->srcu, idx);
	return ret;
}