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
typedef  int /*<<< orphan*/  memory_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 unsigned int hw_atomic_add (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* vnode_pager_lookup (int /*<<< orphan*/ ) ; 

void
vnode_pager_reference(
	memory_object_t		mem_obj)
{	
	vnode_pager_t	vnode_object;
	unsigned int		new_ref_count;

	vnode_object = vnode_pager_lookup(mem_obj);
	new_ref_count = hw_atomic_add(&vnode_object->ref_count, 1);
	assert(new_ref_count > 1);
}