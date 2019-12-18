#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int v_iocount; scalar_t__ v_usecount; int v_lflag; int /*<<< orphan*/ * v_data; } ;

/* Variables and functions */
 TYPE_1__* NULLVP ; 
 int VL_DEAD ; 
 int /*<<< orphan*/  VNASSERT (int,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vnode_create_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_1__**,int) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

int
vnode_initialize(uint32_t flavor, uint32_t size, void *data, vnode_t *vpp)
{
	if (*vpp == NULLVP) {
		panic("NULL vnode passed to vnode_initialize");
	}
#if DEVELOPMENT || DEBUG
	/*
	 * We lock to check that vnode is fit for unlocked use in
	 * vnode_create_internal.
	 */
	vnode_lock_spin(*vpp);
	VNASSERT(((*vpp)->v_iocount == 1), *vpp,
	    ("vnode_initialize : iocount not 1, is %d", (*vpp)->v_iocount));
	VNASSERT(((*vpp)->v_usecount == 0), *vpp,
	    ("vnode_initialize : usecount not 0, is %d", (*vpp)->v_usecount));
	VNASSERT(((*vpp)->v_lflag & VL_DEAD), *vpp,
	    ("vnode_initialize : v_lflag does not have VL_DEAD, is 0x%x",
	    (*vpp)->v_lflag));
	VNASSERT(((*vpp)->v_data == NULL), *vpp,
	    ("vnode_initialize : v_data not NULL"));
	vnode_unlock(*vpp);
#endif
	return (vnode_create_internal(flavor, size, data, vpp, 1));
}