#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct rpc_request_hdr {int /*<<< orphan*/  xid; int /*<<< orphan*/  procedure; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  accept_stat; } ;
struct TYPE_4__ {TYPE_1__ acc_hdr; } ;
struct rpc_reply_hdr {TYPE_2__ data; int /*<<< orphan*/  reply_stat; } ;
struct audmgr {int /*<<< orphan*/  wait; int /*<<< orphan*/ * task; int /*<<< orphan*/  ept; } ;

/* Variables and functions */
 scalar_t__ RPCMSG_REPLYSTAT_ACCEPTED ; 
 int RPC_COMMON_HDR_SZ ; 
 int RPC_REPLY_HDR_SZ ; 
 int RPC_REQUEST_HDR_SZ ; 
 scalar_t__ RPC_TYPE_REPLY ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rpc_request_hdr*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int msm_rpc_read (int /*<<< orphan*/ ,void**,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  process_rpc_request (scalar_t__,scalar_t__,void*,int,void*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audmgr_rpc_thread(void *data)
{
	struct audmgr *am = data;
	struct rpc_request_hdr *hdr = NULL;
	uint32_t type;
	int len;

	pr_info("audmgr_rpc_thread() start\n");

	while (!kthread_should_stop()) {
		if (hdr) {
			kfree(hdr);
			hdr = NULL;
		}
		len = msm_rpc_read(am->ept, (void **) &hdr, -1, -1);
		if (len < 0) {
			pr_err("audmgr: rpc read failed (%d)\n", len);
			break;
		}
		if (len < RPC_COMMON_HDR_SZ)
			continue;

		type = be32_to_cpu(hdr->type);
		if (type == RPC_TYPE_REPLY) {
			struct rpc_reply_hdr *rep = (void *) hdr;
			uint32_t status;
			if (len < RPC_REPLY_HDR_SZ)
				continue;
			status = be32_to_cpu(rep->reply_stat);
			if (status == RPCMSG_REPLYSTAT_ACCEPTED) {
				status = be32_to_cpu(rep->data.acc_hdr.accept_stat);
				pr_info("audmgr: rpc_reply status %d\n", status);
			} else {
				pr_info("audmgr: rpc_reply denied!\n");
			}
			/* process reply */
			continue;
		}

		if (len < RPC_REQUEST_HDR_SZ)
			continue;

		process_rpc_request(be32_to_cpu(hdr->procedure),
				    be32_to_cpu(hdr->xid),
				    (void *) (hdr + 1),
				    len - sizeof(*hdr),
				    data);
	}
	pr_info("audmgr_rpc_thread() exit\n");
	if (hdr) {
		kfree(hdr);
		hdr = NULL;
	}
	am->task = NULL;
	wake_up(&am->wait);
	return 0;
}