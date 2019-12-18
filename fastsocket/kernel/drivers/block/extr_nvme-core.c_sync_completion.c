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
struct sync_cmd_info {int status; int /*<<< orphan*/  task; int /*<<< orphan*/  result; } ;
struct nvme_dev {int dummy; } ;
struct nvme_completion {int /*<<< orphan*/  status; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sync_completion(struct nvme_dev *dev, void *ctx,
						struct nvme_completion *cqe)
{
	struct sync_cmd_info *cmdinfo = ctx;
	cmdinfo->result = le32_to_cpup(&cqe->result);
	cmdinfo->status = le16_to_cpup(&cqe->status) >> 1;
	wake_up_process(cmdinfo->task);
}