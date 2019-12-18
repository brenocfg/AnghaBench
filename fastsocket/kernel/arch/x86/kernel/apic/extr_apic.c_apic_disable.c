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
struct TYPE_2__ {void* eoi_write; void* write; int /*<<< orphan*/  read; } ;

/* Variables and functions */
 TYPE_1__* apic ; 
 int /*<<< orphan*/  native_apic_read_dummy ; 
 void* native_apic_write_dummy ; 

void apic_disable(void)
{
	apic->read = native_apic_read_dummy;
	apic->write = native_apic_write_dummy;
	apic->eoi_write = native_apic_write_dummy;
}