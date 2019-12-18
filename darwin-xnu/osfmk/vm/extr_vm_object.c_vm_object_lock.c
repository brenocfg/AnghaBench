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
struct TYPE_4__ {int /*<<< orphan*/  Lock_owner; int /*<<< orphan*/  Lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_pause (int) ; 
 int /*<<< orphan*/  scan_object_collision ; 
 TYPE_1__* vm_pageout_scan_wants_object ; 

void
vm_object_lock(vm_object_t object)
{
        if (object == vm_pageout_scan_wants_object) {
	        scan_object_collision++;
	        mutex_pause(2);
	}
        lck_rw_lock_exclusive(&object->Lock);
#if DEVELOPMENT || DEBUG
	object->Lock_owner = current_thread();
#endif
}