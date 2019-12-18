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
typedef  int u16 ;
struct ssb_device {struct ssb_bus* bus; } ;
struct ssb_bus {int mmio; int /*<<< orphan*/  bar_lock; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int readw (int) ; 
 int select_core_and_segment (struct ssb_device*,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u16 ssb_pcmcia_read16(struct ssb_device *dev, u16 offset)
{
	struct ssb_bus *bus = dev->bus;
	unsigned long flags;
	int err;
	u16 value = 0xFFFF;

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = select_core_and_segment(dev, &offset);
	if (likely(!err))
		value = readw(bus->mmio + offset);
	spin_unlock_irqrestore(&bus->bar_lock, flags);

	return value;
}