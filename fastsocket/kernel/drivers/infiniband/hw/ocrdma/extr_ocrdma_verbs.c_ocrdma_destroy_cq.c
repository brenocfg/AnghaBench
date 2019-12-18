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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  db_page_size; int /*<<< orphan*/  unmapped_db; } ;
struct ocrdma_dev {int /*<<< orphan*/ ** cq_tbl; TYPE_1__ nic_info; } ;
struct ocrdma_cq {size_t id; scalar_t__ ucontext; int /*<<< orphan*/  len; scalar_t__ pa; struct ocrdma_dev* dev; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 struct ocrdma_cq* get_ocrdma_cq (struct ib_cq*) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_cq*) ; 
 int /*<<< orphan*/  ocrdma_del_mmap (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocrdma_mbx_destroy_cq (struct ocrdma_dev*,struct ocrdma_cq*) ; 

int ocrdma_destroy_cq(struct ib_cq *ibcq)
{
	int status;
	struct ocrdma_cq *cq = get_ocrdma_cq(ibcq);
	struct ocrdma_dev *dev = cq->dev;

	status = ocrdma_mbx_destroy_cq(dev, cq);

	if (cq->ucontext) {
		ocrdma_del_mmap(cq->ucontext, (u64) cq->pa, cq->len);
		ocrdma_del_mmap(cq->ucontext, dev->nic_info.unmapped_db,
				dev->nic_info.db_page_size);
	}
	dev->cq_tbl[cq->id] = NULL;

	kfree(cq);
	return status;
}