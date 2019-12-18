#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ipc_kmsg_t ;
typedef  int /*<<< orphan*/  ipc_kmsg_queue_t ;

/* Variables and functions */
 scalar_t__ IKM_NULL ; 
 scalar_t__ ipc_kmsg_queue_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kmsg_rmqueue (int /*<<< orphan*/ ,scalar_t__) ; 

ipc_kmsg_t
ipc_kmsg_dequeue(
	ipc_kmsg_queue_t	queue)
{
	ipc_kmsg_t first;

	first = ipc_kmsg_queue_first(queue);

	if (first != IKM_NULL)
		ipc_kmsg_rmqueue(queue, first);

	return first;
}