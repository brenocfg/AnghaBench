#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_pager_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  TYPE_2__* memory_object_t ;
struct TYPE_7__ {int /*<<< orphan*/ * mo_pager_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  vnode_handle; } ;

/* Variables and functions */
 TYPE_1__* vnode_pager_lookup (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_pager_ops ; 
 int /*<<< orphan*/  vnode_pager_was_dirtied (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vnode_pager_dirtied(
	memory_object_t		mem_obj,
	vm_object_offset_t	s_offset,
	vm_object_offset_t	e_offset)
{
	vnode_pager_t	vnode_object;

	if (mem_obj && mem_obj->mo_pager_ops == &vnode_pager_ops) {

		vnode_object = vnode_pager_lookup(mem_obj);
		vnode_pager_was_dirtied(vnode_object->vnode_handle, s_offset, e_offset);
	}
}