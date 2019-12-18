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
struct irq_info {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IRQT_UNBOUND ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int* evtchn_to_irq ; 
 struct irq_info* info_for_irq (int) ; 
 int /*<<< orphan*/ * irq_info ; 
 int /*<<< orphan*/  irq_mapping_update_lock ; 
 int /*<<< orphan*/  irq_set_affinity (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_evtchn_info (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void rebind_evtchn_irq(int evtchn, int irq)
{
	struct irq_info *info = info_for_irq(irq);

	/* Make sure the irq is masked, since the new event channel
	   will also be masked. */
	disable_irq(irq);

	mutex_lock(&irq_mapping_update_lock);

	/* After resume the irq<->evtchn mappings are all cleared out */
	BUG_ON(evtchn_to_irq[evtchn] != -1);
	/* Expect irq to have been bound before,
	   so there should be a proper type */
	BUG_ON(info->type == IRQT_UNBOUND);

	evtchn_to_irq[evtchn] = irq;
	irq_info[irq] = mk_evtchn_info(evtchn);

	mutex_unlock(&irq_mapping_update_lock);

	/* new event channels are always bound to cpu 0 */
	irq_set_affinity(irq, cpumask_of(0));

	/* Unmask the event channel. */
	enable_irq(irq);
}