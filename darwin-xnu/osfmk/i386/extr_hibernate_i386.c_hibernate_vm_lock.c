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
struct TYPE_2__ {scalar_t__ cpu_hibernate; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_cpu_datap () ; 
 int /*<<< orphan*/  hibernate_vm_lock_queues () ; 
 int /*<<< orphan*/  hibernate_vm_locks_safe ; 

void
hibernate_vm_lock(void)
{
    if (current_cpu_datap()->cpu_hibernate) {
	hibernate_vm_lock_queues();
	hibernate_vm_locks_safe = TRUE;
    }
}