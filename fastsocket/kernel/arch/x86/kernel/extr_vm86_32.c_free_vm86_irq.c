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
struct TYPE_2__ {int /*<<< orphan*/ * tsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ *) ; 
 int irqbits ; 
 int /*<<< orphan*/  irqbits_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* vm86_irqs ; 

__attribute__((used)) static inline void free_vm86_irq(int irqnumber)
{
	unsigned long flags;

	free_irq(irqnumber, NULL);
	vm86_irqs[irqnumber].tsk = NULL;

	spin_lock_irqsave(&irqbits_lock, flags);
	irqbits &= ~(1 << irqnumber);
	spin_unlock_irqrestore(&irqbits_lock, flags);
}