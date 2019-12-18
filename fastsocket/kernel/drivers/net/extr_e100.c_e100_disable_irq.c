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
struct nic {int /*<<< orphan*/  cmd_lock; TYPE_2__* csr; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_hi; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  e100_write_flush (struct nic*) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_mask_all ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void e100_disable_irq(struct nic *nic)
{
	unsigned long flags;

	spin_lock_irqsave(&nic->cmd_lock, flags);
	iowrite8(irq_mask_all, &nic->csr->scb.cmd_hi);
	e100_write_flush(nic);
	spin_unlock_irqrestore(&nic->cmd_lock, flags);
}