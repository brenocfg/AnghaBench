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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EJUKEBOX ; 
 int /*<<< orphan*/  EKEYEXPIRED ; 
 int /*<<< orphan*/  NFSIOS_DELAY ; 
 int /*<<< orphan*/  NFS_JUKEBOX_RETRY_TIME ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_delay (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_restart_call (struct rpc_task*) ; 

__attribute__((used)) static int
nfs3_async_handle_jukebox(struct rpc_task *task, struct inode *inode)
{
	if (task->tk_status != -EJUKEBOX && task->tk_status != -EKEYEXPIRED)
		return 0;
	if (task->tk_status == -EJUKEBOX)
		nfs_inc_stats(inode, NFSIOS_DELAY);
	task->tk_status = 0;
	rpc_restart_call(task);
	rpc_delay(task, NFS_JUKEBOX_RETRY_TIME);
	return 1;
}