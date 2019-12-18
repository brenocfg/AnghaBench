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
struct TYPE_2__ {int /*<<< orphan*/  ith_messages; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKM_NULL ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  ipc_kmsg_clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kmsg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kmsg_queue_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_kmsg_rmqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ipc_kmsg_reap_delayed(void)
{
	ipc_kmsg_queue_t queue = &(current_thread()->ith_messages);
	ipc_kmsg_t kmsg;

	/*
	 * must leave kmsg in queue while cleaning it to assure
	 * no nested calls recurse into here.
	 */
	while ((kmsg = ipc_kmsg_queue_first(queue)) != IKM_NULL) {
		ipc_kmsg_clean(kmsg);
		ipc_kmsg_rmqueue(queue, kmsg);
		ipc_kmsg_free(kmsg);
	}
}