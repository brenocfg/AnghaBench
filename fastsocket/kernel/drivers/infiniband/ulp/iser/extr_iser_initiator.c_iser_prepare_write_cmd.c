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
struct TYPE_3__ {int /*<<< orphan*/  lkey; scalar_t__ va; int /*<<< orphan*/  rkey; } ;
struct iser_regd_buf {TYPE_1__ reg; } ;
struct iser_hdr {int /*<<< orphan*/  write_va; int /*<<< orphan*/  write_stag; int /*<<< orphan*/  flags; } ;
struct iser_data_buf {unsigned int data_len; } ;
struct iscsi_task {int /*<<< orphan*/  itt; int /*<<< orphan*/  conn; struct iscsi_iser_task* dd_data; } ;
struct TYPE_4__ {int num_sge; struct ib_sge* tx_sg; struct iser_hdr iser_header; } ;
struct iscsi_iser_task {TYPE_2__ desc; struct iser_regd_buf* rdma_regd; struct iser_data_buf* data; } ;
struct ib_sge {unsigned int length; int /*<<< orphan*/  lkey; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 size_t ISER_DIR_OUT ; 
 int /*<<< orphan*/  ISER_WSV ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ ,unsigned int,...) ; 
 int iser_dma_map_task_data (struct iscsi_iser_task*,struct iser_data_buf*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_err (char*,...) ; 
 int iser_reg_rdma_mem (struct iscsi_iser_task*,size_t) ; 

__attribute__((used)) static int
iser_prepare_write_cmd(struct iscsi_task *task,
		       unsigned int imm_sz,
		       unsigned int unsol_sz,
		       unsigned int edtl)
{
	struct iscsi_iser_task *iser_task = task->dd_data;
	struct iser_regd_buf *regd_buf;
	int err;
	struct iser_hdr *hdr = &iser_task->desc.iser_header;
	struct iser_data_buf *buf_out = &iser_task->data[ISER_DIR_OUT];
	struct ib_sge *tx_dsg = &iser_task->desc.tx_sg[1];

	err = iser_dma_map_task_data(iser_task,
				     buf_out,
				     ISER_DIR_OUT,
				     DMA_TO_DEVICE);
	if (err)
		return err;

	if (edtl > iser_task->data[ISER_DIR_OUT].data_len) {
		iser_err("Total data length: %ld, less than EDTL: %d, "
			 "in WRITE cmd BHS itt: %d, conn: 0x%p\n",
			 iser_task->data[ISER_DIR_OUT].data_len,
			 edtl, task->itt, task->conn);
		return -EINVAL;
	}

	err = iser_reg_rdma_mem(iser_task,ISER_DIR_OUT);
	if (err != 0) {
		iser_err("Failed to register write cmd RDMA mem\n");
		return err;
	}

	regd_buf = &iser_task->rdma_regd[ISER_DIR_OUT];

	if (unsol_sz < edtl) {
		hdr->flags     |= ISER_WSV;
		hdr->write_stag = cpu_to_be32(regd_buf->reg.rkey);
		hdr->write_va   = cpu_to_be64(regd_buf->reg.va + unsol_sz);

		iser_dbg("Cmd itt:%d, WRITE tags, RKEY:%#.4X "
			 "VA:%#llX + unsol:%d\n",
			 task->itt, regd_buf->reg.rkey,
			 (unsigned long long)regd_buf->reg.va, unsol_sz);
	}

	if (imm_sz > 0) {
		iser_dbg("Cmd itt:%d, WRITE, adding imm.data sz: %d\n",
			 task->itt, imm_sz);
		tx_dsg->addr   = regd_buf->reg.va;
		tx_dsg->length = imm_sz;
		tx_dsg->lkey   = regd_buf->reg.lkey;
		iser_task->desc.num_sge = 2;
	}

	return 0;
}