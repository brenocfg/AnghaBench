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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  atm_value_t ;
typedef  scalar_t__ atm_task_descriptor_t ;
typedef  int /*<<< orphan*/  atm_guard_t ;

/* Variables and functions */
 scalar_t__ ATM_TASK_DESCRIPTOR_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_TASK ; 
 int /*<<< orphan*/  atm_listener_insert (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
atm_value_register(
	atm_value_t atm_value,
	atm_task_descriptor_t task_descriptor,
	atm_guard_t guard)
{
	kern_return_t kr;

	if (task_descriptor == ATM_TASK_DESCRIPTOR_NULL)
		return KERN_INVALID_TASK;

	kr = atm_listener_insert(atm_value, task_descriptor, guard);
	return kr;
}