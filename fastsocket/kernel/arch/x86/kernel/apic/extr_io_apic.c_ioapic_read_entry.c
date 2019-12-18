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
struct IO_APIC_route_entry {int dummy; } ;
union entry_union {struct IO_APIC_route_entry entry; void* w2; void* w1; } ;

/* Variables and functions */
 void* io_apic_read (int,int) ; 
 int /*<<< orphan*/  ioapic_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct IO_APIC_route_entry ioapic_read_entry(int apic, int pin)
{
	union entry_union eu;
	unsigned long flags;
	spin_lock_irqsave(&ioapic_lock, flags);
	eu.w1 = io_apic_read(apic, 0x10 + 2 * pin);
	eu.w2 = io_apic_read(apic, 0x11 + 2 * pin);
	spin_unlock_irqrestore(&ioapic_lock, flags);
	return eu.entry;
}