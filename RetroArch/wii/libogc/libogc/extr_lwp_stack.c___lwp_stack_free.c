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
struct TYPE_3__ {int /*<<< orphan*/  stack; int /*<<< orphan*/  stack_allocated; } ;
typedef  TYPE_1__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_wkspace_free (int /*<<< orphan*/ ) ; 

void __lwp_stack_free(lwp_cntrl *thethread)
{
	if(!thethread->stack_allocated)
		return;

	__lwp_wkspace_free(thethread->stack);
}