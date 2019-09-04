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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ABORTED ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_OPERATION_TIMED_OUT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  KERN_TERMINATED ; 
#define  THREAD_AWAKENED 131 
#define  THREAD_INTERRUPTED 130 
#define  THREAD_RESTART 129 
#define  THREAD_TIMED_OUT 128 
 int /*<<< orphan*/  panic (char*) ; 

kern_return_t
semaphore_convert_wait_result(int wait_result)
{
	switch (wait_result) {
	case THREAD_AWAKENED:
		return KERN_SUCCESS;

	case THREAD_TIMED_OUT:
		return KERN_OPERATION_TIMED_OUT;
		
	case THREAD_INTERRUPTED:
		return KERN_ABORTED;

	case THREAD_RESTART:
		return KERN_TERMINATED;

	default:
		panic("semaphore_block\n");
		return KERN_FAILURE;
	}
}