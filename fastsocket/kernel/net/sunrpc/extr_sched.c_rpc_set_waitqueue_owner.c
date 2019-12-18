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
struct rpc_wait_queue {int /*<<< orphan*/  nr; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_BATCH_COUNT ; 

__attribute__((used)) static void rpc_set_waitqueue_owner(struct rpc_wait_queue *queue, pid_t pid)
{
	queue->owner = pid;
	queue->nr = RPC_BATCH_COUNT;
}