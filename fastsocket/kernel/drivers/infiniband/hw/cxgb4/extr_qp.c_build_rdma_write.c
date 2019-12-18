#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* immd_src; int /*<<< orphan*/  isgl_src; } ;
struct TYPE_9__ {void* plen; TYPE_3__ u; int /*<<< orphan*/  to_sink; void* stag_sink; scalar_t__ r2; } ;
union t4_wr {TYPE_4__ write; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct t4_sq {size_t size; int /*<<< orphan*/ * queue; } ;
struct TYPE_6__ {int rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_7__ {TYPE_1__ rdma; } ;
struct ib_send_wr {int num_sge; int send_flags; int /*<<< orphan*/  sg_list; TYPE_2__ wr; } ;
struct fw_ri_sge {int dummy; } ;
struct fw_ri_isgl {int dummy; } ;
struct fw_ri_immd {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_10__ {scalar_t__ immdlen; scalar_t__ r2; scalar_t__ r1; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FW_RI_DATA_IMMD ; 
 int IB_SEND_INLINE ; 
 int T4_MAX_SEND_SGE ; 
 int /*<<< orphan*/  T4_MAX_WRITE_INLINE ; 
 int build_immd (struct t4_sq*,TYPE_5__*,struct ib_send_wr*,int /*<<< orphan*/ ,int*) ; 
 int build_isgl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_rdma_write(struct t4_sq *sq, union t4_wr *wqe,
			    struct ib_send_wr *wr, u8 *len16)
{
	u32 plen;
	int size;
	int ret;

	if (wr->num_sge > T4_MAX_SEND_SGE)
		return -EINVAL;
	wqe->write.r2 = 0;
	wqe->write.stag_sink = cpu_to_be32(wr->wr.rdma.rkey);
	wqe->write.to_sink = cpu_to_be64(wr->wr.rdma.remote_addr);
	if (wr->num_sge) {
		if (wr->send_flags & IB_SEND_INLINE) {
			ret = build_immd(sq, wqe->write.u.immd_src, wr,
					 T4_MAX_WRITE_INLINE, &plen);
			if (ret)
				return ret;
			size = sizeof wqe->write + sizeof(struct fw_ri_immd) +
			       plen;
		} else {
			ret = build_isgl((__be64 *)sq->queue,
					 (__be64 *)&sq->queue[sq->size],
					 wqe->write.u.isgl_src,
					 wr->sg_list, wr->num_sge, &plen);
			if (ret)
				return ret;
			size = sizeof wqe->write + sizeof(struct fw_ri_isgl) +
			       wr->num_sge * sizeof(struct fw_ri_sge);
		}
	} else {
		wqe->write.u.immd_src[0].op = FW_RI_DATA_IMMD;
		wqe->write.u.immd_src[0].r1 = 0;
		wqe->write.u.immd_src[0].r2 = 0;
		wqe->write.u.immd_src[0].immdlen = 0;
		size = sizeof wqe->write + sizeof(struct fw_ri_immd);
		plen = 0;
	}
	*len16 = DIV_ROUND_UP(size, 16);
	wqe->write.plen = cpu_to_be32(plen);
	return 0;
}