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
struct nvme_queue {int q_depth; int /*<<< orphan*/  cmdid_data; } ;
struct nvme_cmd_info {unsigned int timeout; void* ctx; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  nvme_completion_fn ;

/* Variables and functions */
 int EBUSY ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 unsigned int jiffies ; 
 struct nvme_cmd_info* nvme_cmd_info (struct nvme_queue*) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_cmdid(struct nvme_queue *nvmeq, void *ctx,
				nvme_completion_fn handler, unsigned timeout)
{
	int depth = nvmeq->q_depth - 1;
	struct nvme_cmd_info *info = nvme_cmd_info(nvmeq);
	int cmdid;

	do {
		cmdid = find_first_zero_bit(nvmeq->cmdid_data, depth);
		if (cmdid >= depth)
			return -EBUSY;
	} while (test_and_set_bit(cmdid, nvmeq->cmdid_data));

	info[cmdid].fn = handler;
	info[cmdid].ctx = ctx;
	info[cmdid].timeout = jiffies + timeout;
	return cmdid;
}