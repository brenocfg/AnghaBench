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
struct rpc_message {int dummy; } ;
struct rpc_clnt {int dummy; } ;

/* Variables and functions */
 int EJUKEBOX ; 
 int EKEYEXPIRED ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  NFS_JUKEBOX_RETRY_TIME ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freezable_schedule_timeout_killable (int /*<<< orphan*/ ) ; 
 int rpc_call_sync (struct rpc_clnt*,struct rpc_message*,int) ; 

__attribute__((used)) static int
nfs3_rpc_wrapper(struct rpc_clnt *clnt, struct rpc_message *msg, int flags)
{
	int res;
	do {
		res = rpc_call_sync(clnt, msg, flags);
		if (res != -EJUKEBOX && res != -EKEYEXPIRED)
			break;
		freezable_schedule_timeout_killable(NFS_JUKEBOX_RETRY_TIME);
		res = -ERESTARTSYS;
	} while (!fatal_signal_pending(current));
	return res;
}