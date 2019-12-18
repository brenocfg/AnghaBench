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
struct subchannel {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int cio_disable_subchannel (struct subchannel*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eadm_quiesce(struct subchannel *sch)
{
	int ret;

	do {
		spin_lock_irq(sch->lock);
		ret = cio_disable_subchannel(sch);
		spin_unlock_irq(sch->lock);
	} while (ret == -EBUSY);
}