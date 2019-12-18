#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/ * processor_set_t ;
typedef  TYPE_1__* policy_timeshare_limit_t ;
typedef  TYPE_2__* policy_timeshare_base_t ;
typedef  int policy_t ;
typedef  TYPE_3__* policy_rr_limit_t ;
typedef  TYPE_4__* policy_rr_base_t ;
typedef  int /*<<< orphan*/  policy_limit_t ;
typedef  TYPE_5__* policy_fifo_limit_t ;
typedef  TYPE_6__* policy_fifo_base_t ;
typedef  int /*<<< orphan*/  policy_base_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_12__ {int base_priority; } ;
struct TYPE_11__ {int max_priority; } ;
struct TYPE_10__ {int base_priority; } ;
struct TYPE_9__ {int max_priority; } ;
struct TYPE_8__ {int base_priority; } ;
struct TYPE_7__ {int max_priority; } ;

/* Variables and functions */
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_INVALID_POLICY ; 
 scalar_t__ KERN_SUCCESS ; 
#define  POLICY_FIFO 130 
 int /*<<< orphan*/  POLICY_FIFO_BASE_COUNT ; 
 int /*<<< orphan*/  POLICY_FIFO_LIMIT_COUNT ; 
#define  POLICY_RR 129 
 int /*<<< orphan*/  POLICY_RR_BASE_COUNT ; 
 int /*<<< orphan*/  POLICY_RR_LIMIT_COUNT ; 
#define  POLICY_TIMESHARE 128 
 int /*<<< orphan*/  POLICY_TIMESHARE_BASE_COUNT ; 
 int /*<<< orphan*/  POLICY_TIMESHARE_LIMIT_COUNT ; 
 int /*<<< orphan*/ * PROCESSOR_SET_NULL ; 
 scalar_t__ THREAD_NULL ; 
 scalar_t__ invalid_policy (int) ; 
 int /*<<< orphan*/  invalid_pri (int) ; 
 int /*<<< orphan*/  pset0 ; 
 scalar_t__ thread_set_mode_and_absolute_pri (scalar_t__,int,int) ; 

kern_return_t
thread_set_policy(
	thread_t				thread,
	processor_set_t			pset,
	policy_t				policy,
	policy_base_t			base,
	mach_msg_type_number_t	base_count,
	policy_limit_t			limit,
	mach_msg_type_number_t	limit_count)
{
	int 					max, bas;
	kern_return_t			result = KERN_SUCCESS;

	if (	thread == THREAD_NULL			||
			pset == PROCESSOR_SET_NULL || pset != &pset0)
		return (KERN_INVALID_ARGUMENT);

	if (invalid_policy(policy))
		return(KERN_INVALID_ARGUMENT);	

	switch (policy) {

	case POLICY_RR:
	{
		policy_rr_base_t		rr_base = (policy_rr_base_t) base;
		policy_rr_limit_t		rr_limit = (policy_rr_limit_t) limit;

		if (	base_count != POLICY_RR_BASE_COUNT		||
				limit_count != POLICY_RR_LIMIT_COUNT		) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		bas = rr_base->base_priority;
		max = rr_limit->max_priority;
		if (invalid_pri(bas) || invalid_pri(max)) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		break;
	}

	case POLICY_FIFO:
	{
		policy_fifo_base_t		fifo_base = (policy_fifo_base_t) base;
		policy_fifo_limit_t		fifo_limit = (policy_fifo_limit_t) limit;

		if (	base_count != POLICY_FIFO_BASE_COUNT	||
				limit_count != POLICY_FIFO_LIMIT_COUNT)		{
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		bas = fifo_base->base_priority;
		max = fifo_limit->max_priority;
		if (invalid_pri(bas) || invalid_pri(max)) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		break;
	}

	case POLICY_TIMESHARE:
	{
		policy_timeshare_base_t		ts_base = (policy_timeshare_base_t) base;
		policy_timeshare_limit_t	ts_limit =
						(policy_timeshare_limit_t) limit;

		if (	base_count != POLICY_TIMESHARE_BASE_COUNT		||
				limit_count != POLICY_TIMESHARE_LIMIT_COUNT			) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		bas = ts_base->base_priority;
		max = ts_limit->max_priority;
		if (invalid_pri(bas) || invalid_pri(max)) {
			result = KERN_INVALID_ARGUMENT;
			break;
		}

		break;
	}

	default:
		result = KERN_INVALID_POLICY;
	}

	if (result != KERN_SUCCESS) {
		return (result);
	}

	/* Note that we do not pass on max priority. */
	if (result == KERN_SUCCESS) {
	    result = thread_set_mode_and_absolute_pri(thread, policy, bas);
	}

	return (result);
}