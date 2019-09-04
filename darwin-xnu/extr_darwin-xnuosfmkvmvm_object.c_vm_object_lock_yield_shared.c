#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  Lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  lck_rw_lock_yield_shared (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock_assert_shared (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_lock_avoid (TYPE_1__*) ; 

boolean_t
vm_object_lock_yield_shared(vm_object_t object)
{
	boolean_t retval = FALSE, force_yield = FALSE;;

	vm_object_lock_assert_shared(object);

	force_yield = vm_object_lock_avoid(object);

	retval = lck_rw_lock_yield_shared(&object->Lock, force_yield);

	return (retval);
}