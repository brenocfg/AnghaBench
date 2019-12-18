#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int local_inv; void* local_to; void* local_len; void* local_stag; void* rem_to; void* rem_stag; scalar_t__* reserved; int /*<<< orphan*/  rdmaop; } ;
union t3_wr {TYPE_3__ read; } ;
typedef  int u8 ;
struct t3_rdma_read_wr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  rkey; } ;
struct TYPE_6__ {TYPE_1__ rdma; } ;
struct ib_send_wr {int num_sge; scalar_t__ opcode; TYPE_4__* sg_list; TYPE_2__ wr; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  length; int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_WR_RDMA_READ_WITH_INV ; 
 int /*<<< orphan*/  T3_READ_REQ ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_rdma_read(union t3_wr *wqe, struct ib_send_wr *wr,
				u8 *flit_cnt)
{
	if (wr->num_sge > 1)
		return -EINVAL;
	wqe->read.rdmaop = T3_READ_REQ;
	if (wr->opcode == IB_WR_RDMA_READ_WITH_INV)
		wqe->read.local_inv = 1;
	else
		wqe->read.local_inv = 0;
	wqe->read.reserved[0] = 0;
	wqe->read.reserved[1] = 0;
	wqe->read.rem_stag = cpu_to_be32(wr->wr.rdma.rkey);
	wqe->read.rem_to = cpu_to_be64(wr->wr.rdma.remote_addr);
	wqe->read.local_stag = cpu_to_be32(wr->sg_list[0].lkey);
	wqe->read.local_len = cpu_to_be32(wr->sg_list[0].length);
	wqe->read.local_to = cpu_to_be64(wr->sg_list[0].addr);
	*flit_cnt = sizeof(struct t3_rdma_read_wr) >> 3;
	return 0;
}