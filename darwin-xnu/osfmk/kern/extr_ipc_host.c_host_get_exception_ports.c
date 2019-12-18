#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* thread_state_flavor_array_t ;
typedef  unsigned int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_2__* host_priv_t ;
typedef  scalar_t__* exception_port_array_t ;
typedef  int exception_mask_t ;
typedef  int* exception_mask_array_t ;
typedef  scalar_t__* exception_behavior_array_t ;
struct TYPE_9__ {TYPE_1__* exc_actions; } ;
struct TYPE_8__ {scalar_t__ port; scalar_t__ behavior; scalar_t__ flavor; } ;

/* Variables and functions */
 int EXC_MASK_VALID ; 
 unsigned int EXC_TYPES_COUNT ; 
 unsigned int FIRST_EXCEPTION ; 
 TYPE_2__* HOST_PRIV_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  host_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  host_unlock (TYPE_2__*) ; 
 scalar_t__ ipc_port_copy_send (scalar_t__) ; 
 TYPE_2__ realhost ; 

kern_return_t
host_get_exception_ports(
	host_priv_t			host_priv,
	exception_mask_t                exception_mask,
	exception_mask_array_t		masks,
	mach_msg_type_number_t		* CountCnt,
	exception_port_array_t		ports,
	exception_behavior_array_t      behaviors,
	thread_state_flavor_array_t     flavors		)
{
	unsigned int	i, j, count;

	if (host_priv == HOST_PRIV_NULL)
		return KERN_INVALID_ARGUMENT;

	if (exception_mask & ~EXC_MASK_VALID) {
		return KERN_INVALID_ARGUMENT;
	}

	assert (host_priv == &realhost);

	host_lock(host_priv);

	count = 0;

	for (i = FIRST_EXCEPTION; i < EXC_TYPES_COUNT; i++) {
		if (exception_mask & (1 << i)) {
			for (j = 0; j < count; j++) {
/*
 *				search for an identical entry, if found
 *				set corresponding mask for this exception.
 */
				if (host_priv->exc_actions[i].port == ports[j] &&
					host_priv->exc_actions[i].behavior == behaviors[j]
				  && host_priv->exc_actions[i].flavor == flavors[j])
				{
					masks[j] |= (1 << i);
					break;
				}
			}/* for */
			if (j == count) {
				masks[j] = (1 << i);
				ports[j] =
				  ipc_port_copy_send(host_priv->exc_actions[i].port);
				behaviors[j] = host_priv->exc_actions[i].behavior;
				flavors[j] = host_priv->exc_actions[i].flavor;
				count++;
				if (count > *CountCnt) {
					break;
				}
			}
		}
	}/* for */
	host_unlock(host_priv);

	*CountCnt = count;
	return KERN_SUCCESS;
}