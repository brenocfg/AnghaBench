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
typedef  int uint32_t ;
typedef  TYPE_2__* memory_object_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_7__ {int /*<<< orphan*/ * mo_pager_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  vnode_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int vnode_pager_isinuse (int /*<<< orphan*/ ) ; 
 TYPE_1__* vnode_pager_lookup (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_pager_ops ; 

kern_return_t
vnode_pager_get_isinuse(
	memory_object_t		mem_obj,
	uint32_t		*isinuse)
{
	vnode_pager_t	vnode_object;

	if (mem_obj->mo_pager_ops != &vnode_pager_ops) {
		*isinuse = 1;
		return KERN_INVALID_ARGUMENT;
	}

	vnode_object = vnode_pager_lookup(mem_obj);

	*isinuse = vnode_pager_isinuse(vnode_object->vnode_handle);
	return KERN_SUCCESS;
}