#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  cvmx_cmd_queue_result_t ;
typedef  int /*<<< orphan*/  cvmx_cmd_queue_id_t ;
struct TYPE_5__ {int max_depth; int index; int pool_size_m1; int base_ptr_div128; int /*<<< orphan*/  fpa_pool; } ;
typedef  TYPE_1__ __cvmx_cmd_queue_state_t ;

/* Variables and functions */
 scalar_t__ CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH ; 
 int /*<<< orphan*/  CVMX_CMD_QUEUE_FULL ; 
 int /*<<< orphan*/  CVMX_CMD_QUEUE_NO_MEMORY ; 
 int /*<<< orphan*/  CVMX_CMD_QUEUE_SUCCESS ; 
 TYPE_1__* __cvmx_cmd_queue_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_cmd_queue_lock (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  __cvmx_cmd_queue_unlock (TYPE_1__*) ; 
 int cvmx_cmd_queue_length (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_fpa_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_phys_to_ptr (int) ; 
 int cvmx_ptr_to_phys (int*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline cvmx_cmd_queue_result_t cvmx_cmd_queue_write2(cvmx_cmd_queue_id_t
							    queue_id,
							    int use_locking,
							    uint64_t cmd1,
							    uint64_t cmd2)
{
	__cvmx_cmd_queue_state_t *qptr = __cvmx_cmd_queue_get_state(queue_id);

	/* Make sure nobody else is updating the same queue */
	if (likely(use_locking))
		__cvmx_cmd_queue_lock(queue_id, qptr);

	/*
	 * If a max queue length was specified then make sure we don't
	 * exceed it. If any part of the command would be below the
	 * limit we allow it.
	 */
	if (CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH && unlikely(qptr->max_depth)) {
		if (unlikely
		    (cvmx_cmd_queue_length(queue_id) > (int)qptr->max_depth)) {
			if (likely(use_locking))
				__cvmx_cmd_queue_unlock(qptr);
			return CVMX_CMD_QUEUE_FULL;
		}
	}

	/*
	 * Normally there is plenty of room in the current buffer for
	 * the command.
	 */
	if (likely(qptr->index + 2 < qptr->pool_size_m1)) {
		uint64_t *ptr =
		    (uint64_t *) cvmx_phys_to_ptr((uint64_t) qptr->
						  base_ptr_div128 << 7);
		ptr += qptr->index;
		qptr->index += 2;
		ptr[0] = cmd1;
		ptr[1] = cmd2;
	} else {
		uint64_t *ptr;
		/*
		 * Figure out how many command words will fit in this
		 * buffer. One location will be needed for the next
		 * buffer pointer.
		 */
		int count = qptr->pool_size_m1 - qptr->index;
		/*
		 * We need a new comamnd buffer. Fail if there isn't
		 * one available.
		 */
		uint64_t *new_buffer =
		    (uint64_t *) cvmx_fpa_alloc(qptr->fpa_pool);
		if (unlikely(new_buffer == NULL)) {
			if (likely(use_locking))
				__cvmx_cmd_queue_unlock(qptr);
			return CVMX_CMD_QUEUE_NO_MEMORY;
		}
		count--;
		ptr =
		    (uint64_t *) cvmx_phys_to_ptr((uint64_t) qptr->
						  base_ptr_div128 << 7);
		ptr += qptr->index;
		*ptr++ = cmd1;
		if (likely(count))
			*ptr++ = cmd2;
		*ptr = cvmx_ptr_to_phys(new_buffer);
		/*
		 * The current buffer is full and has a link to the
		 * next buffer. Time to write the rest of the commands
		 * into the new buffer.
		 */
		qptr->base_ptr_div128 = *ptr >> 7;
		qptr->index = 0;
		if (unlikely(count == 0)) {
			qptr->index = 1;
			new_buffer[0] = cmd2;
		}
	}

	/* All updates are complete. Release the lock and return */
	if (likely(use_locking))
		__cvmx_cmd_queue_unlock(qptr);
	return CVMX_CMD_QUEUE_SUCCESS;
}