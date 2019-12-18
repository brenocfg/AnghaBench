#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_2__* clock_t ;
typedef  int /*<<< orphan*/  clock_flavor_t ;
typedef  int /*<<< orphan*/  clock_attr_t ;
struct TYPE_6__ {TYPE_1__* cl_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* c_getattr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_2__* CLOCK_NULL ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
clock_get_attributes(
	clock_t					clock,
	clock_flavor_t			flavor,
	clock_attr_t			attr,		/* OUT */
	mach_msg_type_number_t	*count)		/* IN/OUT */
{
	if (clock == CLOCK_NULL)
		return (KERN_INVALID_ARGUMENT);
	if (clock->cl_ops->c_getattr)
		return (clock->cl_ops->c_getattr(flavor, attr, count));
	return (KERN_FAILURE);
}