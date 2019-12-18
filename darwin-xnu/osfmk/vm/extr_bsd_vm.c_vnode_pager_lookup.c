#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_pager_t ;
typedef  scalar_t__ memory_object_t ;
struct TYPE_4__ {int /*<<< orphan*/ * mo_pager_ops; } ;
struct TYPE_5__ {TYPE_1__ vn_pgr_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vnode_pager_ops ; 

vnode_pager_t
vnode_pager_lookup(
	memory_object_t	 name)
{
	vnode_pager_t	vnode_object;

	vnode_object = (vnode_pager_t)name;
	assert(vnode_object->vn_pgr_hdr.mo_pager_ops == &vnode_pager_ops);
	return (vnode_object);
}