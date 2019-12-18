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
typedef  int /*<<< orphan*/  mach_timespec_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_2__* clock_t ;
struct TYPE_6__ {TYPE_1__* cl_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* c_gettime ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_2__* CLOCK_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

kern_return_t
clock_get_time(
	clock_t			clock,
	mach_timespec_t	*cur_time)	/* OUT */
{
	if (clock == CLOCK_NULL)
		return (KERN_INVALID_ARGUMENT);
	return ((*clock->cl_ops->c_gettime)(cur_time));
}