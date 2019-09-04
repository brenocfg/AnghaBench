#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_9__ {scalar_t__ is_sub_map; } ;
struct TYPE_8__ {struct TYPE_8__* shadow; } ;

/* Variables and functions */
 scalar_t__ VME_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 

__attribute__((used)) static int
vm_map_region_count_obj_refs(
        vm_map_entry_t    entry,
	vm_object_t       object)
{
        int ref_count;
	vm_object_t chk_obj;
	vm_object_t tmp_obj;

	if (VME_OBJECT(entry) == 0)
		return(0);

        if (entry->is_sub_map)
		return(0);
	else {
		ref_count = 0;

		chk_obj = VME_OBJECT(entry);
		vm_object_lock(chk_obj);

		while (chk_obj) {
			if (chk_obj == object)
				ref_count++;
			tmp_obj = chk_obj->shadow;
			if (tmp_obj)
				vm_object_lock(tmp_obj);
			vm_object_unlock(chk_obj);

			chk_obj = tmp_obj;
		}
	}
	return(ref_count);
}