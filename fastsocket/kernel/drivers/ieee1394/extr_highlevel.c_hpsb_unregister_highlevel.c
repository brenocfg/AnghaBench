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
struct hpsb_highlevel {int /*<<< orphan*/  hl_list; int /*<<< orphan*/  irq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  highlevel_for_each_host_unreg ; 
 int /*<<< orphan*/  hl_drivers_sem ; 
 int /*<<< orphan*/  hl_irqs_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodemgr_for_each_host (struct hpsb_highlevel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void hpsb_unregister_highlevel(struct hpsb_highlevel *hl)
{
	unsigned long flags;

	write_lock_irqsave(&hl_irqs_lock, flags);
	list_del(&hl->irq_list);
	write_unlock_irqrestore(&hl_irqs_lock, flags);

	down_write(&hl_drivers_sem);
	list_del(&hl->hl_list);
	up_write(&hl_drivers_sem);

	nodemgr_for_each_host(hl, highlevel_for_each_host_unreg);
}