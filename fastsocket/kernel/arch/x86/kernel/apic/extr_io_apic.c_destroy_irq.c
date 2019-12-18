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
struct irq_cfg {int dummy; } ;
struct TYPE_2__ {struct irq_cfg* chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_irq_vector (unsigned int,struct irq_cfg*) ; 
 int /*<<< orphan*/  dynamic_irq_cleanup_keep_chip_data (unsigned int) ; 
 int /*<<< orphan*/  free_irte (unsigned int) ; 
 TYPE_1__* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vector_lock ; 

void destroy_irq(unsigned int irq)
{
	unsigned long flags;
	struct irq_cfg *cfg;

	dynamic_irq_cleanup_keep_chip_data(irq);

	free_irte(irq);
	spin_lock_irqsave(&vector_lock, flags);
	cfg = irq_to_desc(irq)->chip_data;
	__clear_irq_vector(irq, cfg);
	spin_unlock_irqrestore(&vector_lock, flags);
}