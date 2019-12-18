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
struct nvme_queue {int dummy; } ;
struct nvme_cmd_info {void* ctx; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  nvme_completion_fn ;

/* Variables and functions */
 void* CMD_CTX_CANCELLED ; 
 struct nvme_cmd_info* nvme_cmd_info (struct nvme_queue*) ; 
 int /*<<< orphan*/  special_completion ; 

__attribute__((used)) static void *cancel_cmdid(struct nvme_queue *nvmeq, int cmdid,
						nvme_completion_fn *fn)
{
	void *ctx;
	struct nvme_cmd_info *info = nvme_cmd_info(nvmeq);
	if (fn)
		*fn = info[cmdid].fn;
	ctx = info[cmdid].ctx;
	info[cmdid].fn = special_completion;
	info[cmdid].ctx = CMD_CTX_CANCELLED;
	return ctx;
}