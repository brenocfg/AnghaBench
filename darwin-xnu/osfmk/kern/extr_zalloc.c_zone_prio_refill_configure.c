#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* zone_t ;
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  zone_replenish_thread; int /*<<< orphan*/  async_prio_refill; int /*<<< orphan*/  prio_refill_watermark; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MAXPRI_KERNEL ; 
 int /*<<< orphan*/  OSMemoryBarrier () ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ kernel_thread_start_priority (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 scalar_t__ zone_replenish_thread ; 

void
zone_prio_refill_configure(zone_t z, vm_size_t low_water_mark) {
	z->prio_refill_watermark = low_water_mark;

	z->async_prio_refill = TRUE;
	OSMemoryBarrier();
	kern_return_t tres = kernel_thread_start_priority((thread_continue_t)zone_replenish_thread, z, MAXPRI_KERNEL, &z->zone_replenish_thread);

	if (tres != KERN_SUCCESS) {
		panic("zone_prio_refill_configure, thread create: 0x%x", tres);
	}

	thread_deallocate(z->zone_replenish_thread);
}