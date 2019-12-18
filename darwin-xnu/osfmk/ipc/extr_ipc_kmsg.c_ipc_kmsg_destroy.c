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
typedef  int /*<<< orphan*/  ipc_kmsg_t ;

/* Variables and functions */
 scalar_t__ ipc_kmsg_delayed_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kmsg_reap_delayed () ; 

void
ipc_kmsg_destroy(
	ipc_kmsg_t	kmsg)
{
	/*
	 *	Destroying a message can cause more messages to be destroyed.
	 *	Curtail recursion by putting messages on the deferred
	 *	destruction queue.  If this was the first message on the
	 *	queue, this instance must process the full queue.
	 */
	if (ipc_kmsg_delayed_destroy(kmsg))
		ipc_kmsg_reap_delayed();
}