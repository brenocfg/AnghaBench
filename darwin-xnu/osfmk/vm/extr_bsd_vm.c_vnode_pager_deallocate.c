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
typedef  TYPE_1__* vnode_pager_t ;
typedef  int /*<<< orphan*/  memory_object_t ;
struct TYPE_4__ {int /*<<< orphan*/ * vnode_handle; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGER_ALL ; 
 int /*<<< orphan*/  PAGER_DEBUG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hw_atomic_sub (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* vnode_pager_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_pager_vrele (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_pager_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
vnode_pager_deallocate(
	memory_object_t		mem_obj)
{
	vnode_pager_t	vnode_object;

	PAGER_DEBUG(PAGER_ALL, ("vnode_pager_deallocate: %p\n", mem_obj));

	vnode_object = vnode_pager_lookup(mem_obj);

	if (hw_atomic_sub(&vnode_object->ref_count, 1) == 0) {
		if (vnode_object->vnode_handle != NULL) {
			vnode_pager_vrele(vnode_object->vnode_handle);
		}
		zfree(vnode_pager_zone, vnode_object);
	}
	return;
}