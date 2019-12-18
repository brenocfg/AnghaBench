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
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {int uu_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int UT_CANCEL ; 
 int UT_CANCELDISABLE ; 
 int UT_CANCELED ; 
 int UT_NOTCANCELPT ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_abort_safely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_syscall_return (int /*<<< orphan*/ ) ; 

void
__pthread_testcancel(int presyscall)
{

	thread_t self = current_thread();
	struct uthread * uthread;

	uthread = (struct uthread *)get_bsdthread_info(self);

	
	uthread->uu_flag &= ~UT_NOTCANCELPT;

	if ((uthread->uu_flag & (UT_CANCELDISABLE | UT_CANCEL | UT_CANCELED)) == UT_CANCEL) {
		if(presyscall != 0) {
			unix_syscall_return(EINTR);
			/* NOTREACHED */
		} else 
			thread_abort_safely(self);
	}
}