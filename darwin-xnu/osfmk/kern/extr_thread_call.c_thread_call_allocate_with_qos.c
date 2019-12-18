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
typedef  int /*<<< orphan*/  thread_call_param_t ;
typedef  int thread_call_options_t ;
typedef  int /*<<< orphan*/  thread_call_func_t ;
struct TYPE_4__ {int /*<<< orphan*/  tc_flags; int /*<<< orphan*/  tc_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_CALL_INDEX_HIGH ; 
 int /*<<< orphan*/  THREAD_CALL_INDEX_LOW ; 
 int /*<<< orphan*/  THREAD_CALL_INDEX_QOS_IN ; 
 int /*<<< orphan*/  THREAD_CALL_INDEX_QOS_UI ; 
 int /*<<< orphan*/  THREAD_CALL_INDEX_QOS_UT ; 
 int /*<<< orphan*/  THREAD_CALL_INDEX_USER ; 
 int /*<<< orphan*/  THREAD_CALL_ONCE ; 
 int THREAD_CALL_OPTIONS_ONCE ; 
#define  THREAD_QOS_BACKGROUND 134 
#define  THREAD_QOS_LEGACY 133 
#define  THREAD_QOS_MAINTENANCE 132 
#define  THREAD_QOS_UNSPECIFIED 131 
#define  THREAD_QOS_USER_INITIATED 130 
#define  THREAD_QOS_USER_INTERACTIVE 129 
#define  THREAD_QOS_UTILITY 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 TYPE_1__* thread_call_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

thread_call_t
thread_call_allocate_with_qos(thread_call_func_t        func,
                              thread_call_param_t       param0,
                              int                       qos_tier,
                              thread_call_options_t     options)
{
	thread_call_t call = thread_call_allocate(func, param0);

	switch (qos_tier) {
		case THREAD_QOS_UNSPECIFIED:
			call->tc_index = THREAD_CALL_INDEX_HIGH;
			break;
		case THREAD_QOS_LEGACY:
			call->tc_index = THREAD_CALL_INDEX_USER;
			break;
		case THREAD_QOS_MAINTENANCE:
		case THREAD_QOS_BACKGROUND:
			call->tc_index = THREAD_CALL_INDEX_LOW;
			break;
		case THREAD_QOS_UTILITY:
			call->tc_index = THREAD_CALL_INDEX_QOS_UT;
			break;
		case THREAD_QOS_USER_INITIATED:
			call->tc_index = THREAD_CALL_INDEX_QOS_IN;
			break;
		case THREAD_QOS_USER_INTERACTIVE:
			call->tc_index = THREAD_CALL_INDEX_QOS_UI;
			break;
		default:
			panic("Invalid thread call qos value: %d", qos_tier);
			break;
	}

	if (options & THREAD_CALL_OPTIONS_ONCE)
		call->tc_flags |= THREAD_CALL_ONCE;

	/* does not support THREAD_CALL_OPTIONS_SIGNAL */

	return call;
}