#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ipc_kmsg_t ;
typedef  int /*<<< orphan*/ * ipc_kmsg_queue_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  ith_messages; } ;

/* Variables and functions */
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  ipc_kmsg_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kmsg_queue_empty (int /*<<< orphan*/ *) ; 

boolean_t ipc_kmsg_delayed_destroy(
	ipc_kmsg_t kmsg)
{
	ipc_kmsg_queue_t queue = &(current_thread()->ith_messages);
	boolean_t first = ipc_kmsg_queue_empty(queue);

	ipc_kmsg_enqueue(queue, kmsg);
	return first;
}