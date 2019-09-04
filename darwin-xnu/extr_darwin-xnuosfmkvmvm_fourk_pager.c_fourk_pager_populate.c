#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  int /*<<< orphan*/  memory_object_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_3__* fourk_pager_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {scalar_t__ mo_control; } ;
struct TYPE_7__ {scalar_t__ ref_count; TYPE_2__* slots; TYPE_1__ fourk_pgr_hdr; } ;
struct TYPE_6__ {scalar_t__ backing_object; scalar_t__ backing_offset; } ;

/* Variables and functions */
 int FOURK_PAGER_SLOTS ; 
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MEMORY_OBJECT_CONTROL_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* fourk_pager_lookup (int /*<<< orphan*/ ) ; 

kern_return_t
fourk_pager_populate(
	memory_object_t		mem_obj,
	boolean_t		overwrite,
	int			index,
	vm_object_t		new_backing_object,
	vm_object_offset_t	new_backing_offset,
	vm_object_t		*old_backing_object,
	vm_object_offset_t	*old_backing_offset)
{
	fourk_pager_t	pager;

	pager = fourk_pager_lookup(mem_obj);
	if (pager == NULL) {
		return KERN_INVALID_ARGUMENT;
	}

	assert(pager->ref_count > 0);
	assert(pager->fourk_pgr_hdr.mo_control != MEMORY_OBJECT_CONTROL_NULL);

	if (index < 0 || index > FOURK_PAGER_SLOTS) {
		return KERN_INVALID_ARGUMENT;
	}

	if (!overwrite &&
	    (pager->slots[index].backing_object != (vm_object_t) -1 ||
	     pager->slots[index].backing_offset != (vm_object_offset_t) -1)) {
		return KERN_INVALID_ADDRESS;
	}

	*old_backing_object = pager->slots[index].backing_object;
	*old_backing_offset = pager->slots[index].backing_offset;

	pager->slots[index].backing_object = new_backing_object;
	pager->slots[index].backing_offset = new_backing_offset;

	return KERN_SUCCESS;
}