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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t _dmac_addr_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _s6dmac_disable_error_irqs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* s6dmac_ctrl ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void s6dmac_disable_error_irqs(u32 dmac, u32 mask)
{
	unsigned long flags;
	spinlock_t *spinl = &s6dmac_ctrl[_dmac_addr_index(dmac)].lock;
	spin_lock_irqsave(spinl, flags);
	_s6dmac_disable_error_irqs(dmac, mask);
	spin_unlock_irqrestore(spinl, flags);
}