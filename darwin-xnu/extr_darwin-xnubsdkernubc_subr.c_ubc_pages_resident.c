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
typedef  TYPE_2__* vnode_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {TYPE_1__* v_ubcinfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  ui_control; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UBCINFOEXISTS (TYPE_2__*) ; 
 scalar_t__ memory_object_pages_resident (int /*<<< orphan*/ ,scalar_t__*) ; 

int
ubc_pages_resident(vnode_t vp)
{
	kern_return_t		kret;
	boolean_t			has_pages_resident;
	
	if (!UBCINFOEXISTS(vp))
		return (0);
			
	/*
	 * The following call may fail if an invalid ui_control is specified,
	 * or if there is no VM object associated with the control object.  In
	 * either case, reacting to it as if there were no pages resident will
	 * result in correct behavior.
	 */
	kret = memory_object_pages_resident(vp->v_ubcinfo->ui_control, &has_pages_resident);
	
	if (kret != KERN_SUCCESS)
		return (0);
		
	if (has_pages_resident == TRUE)
		return (1);
		
	return (0);
}