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
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ mach_msg_return_t ;
struct TYPE_3__ {scalar_t__ ith_state; int /*<<< orphan*/  (* ith_continuation ) (scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ MACH_PEEK_READY ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ mach_msg_receive_results (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void
mach_msg_receive_continue(void)
{
	mach_msg_return_t mr;
	thread_t self = current_thread();

	if (self->ith_state == MACH_PEEK_READY)
		mr = MACH_PEEK_READY;
	else
		mr = mach_msg_receive_results(NULL);
	(*self->ith_continuation)(mr);
}