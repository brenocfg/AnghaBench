#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mach_msg_priority_t ;
typedef  TYPE_1__* ipc_kmsg_t ;
typedef  TYPE_2__* ipc_kmsg_queue_t ;
typedef  int boolean_t ;
struct TYPE_7__ {TYPE_1__* ikmq_base; } ;
struct TYPE_6__ {scalar_t__ ikm_qos_override; struct TYPE_6__* ikm_prev; struct TYPE_6__* ikm_next; } ;

/* Variables and functions */
 TYPE_1__* IKM_NULL ; 
 int TRUE ; 

boolean_t
ipc_kmsg_enqueue_qos(
	ipc_kmsg_queue_t	queue,
	ipc_kmsg_t		kmsg)
{
	ipc_kmsg_t first = queue->ikmq_base;
	ipc_kmsg_t prev;
	mach_msg_priority_t override;

	if (first == IKM_NULL) {
		/* insert a first message */
		queue->ikmq_base = kmsg;
		kmsg->ikm_next = kmsg;
		kmsg->ikm_prev = kmsg;
		return TRUE;
	}

	/* insert at the tail */
	prev = first->ikm_prev;
	kmsg->ikm_next = first;
	kmsg->ikm_prev = prev;
	first->ikm_prev = kmsg;
	prev->ikm_next = kmsg;

	/* apply QoS overrides towards the head */
	override = kmsg->ikm_qos_override;
	while (prev != kmsg &&
	       override > prev->ikm_qos_override) {
		prev->ikm_qos_override = override;
		prev = prev->ikm_prev;
	}

	/* did we adjust everything? */
	return (prev == kmsg);
}