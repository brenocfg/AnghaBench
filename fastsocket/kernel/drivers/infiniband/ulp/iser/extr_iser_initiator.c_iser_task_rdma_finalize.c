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
struct TYPE_4__ {scalar_t__ is_fmr; } ;
struct iser_regd_buf {TYPE_2__ reg; } ;
struct iscsi_iser_task {struct iser_regd_buf* rdma_regd; scalar_t__* dir; TYPE_1__* data_copy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * copy_buf; } ;

/* Variables and functions */
 size_t ISER_DIR_IN ; 
 size_t ISER_DIR_OUT ; 
 int /*<<< orphan*/  iser_dma_unmap_task_data (struct iscsi_iser_task*) ; 
 int /*<<< orphan*/  iser_finalize_rdma_unaligned_sg (struct iscsi_iser_task*,size_t) ; 
 int /*<<< orphan*/  iser_unreg_mem (TYPE_2__*) ; 

void iser_task_rdma_finalize(struct iscsi_iser_task *iser_task)
{
	int is_rdma_aligned = 1;
	struct iser_regd_buf *regd;

	/* if we were reading, copy back to unaligned sglist,
	 * anyway dma_unmap and free the copy
	 */
	if (iser_task->data_copy[ISER_DIR_IN].copy_buf != NULL) {
		is_rdma_aligned = 0;
		iser_finalize_rdma_unaligned_sg(iser_task, ISER_DIR_IN);
	}
	if (iser_task->data_copy[ISER_DIR_OUT].copy_buf != NULL) {
		is_rdma_aligned = 0;
		iser_finalize_rdma_unaligned_sg(iser_task, ISER_DIR_OUT);
	}

	if (iser_task->dir[ISER_DIR_IN]) {
		regd = &iser_task->rdma_regd[ISER_DIR_IN];
		if (regd->reg.is_fmr)
			iser_unreg_mem(&regd->reg);
	}

	if (iser_task->dir[ISER_DIR_OUT]) {
		regd = &iser_task->rdma_regd[ISER_DIR_OUT];
		if (regd->reg.is_fmr)
			iser_unreg_mem(&regd->reg);
	}

       /* if the data was unaligned, it was already unmapped and then copied */
       if (is_rdma_aligned)
		iser_dma_unmap_task_data(iser_task);
}