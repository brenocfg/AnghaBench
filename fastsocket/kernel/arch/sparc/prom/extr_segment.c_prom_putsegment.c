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
struct TYPE_2__ {int /*<<< orphan*/  (* pv_setctxt ) (int,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  prom_lock ; 
 int /*<<< orphan*/  restore_current () ; 
 TYPE_1__* romvec ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int,char*,int) ; 

void
prom_putsegment(int ctx, unsigned long vaddr, int segment)
{
	unsigned long flags;
	spin_lock_irqsave(&prom_lock, flags);
	(*(romvec->pv_setctxt))(ctx, (char *) vaddr, segment);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	return;
}