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
struct hpsb_highlevel {scalar_t__ add_host; int /*<<< orphan*/  irq_list; int /*<<< orphan*/  hl_list; int /*<<< orphan*/  addr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  highlevel_for_each_host_reg ; 
 int /*<<< orphan*/  hl_drivers ; 
 int /*<<< orphan*/  hl_drivers_sem ; 
 int /*<<< orphan*/  hl_irqs ; 
 int /*<<< orphan*/  hl_irqs_lock ; 
 int /*<<< orphan*/  hpsb_init_highlevel (struct hpsb_highlevel*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodemgr_for_each_host (struct hpsb_highlevel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void hpsb_register_highlevel(struct hpsb_highlevel *hl)
{
	unsigned long flags;

	hpsb_init_highlevel(hl);
	INIT_LIST_HEAD(&hl->addr_list);

	down_write(&hl_drivers_sem);
	list_add_tail(&hl->hl_list, &hl_drivers);
	up_write(&hl_drivers_sem);

	write_lock_irqsave(&hl_irqs_lock, flags);
	list_add_tail(&hl->irq_list, &hl_irqs);
	write_unlock_irqrestore(&hl_irqs_lock, flags);

	if (hl->add_host)
		nodemgr_for_each_host(hl, highlevel_for_each_host_reg);
	return;
}