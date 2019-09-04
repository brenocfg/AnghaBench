#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ processor_set_t ;
typedef  scalar_t__ processor_set_info_t ;
typedef  TYPE_1__* processor_set_basic_info_t ;
typedef  TYPE_2__* policy_timeshare_limit_t ;
typedef  TYPE_3__* policy_timeshare_base_t ;
typedef  TYPE_4__* policy_rr_limit_t ;
typedef  TYPE_5__* policy_rr_base_t ;
typedef  TYPE_6__* policy_fifo_limit_t ;
typedef  TYPE_7__* policy_fifo_base_t ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/ * host_t ;
struct TYPE_14__ {void* base_priority; } ;
struct TYPE_13__ {void* max_priority; } ;
struct TYPE_12__ {int quantum; void* base_priority; } ;
struct TYPE_11__ {void* max_priority; } ;
struct TYPE_10__ {void* base_priority; } ;
struct TYPE_9__ {void* max_priority; } ;
struct TYPE_8__ {int default_policy; int /*<<< orphan*/  processor_count; } ;

/* Variables and functions */
 void* BASEPRI_DEFAULT ; 
 int /*<<< orphan*/ * HOST_NULL ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 void* MAXPRI_KERNEL ; 
 int POLICY_FIFO ; 
 scalar_t__ POLICY_FIFO_BASE_COUNT ; 
 scalar_t__ POLICY_FIFO_LIMIT_COUNT ; 
 int POLICY_RR ; 
 scalar_t__ POLICY_RR_BASE_COUNT ; 
 scalar_t__ POLICY_RR_LIMIT_COUNT ; 
 int POLICY_TIMESHARE ; 
 scalar_t__ POLICY_TIMESHARE_BASE_COUNT ; 
 scalar_t__ POLICY_TIMESHARE_LIMIT_COUNT ; 
 int PROCESSOR_SET_BASIC_INFO ; 
 scalar_t__ PROCESSOR_SET_BASIC_INFO_COUNT ; 
 int PROCESSOR_SET_ENABLED_POLICIES ; 
 int PROCESSOR_SET_FIFO_DEFAULT ; 
 int PROCESSOR_SET_FIFO_LIMITS ; 
 scalar_t__ PROCESSOR_SET_NULL ; 
 int PROCESSOR_SET_RR_DEFAULT ; 
 int PROCESSOR_SET_RR_LIMITS ; 
 int PROCESSOR_SET_TIMESHARE_DEFAULT ; 
 int PROCESSOR_SET_TIMESHARE_LIMITS ; 
 int /*<<< orphan*/  processor_avail_count ; 
 int /*<<< orphan*/  realhost ; 

kern_return_t
processor_set_info(
	processor_set_t		pset,
	int			flavor,
	host_t			*host,
	processor_set_info_t	info,
	mach_msg_type_number_t	*count)
{
	if (pset == PROCESSOR_SET_NULL)
		return(KERN_INVALID_ARGUMENT);

	if (flavor == PROCESSOR_SET_BASIC_INFO) {
		processor_set_basic_info_t	basic_info;

		if (*count < PROCESSOR_SET_BASIC_INFO_COUNT)
			return(KERN_FAILURE);

		basic_info = (processor_set_basic_info_t) info;
		basic_info->processor_count = processor_avail_count;
		basic_info->default_policy = POLICY_TIMESHARE;

		*count = PROCESSOR_SET_BASIC_INFO_COUNT;
		*host = &realhost;
		return(KERN_SUCCESS);
	}
	else if (flavor == PROCESSOR_SET_TIMESHARE_DEFAULT) {
		policy_timeshare_base_t	ts_base;

		if (*count < POLICY_TIMESHARE_BASE_COUNT)
			return(KERN_FAILURE);

		ts_base = (policy_timeshare_base_t) info;
		ts_base->base_priority = BASEPRI_DEFAULT;

		*count = POLICY_TIMESHARE_BASE_COUNT;
		*host = &realhost;
		return(KERN_SUCCESS);
	}
	else if (flavor == PROCESSOR_SET_FIFO_DEFAULT) {
		policy_fifo_base_t		fifo_base;

		if (*count < POLICY_FIFO_BASE_COUNT)
			return(KERN_FAILURE);

		fifo_base = (policy_fifo_base_t) info;
		fifo_base->base_priority = BASEPRI_DEFAULT;

		*count = POLICY_FIFO_BASE_COUNT;
		*host = &realhost;
		return(KERN_SUCCESS);
	}
	else if (flavor == PROCESSOR_SET_RR_DEFAULT) {
		policy_rr_base_t		rr_base;

		if (*count < POLICY_RR_BASE_COUNT)
			return(KERN_FAILURE);

		rr_base = (policy_rr_base_t) info;
		rr_base->base_priority = BASEPRI_DEFAULT;
		rr_base->quantum = 1;

		*count = POLICY_RR_BASE_COUNT;
		*host = &realhost;
		return(KERN_SUCCESS);
	}
	else if (flavor == PROCESSOR_SET_TIMESHARE_LIMITS) {
		policy_timeshare_limit_t	ts_limit;

		if (*count < POLICY_TIMESHARE_LIMIT_COUNT)
			return(KERN_FAILURE);

		ts_limit = (policy_timeshare_limit_t) info;
		ts_limit->max_priority = MAXPRI_KERNEL;

		*count = POLICY_TIMESHARE_LIMIT_COUNT;
		*host = &realhost;
		return(KERN_SUCCESS);
	}
	else if (flavor == PROCESSOR_SET_FIFO_LIMITS) {
		policy_fifo_limit_t		fifo_limit;

		if (*count < POLICY_FIFO_LIMIT_COUNT)
			return(KERN_FAILURE);

		fifo_limit = (policy_fifo_limit_t) info;
		fifo_limit->max_priority = MAXPRI_KERNEL;

		*count = POLICY_FIFO_LIMIT_COUNT;
		*host = &realhost;
		return(KERN_SUCCESS);
	}
	else if (flavor == PROCESSOR_SET_RR_LIMITS) {
		policy_rr_limit_t		rr_limit;

		if (*count < POLICY_RR_LIMIT_COUNT)
			return(KERN_FAILURE);

		rr_limit = (policy_rr_limit_t) info;
		rr_limit->max_priority = MAXPRI_KERNEL;

		*count = POLICY_RR_LIMIT_COUNT;
		*host = &realhost;
		return(KERN_SUCCESS);
	}
	else if (flavor == PROCESSOR_SET_ENABLED_POLICIES) {
		int				*enabled;

		if (*count < (sizeof(*enabled)/sizeof(int)))
			return(KERN_FAILURE);

		enabled = (int *) info;
		*enabled = POLICY_TIMESHARE | POLICY_RR | POLICY_FIFO;

		*count = sizeof(*enabled)/sizeof(int);
		*host = &realhost;
		return(KERN_SUCCESS);
	}


	*host = HOST_NULL;
	return(KERN_INVALID_ARGUMENT);
}