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
struct IO_APIC_route_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
union entry_union {int /*<<< orphan*/  w1; int /*<<< orphan*/  w2; struct IO_APIC_route_entry entry; TYPE_1__ member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_apic_write (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__ioapic_write_entry(int apic, int pin, struct IO_APIC_route_entry e)
{
	union entry_union eu = {{0, 0}};

	eu.entry = e;
	io_apic_write(apic, 0x11 + 2*pin, eu.w2);
	io_apic_write(apic, 0x10 + 2*pin, eu.w1);
}