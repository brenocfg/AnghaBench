#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* plen; void* num_sgle; TYPE_4__* sgl; void* to_sink; void* stag_sink; scalar_t__* reserved; int /*<<< orphan*/  rdmaop; } ;
union t3_wr {TYPE_6__ write; } ;
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_9__ {void* imm_data; } ;
struct TYPE_7__ {int rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_8__ {TYPE_1__ rdma; } ;
struct ib_send_wr {int num_sge; scalar_t__ opcode; TYPE_5__* sg_list; TYPE_3__ ex; TYPE_2__ wr; } ;
struct TYPE_11__ {int length; int lkey; int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {void* to; void* len; void* stag; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 scalar_t__ IB_WR_RDMA_WRITE_WITH_IMM ; 
 int T3_MAX_SGE ; 
 int /*<<< orphan*/  T3_RDMA_WRITE ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_rdma_write(union t3_wr *wqe, struct ib_send_wr *wr,
				 u8 *flit_cnt)
{
	int i;
	u32 plen;
	if (wr->num_sge > T3_MAX_SGE)
		return -EINVAL;
	wqe->write.rdmaop = T3_RDMA_WRITE;
	wqe->write.reserved[0] = 0;
	wqe->write.reserved[1] = 0;
	wqe->write.reserved[2] = 0;
	wqe->write.stag_sink = cpu_to_be32(wr->wr.rdma.rkey);
	wqe->write.to_sink = cpu_to_be64(wr->wr.rdma.remote_addr);

	if (wr->opcode == IB_WR_RDMA_WRITE_WITH_IMM) {
		plen = 4;
		wqe->write.sgl[0].stag = wr->ex.imm_data;
		wqe->write.sgl[0].len = cpu_to_be32(0);
		wqe->write.num_sgle = cpu_to_be32(0);
		*flit_cnt = 6;
	} else {
		plen = 0;
		for (i = 0; i < wr->num_sge; i++) {
			if ((plen + wr->sg_list[i].length) < plen) {
				return -EMSGSIZE;
			}
			plen += wr->sg_list[i].length;
			wqe->write.sgl[i].stag =
			    cpu_to_be32(wr->sg_list[i].lkey);
			wqe->write.sgl[i].len =
			    cpu_to_be32(wr->sg_list[i].length);
			wqe->write.sgl[i].to =
			    cpu_to_be64(wr->sg_list[i].addr);
		}
		wqe->write.num_sgle = cpu_to_be32(wr->num_sge);
		*flit_cnt = 5 + ((wr->num_sge) << 1);
	}
	wqe->write.plen = cpu_to_be32(plen);
	return 0;
}