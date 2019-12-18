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
struct nvme_queue {size_t sq_tail; size_t q_depth; int /*<<< orphan*/  q_db; struct nvme_command* sq_cmds; } ;
struct nvme_ns {int /*<<< orphan*/  ns_id; } ;
struct TYPE_2__ {int command_id; int /*<<< orphan*/  nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_cmd_flush ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_submit_flush(struct nvme_queue *nvmeq, struct nvme_ns *ns,
								int cmdid)
{
	struct nvme_command *cmnd = &nvmeq->sq_cmds[nvmeq->sq_tail];

	memset(cmnd, 0, sizeof(*cmnd));
	cmnd->common.opcode = nvme_cmd_flush;
	cmnd->common.command_id = cmdid;
	cmnd->common.nsid = cpu_to_le32(ns->ns_id);

	if (++nvmeq->sq_tail == nvmeq->q_depth)
		nvmeq->sq_tail = 0;
	writel(nvmeq->sq_tail, nvmeq->q_db);

	return 0;
}