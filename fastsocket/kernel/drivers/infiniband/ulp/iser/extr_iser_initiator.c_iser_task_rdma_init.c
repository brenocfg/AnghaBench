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
struct iser_regd_buf {int dummy; } ;
struct iscsi_iser_task {int /*<<< orphan*/ * rdma_regd; TYPE_1__* data; scalar_t__* dir; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {scalar_t__ data_len; } ;

/* Variables and functions */
 size_t ISER_DIR_IN ; 
 size_t ISER_DIR_OUT ; 
 int /*<<< orphan*/  ISER_TASK_STATUS_INIT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void iser_task_rdma_init(struct iscsi_iser_task *iser_task)

{
	iser_task->status = ISER_TASK_STATUS_INIT;

	iser_task->dir[ISER_DIR_IN] = 0;
	iser_task->dir[ISER_DIR_OUT] = 0;

	iser_task->data[ISER_DIR_IN].data_len  = 0;
	iser_task->data[ISER_DIR_OUT].data_len = 0;

	memset(&iser_task->rdma_regd[ISER_DIR_IN], 0,
	       sizeof(struct iser_regd_buf));
	memset(&iser_task->rdma_regd[ISER_DIR_OUT], 0,
	       sizeof(struct iser_regd_buf));
}