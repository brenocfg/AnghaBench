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
struct comedi_subdevice {unsigned int runflags; int /*<<< orphan*/  spin_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void comedi_set_subdevice_runflags(struct comedi_subdevice *s, unsigned mask,
				   unsigned bits)
{
	unsigned long flags;

	spin_lock_irqsave(&s->spin_lock, flags);
	s->runflags &= ~mask;
	s->runflags |= (bits & mask);
	spin_unlock_irqrestore(&s->spin_lock, flags);
}