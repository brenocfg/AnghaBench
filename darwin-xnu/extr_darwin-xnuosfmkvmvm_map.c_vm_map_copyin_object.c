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
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_size_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  TYPE_1__* vm_map_copy_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  cpy_object; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  VM_MAP_COPY_OBJECT ; 
 TYPE_1__* vm_map_copy_allocate () ; 

kern_return_t
vm_map_copyin_object(
	vm_object_t		object,
	vm_object_offset_t	offset,	/* offset of region in object */
	vm_object_size_t	size,	/* size of region in object */
	vm_map_copy_t	*copy_result)	/* OUT */
{
	vm_map_copy_t	copy;		/* Resulting copy */

	/*
	 *	We drop the object into a special copy object
	 *	that contains the object directly.
	 */

	copy = vm_map_copy_allocate();
	copy->type = VM_MAP_COPY_OBJECT;
	copy->cpy_object = object;
	copy->offset = offset;
	copy->size = size;

	*copy_result = copy;
	return(KERN_SUCCESS);
}