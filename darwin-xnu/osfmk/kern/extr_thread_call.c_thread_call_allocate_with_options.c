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
typedef  TYPE_1__* thread_call_t ;
typedef  int thread_call_priority_t ;
typedef  int /*<<< orphan*/  thread_call_param_t ;
typedef  int thread_call_options_t ;
typedef  int /*<<< orphan*/  thread_call_func_t ;
struct TYPE_4__ {int tc_flags; int /*<<< orphan*/  tc_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_CALL_INDEX_HIGH ; 
 int /*<<< orphan*/  THREAD_CALL_INDEX_KERNEL ; 
 int /*<<< orphan*/  THREAD_CALL_INDEX_KERNEL_HIGH ; 
 int /*<<< orphan*/  THREAD_CALL_INDEX_LOW ; 
 int /*<<< orphan*/  THREAD_CALL_INDEX_USER ; 
 int THREAD_CALL_ONCE ; 
 int THREAD_CALL_OPTIONS_ONCE ; 
 int THREAD_CALL_OPTIONS_SIGNAL ; 
#define  THREAD_CALL_PRIORITY_HIGH 132 
#define  THREAD_CALL_PRIORITY_KERNEL 131 
#define  THREAD_CALL_PRIORITY_KERNEL_HIGH 130 
#define  THREAD_CALL_PRIORITY_LOW 129 
#define  THREAD_CALL_PRIORITY_USER 128 
 int THREAD_CALL_SIGNAL ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 TYPE_1__* thread_call_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

thread_call_t
thread_call_allocate_with_options(
		thread_call_func_t		func,
		thread_call_param_t		param0,
		thread_call_priority_t		pri,
		thread_call_options_t		options)
{
	thread_call_t call = thread_call_allocate(func, param0);

	switch (pri) {
		case THREAD_CALL_PRIORITY_HIGH:
			call->tc_index = THREAD_CALL_INDEX_HIGH;
			break;
		case THREAD_CALL_PRIORITY_KERNEL:
			call->tc_index = THREAD_CALL_INDEX_KERNEL;
			break;
		case THREAD_CALL_PRIORITY_USER:
			call->tc_index = THREAD_CALL_INDEX_USER;
			break;
		case THREAD_CALL_PRIORITY_LOW:
			call->tc_index = THREAD_CALL_INDEX_LOW;
			break;
		case THREAD_CALL_PRIORITY_KERNEL_HIGH:
			call->tc_index = THREAD_CALL_INDEX_KERNEL_HIGH;
			break;
		default:
			panic("Invalid thread call pri value: %d", pri);
			break;
	}

	if (options & THREAD_CALL_OPTIONS_ONCE) {
	    call->tc_flags |= THREAD_CALL_ONCE;
	}
	if (options & THREAD_CALL_OPTIONS_SIGNAL) {
	    call->tc_flags |= THREAD_CALL_SIGNAL | THREAD_CALL_ONCE;
	}

	return call;
}