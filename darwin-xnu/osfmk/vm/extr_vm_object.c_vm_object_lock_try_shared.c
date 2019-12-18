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
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  Lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_rw_try_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_pause (int) ; 
 scalar_t__ vm_object_lock_avoid (TYPE_1__*) ; 

boolean_t
vm_object_lock_try_shared(vm_object_t object)
{
        if (vm_object_lock_avoid(object)) {
	        mutex_pause(2);
	}
	return (lck_rw_try_lock_shared(&object->Lock));
}