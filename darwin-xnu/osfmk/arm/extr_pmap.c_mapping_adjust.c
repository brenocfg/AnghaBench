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
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MAXPRI_KERNEL ; 
 scalar_t__ kernel_thread_start_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mapping_replenish ; 
 int /*<<< orphan*/  mapping_replenish_thread ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 

void mapping_adjust(void) {
	kern_return_t mres;

	mres = kernel_thread_start_priority((thread_continue_t)mapping_replenish, NULL, MAXPRI_KERNEL, &mapping_replenish_thread);
	if (mres != KERN_SUCCESS) {
		panic("pmap: mapping_replenish thread creation failed");
	}
	thread_deallocate(mapping_replenish_thread);
}