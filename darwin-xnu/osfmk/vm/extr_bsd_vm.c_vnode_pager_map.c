#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_pager_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  memory_object_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {int /*<<< orphan*/  vnode_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PAGER_ALL ; 
 int /*<<< orphan*/  PAGER_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ubc_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vnode_pager_lookup (int /*<<< orphan*/ ) ; 

kern_return_t
vnode_pager_map(
	memory_object_t		mem_obj,
	vm_prot_t		prot)
{
	vnode_pager_t		vnode_object;
	int			ret;
	kern_return_t		kr;

	PAGER_DEBUG(PAGER_ALL, ("vnode_pager_map: %p %x\n", mem_obj, prot));

	vnode_object = vnode_pager_lookup(mem_obj);

	ret = ubc_map(vnode_object->vnode_handle, prot);

	if (ret != 0) {
		kr = KERN_FAILURE;
	} else {
		kr = KERN_SUCCESS;
	}

	return kr;
}