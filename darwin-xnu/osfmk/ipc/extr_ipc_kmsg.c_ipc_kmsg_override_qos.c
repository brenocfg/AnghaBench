#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mach_msg_priority_t ;
typedef  TYPE_1__* ipc_kmsg_t ;
typedef  TYPE_2__* ipc_kmsg_queue_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {TYPE_1__* ikmq_base; } ;
struct TYPE_5__ {scalar_t__ ikm_qos_override; struct TYPE_5__* ikm_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
ipc_kmsg_override_qos(
	ipc_kmsg_queue_t	queue,
	ipc_kmsg_t          kmsg,
	mach_msg_priority_t override)
{
	ipc_kmsg_t first = queue->ikmq_base;
	ipc_kmsg_t cur = kmsg;

	/* apply QoS overrides towards the head */
	while (override > cur->ikm_qos_override) {
		cur->ikm_qos_override = override;
		if (cur == first)
			return TRUE;
		 cur = cur->ikm_prev;
	}
	return FALSE;
}