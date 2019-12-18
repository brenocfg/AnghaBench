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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int load_return_t ;
struct TYPE_3__ {scalar_t__ threadstate_sz; scalar_t__* threadstate; } ;
typedef  TYPE_1__ load_result_t ;

/* Variables and functions */
 int LOAD_BADMACHO ; 
 int LOAD_FAILURE ; 
 int LOAD_SUCCESS ; 
 scalar_t__* kalloc (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ os_add_and_mul_overflow (scalar_t__,int,int,scalar_t__*) ; 
 scalar_t__ os_sub_overflow (scalar_t__,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static
load_return_t
load_threadstate(
	thread_t	thread,
	uint32_t	*ts,
	uint32_t	total_size,
	load_result_t	*result
)
{
	uint32_t	size;
	int		flavor;
	uint32_t	thread_size;
	uint32_t        *local_ts = NULL;
	uint32_t        local_ts_size = 0;
	int		ret;

	(void)thread;

	if (total_size > 0) {
		local_ts_size = total_size;
		local_ts = kalloc(local_ts_size);
		if (local_ts == NULL) {
			return LOAD_FAILURE;
		}
		memcpy(local_ts, ts, local_ts_size);
		ts = local_ts;
	}

	/*
	 * Validate the new thread state; iterate through the state flavors in
	 * the Mach-O file.
	 * XXX: we should validate the machine state here, to avoid failing at
	 * activation time where we can't bail out cleanly.
	 */
	while (total_size > 0) {
		flavor = *ts++;
		size = *ts++;

		if (os_add_and_mul_overflow(size, 2, sizeof(uint32_t), &thread_size) ||
		    os_sub_overflow(total_size, thread_size, &total_size)) {
			ret = LOAD_BADMACHO;
			goto bad;
		}

		ts += size;	/* ts is a (uint32_t *) */
	}

	result->threadstate = local_ts;
	result->threadstate_sz = local_ts_size;
	return LOAD_SUCCESS;

bad:
	if (local_ts) {
		kfree(local_ts, local_ts_size);
	}
	return ret;
}