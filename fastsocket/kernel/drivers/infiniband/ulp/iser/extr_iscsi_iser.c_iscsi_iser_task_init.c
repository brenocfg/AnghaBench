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
struct iscsi_task {int /*<<< orphan*/  sc; struct iscsi_iser_task* dd_data; } ;
struct iscsi_iser_task {scalar_t__ command_sent; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ iser_initialize_task_headers (struct iscsi_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iser_task_rdma_init (struct iscsi_iser_task*) ; 

__attribute__((used)) static int
iscsi_iser_task_init(struct iscsi_task *task)
{
	struct iscsi_iser_task *iser_task = task->dd_data;

	if (iser_initialize_task_headers(task, &iser_task->desc))
			return -ENOMEM;

	/* mgmt task */
	if (!task->sc)
		return 0;

	iser_task->command_sent = 0;
	iser_task_rdma_init(iser_task);
	return 0;
}