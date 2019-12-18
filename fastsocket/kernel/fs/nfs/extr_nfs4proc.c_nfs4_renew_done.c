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
struct rpc_task {scalar_t__ tk_status; } ;
struct nfs_client {int /*<<< orphan*/  cl_res_state; } ;
struct nfs4_renewdata {unsigned long timestamp; struct nfs_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CS_RENEWD ; 
 int /*<<< orphan*/  do_renew_lease (struct nfs_client*,unsigned long) ; 
 int /*<<< orphan*/  nfs4_schedule_lease_recovery (struct nfs_client*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_renew_done(struct rpc_task *task, void *calldata)
{
	struct nfs4_renewdata *data = calldata;
	struct nfs_client *clp = data->client;
	unsigned long timestamp = data->timestamp;

	if (task->tk_status < 0) {
		/* Unless we're shutting down, schedule state recovery! */
		if (test_bit(NFS_CS_RENEWD, &clp->cl_res_state) != 0)
			nfs4_schedule_lease_recovery(clp);
		return;
	}
	do_renew_lease(clp, timestamp);
}