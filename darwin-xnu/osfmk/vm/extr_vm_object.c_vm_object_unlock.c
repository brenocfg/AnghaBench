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
struct TYPE_4__ {scalar_t__ Lock_owner; int /*<<< orphan*/  Lock; } ;

/* Variables and functions */
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 

void
vm_object_unlock(vm_object_t object)
{
#if DEVELOPMENT || DEBUG
	if (object->Lock_owner) {
		if (object->Lock_owner != current_thread())
			panic("vm_object_unlock: not owner - %p\n", object);
		object->Lock_owner = 0;
	}
#endif
	lck_rw_done(&object->Lock);
}