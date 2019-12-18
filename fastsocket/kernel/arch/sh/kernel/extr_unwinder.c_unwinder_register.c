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
struct unwinder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  curr_unwinder ; 
 int /*<<< orphan*/  select_unwinder () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int unwinder_enqueue (struct unwinder*) ; 
 int /*<<< orphan*/  unwinder_lock ; 

int unwinder_register(struct unwinder *u)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&unwinder_lock, flags);
	ret = unwinder_enqueue(u);
	if (!ret)
		curr_unwinder = select_unwinder();
	spin_unlock_irqrestore(&unwinder_lock, flags);

	return ret;
}