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
struct ocrdma_queue_info {int id; int created; int /*<<< orphan*/  dma; int /*<<< orphan*/  len; int /*<<< orphan*/  size; int /*<<< orphan*/  va; } ;
struct ocrdma_pa {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  netdev; } ;
struct ocrdma_dev {TYPE_1__ nic_info; struct ocrdma_create_mq_rsp* mbx_cmd; } ;
struct TYPE_4__ {int rsvd_version; } ;
struct ocrdma_create_mq_rsp {int cqid_pages; int async_cqid_ringsize; int id; struct ocrdma_pa* pa; int /*<<< orphan*/  valid; int /*<<< orphan*/  async_event_bitmap; int /*<<< orphan*/  async_cqid_valid; TYPE_2__ req; } ;
struct ocrdma_create_mq_req {int cqid_pages; int async_cqid_ringsize; int id; struct ocrdma_pa* pa; int /*<<< orphan*/  valid; int /*<<< orphan*/  async_event_bitmap; int /*<<< orphan*/  async_cqid_valid; TYPE_2__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  Bit (int) ; 
 int /*<<< orphan*/  OCRDMA_CMD_CREATE_MQ_EXT ; 
 int /*<<< orphan*/  OCRDMA_CREATE_MQ_ASYNC_CQ_VALID ; 
 int OCRDMA_CREATE_MQ_CQ_ID_SHIFT ; 
 int OCRDMA_CREATE_MQ_RING_SIZE_SHIFT ; 
 int /*<<< orphan*/  OCRDMA_CREATE_MQ_VALID ; 
 int /*<<< orphan*/  OCRDMA_SUBSYS_COMMON ; 
 int PAGES_4K_SPANNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE_4K ; 
 int be_roce_mcc_cmd (int /*<<< orphan*/ ,struct ocrdma_create_mq_rsp*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ocrdma_create_mq_rsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_build_q_pages (struct ocrdma_pa*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocrdma_encoded_q_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_init_mch (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocrdma_mbx_create_mq(struct ocrdma_dev *dev,
				struct ocrdma_queue_info *mq,
				struct ocrdma_queue_info *cq)
{
	int num_pages, status;
	struct ocrdma_create_mq_req *cmd = dev->mbx_cmd;
	struct ocrdma_create_mq_rsp *rsp = dev->mbx_cmd;
	struct ocrdma_pa *pa;

	memset(cmd, 0, sizeof(*cmd));
	num_pages = PAGES_4K_SPANNED(mq->va, mq->size);

	ocrdma_init_mch(&cmd->req, OCRDMA_CMD_CREATE_MQ_EXT,
			OCRDMA_SUBSYS_COMMON, sizeof(*cmd));
	cmd->req.rsvd_version = 1;
	cmd->cqid_pages = num_pages;
	cmd->cqid_pages |= (cq->id << OCRDMA_CREATE_MQ_CQ_ID_SHIFT);
	cmd->async_cqid_valid = OCRDMA_CREATE_MQ_ASYNC_CQ_VALID;
	cmd->async_event_bitmap = Bit(20);
	cmd->async_cqid_ringsize = cq->id;
	cmd->async_cqid_ringsize |= (ocrdma_encoded_q_len(mq->len) <<
				OCRDMA_CREATE_MQ_RING_SIZE_SHIFT);
	cmd->valid = OCRDMA_CREATE_MQ_VALID;
	pa = &cmd->pa[0];

	ocrdma_build_q_pages(pa, num_pages, mq->dma, PAGE_SIZE_4K);
	status = be_roce_mcc_cmd(dev->nic_info.netdev,
				 cmd, sizeof(*cmd), NULL, NULL);
	if (!status) {
		mq->id = rsp->id;
		mq->created = true;
	}
	return status;
}