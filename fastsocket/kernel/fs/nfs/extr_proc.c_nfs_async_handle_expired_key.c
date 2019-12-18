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
struct rpc_task {int /*<<< orphan*/  tk_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EKEYEXPIRED ; 
 int /*<<< orphan*/  NFS_JUKEBOX_RETRY_TIME ; 
 int /*<<< orphan*/  rpc_delay (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_restart_call (struct rpc_task*) ; 

__attribute__((used)) static int
nfs_async_handle_expired_key(struct rpc_task *task)
{
	if (task->tk_status != -EKEYEXPIRED)
		return 0;
	task->tk_status = 0;
	rpc_restart_call(task);
	rpc_delay(task, NFS_JUKEBOX_RETRY_TIME);
	return 1;
}