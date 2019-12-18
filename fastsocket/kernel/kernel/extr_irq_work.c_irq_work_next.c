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
struct irq_work {scalar_t__ next; } ;

/* Variables and functions */
 unsigned long IRQ_WORK_FLAGS ; 

__attribute__((used)) static inline struct irq_work *irq_work_next(struct irq_work *entry)
{
	unsigned long next = (unsigned long)entry->next;
	next &= ~IRQ_WORK_FLAGS;
	return (struct irq_work *)next;
}