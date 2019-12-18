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
struct TYPE_2__ {scalar_t__ tsk; } ;

/* Variables and functions */
 scalar_t__ current ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 scalar_t__ invalid_vm86_irq (int) ; 
 int irqbits ; 
 int /*<<< orphan*/  irqbits_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* vm86_irqs ; 

__attribute__((used)) static inline int get_and_reset_irq(int irqnumber)
{
	int bit;
	unsigned long flags;
	int ret = 0;

	if (invalid_vm86_irq(irqnumber)) return 0;
	if (vm86_irqs[irqnumber].tsk != current) return 0;
	spin_lock_irqsave(&irqbits_lock, flags);
	bit = irqbits & (1 << irqnumber);
	irqbits &= ~bit;
	if (bit) {
		enable_irq(irqnumber);
		ret = 1;
	}

	spin_unlock_irqrestore(&irqbits_lock, flags);
	return ret;
}