#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_object_t ;
struct TYPE_5__ {scalar_t__ prev; scalar_t__ next; } ;
struct TYPE_6__ {TYPE_1__ cached_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_object_cache_lock_spin () ; 
 int /*<<< orphan*/  vm_object_cache_remove_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_cache_unlock () ; 

void
vm_object_cache_remove(
	vm_object_t	object)
{
	vm_object_cache_lock_spin();

	if (object->cached_list.next &&
	    object->cached_list.prev)
		vm_object_cache_remove_locked(object);

	vm_object_cache_unlock();
}