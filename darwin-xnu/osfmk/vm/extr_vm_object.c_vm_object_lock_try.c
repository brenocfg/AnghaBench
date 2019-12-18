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
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  _vm_object_lock_try (int /*<<< orphan*/ ) ; 
 scalar_t__ get_preemption_level () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mutex_pause (int) ; 
 scalar_t__ vm_object_lock_avoid (int /*<<< orphan*/ ) ; 

boolean_t
vm_object_lock_try(vm_object_t object)
{
	/*
	 * Called from hibernate path so check before blocking.
	 */
	if (vm_object_lock_avoid(object) && ml_get_interrupts_enabled() && get_preemption_level()==0) {
		mutex_pause(2);
	}
	return _vm_object_lock_try(object);
}