#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vnode {int dummy; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  memory_object_offset_t ;
typedef  scalar_t__ memory_object_control_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ MEMORY_OBJECT_CONTROL_NULL ; 
 int /*<<< orphan*/  UBC_FLAGS_NONE ; 
 int /*<<< orphan*/  memory_object_range_op (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ ubc_getobject (struct vnode*,int /*<<< orphan*/ ) ; 

kern_return_t
ubc_range_op(
	struct vnode 	*vp,
	off_t		f_offset_beg,
	off_t		f_offset_end,
	int             ops,
	int             *range)
{
	memory_object_control_t		control;

	control = ubc_getobject(vp, UBC_FLAGS_NONE);
	if (control == MEMORY_OBJECT_CONTROL_NULL)
		return KERN_INVALID_ARGUMENT;

	return (memory_object_range_op(control,
				      (memory_object_offset_t)f_offset_beg,
				      (memory_object_offset_t)f_offset_end,
				      ops,
				      range));
}