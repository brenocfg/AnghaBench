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
struct irq_work {struct irq_work* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WORK_FLAGS ; 
 unsigned long IRQ_WORK_PENDING ; 
 struct irq_work* cmpxchg (struct irq_work**,struct irq_work*,struct irq_work*) ; 
 struct irq_work* next_flags (struct irq_work*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool irq_work_claim(struct irq_work *entry)
{
	struct irq_work *next, *nflags;

	do {
		next = entry->next;
		if ((unsigned long)next & IRQ_WORK_PENDING)
			return false;
		nflags = next_flags(next, IRQ_WORK_FLAGS);
	} while (cmpxchg(&entry->next, next, nflags) != next);

	return true;
}