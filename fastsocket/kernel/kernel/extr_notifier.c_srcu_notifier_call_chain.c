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
struct srcu_notifier_head {int dummy; } ;

/* Variables and functions */
 int __srcu_notifier_call_chain (struct srcu_notifier_head*,unsigned long,void*,int,int /*<<< orphan*/ *) ; 

int srcu_notifier_call_chain(struct srcu_notifier_head *nh,
		unsigned long val, void *v)
{
	return __srcu_notifier_call_chain(nh, val, v, -1, NULL);
}