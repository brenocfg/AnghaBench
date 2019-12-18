#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  scalar_t__* thread_state_flavor_array_t ;
typedef  unsigned int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__* exception_port_array_t ;
typedef  int exception_mask_t ;
typedef  int* exception_mask_array_t ;
typedef  scalar_t__* exception_behavior_array_t ;
struct TYPE_8__ {TYPE_1__* exc_actions; int /*<<< orphan*/  active; } ;
struct TYPE_7__ {scalar_t__ port; scalar_t__ behavior; scalar_t__ flavor; } ;

/* Variables and functions */
 int EXC_MASK_VALID ; 
 unsigned int EXC_TYPES_COUNT ; 
 unsigned int FIRST_EXCEPTION ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_2__* THREAD_NULL ; 
 scalar_t__ ipc_port_copy_send (scalar_t__) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_2__*) ; 

kern_return_t
thread_get_exception_ports(
	thread_t					thread,
	exception_mask_t			exception_mask,
	exception_mask_array_t		masks,
	mach_msg_type_number_t		*CountCnt,
	exception_port_array_t		ports,
	exception_behavior_array_t	behaviors,
	thread_state_flavor_array_t	flavors)
{
	unsigned int	i, j, count;

	if (thread == THREAD_NULL)
		return (KERN_INVALID_ARGUMENT);

	if (exception_mask & ~EXC_MASK_VALID)
		return (KERN_INVALID_ARGUMENT);

	thread_mtx_lock(thread);

	if (!thread->active) {
		thread_mtx_unlock(thread);

		return (KERN_FAILURE);
	}

	count = 0;

	if (thread->exc_actions == NULL) {
		goto done;
	}

	for (i = FIRST_EXCEPTION; i < EXC_TYPES_COUNT; ++i) {
		if (exception_mask & (1 << i)) {
			for (j = 0; j < count; ++j) {
				/*
				 * search for an identical entry, if found
				 * set corresponding mask for this exception.
				 */
				if (	thread->exc_actions[i].port == ports[j]			&&
						thread->exc_actions[i].behavior ==behaviors[j]	&&
						thread->exc_actions[i].flavor == flavors[j]		) {
					masks[j] |= (1 << i);
					break;
				}
			}

			if (j == count) {
				masks[j] = (1 << i);
				ports[j] = ipc_port_copy_send(thread->exc_actions[i].port);
				behaviors[j] = thread->exc_actions[i].behavior;
				flavors[j] = thread->exc_actions[i].flavor;
				++count;
				if (count >= *CountCnt)
					break;
			}
		}
	}

done:
	thread_mtx_unlock(thread);

	*CountCnt = count;

	return (KERN_SUCCESS);
}