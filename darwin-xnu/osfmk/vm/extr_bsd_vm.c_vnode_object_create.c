#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  struct vnode_pager* vnode_pager_t ;
struct TYPE_2__ {int /*<<< orphan*/  mo_control; int /*<<< orphan*/ * mo_pager_ops; int /*<<< orphan*/  mo_ikot; } ;
struct vnode_pager {int ref_count; struct vnode* vnode_handle; TYPE_1__ vn_pgr_hdr; } ;
struct vnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_MEMORY_OBJECT ; 
 int /*<<< orphan*/  MEMORY_OBJECT_CONTROL_NULL ; 
 struct vnode_pager* VNODE_PAGER_NULL ; 
 int /*<<< orphan*/  vnode_pager_ops ; 
 int /*<<< orphan*/  vnode_pager_zone ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

vnode_pager_t
vnode_object_create(
        struct vnode *vp)
{
	vnode_pager_t  vnode_object;

	vnode_object = (struct vnode_pager *) zalloc(vnode_pager_zone);
	if (vnode_object == VNODE_PAGER_NULL)
		return(VNODE_PAGER_NULL);

	/*
	 * The vm_map call takes both named entry ports and raw memory
	 * objects in the same parameter.  We need to make sure that
	 * vm_map does not see this object as a named entry port.  So,
	 * we reserve the first word in the object for a fake ip_kotype
	 * setting - that will tell vm_map to use it as a memory object.
	 */
	vnode_object->vn_pgr_hdr.mo_ikot = IKOT_MEMORY_OBJECT;
	vnode_object->vn_pgr_hdr.mo_pager_ops = &vnode_pager_ops;
	vnode_object->vn_pgr_hdr.mo_control = MEMORY_OBJECT_CONTROL_NULL;

	vnode_object->ref_count = 1;
	vnode_object->vnode_handle = vp;

	return(vnode_object);
}