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
struct TYPE_6__ {TYPE_4__* immd_src; int /*<<< orphan*/  isgl_src; } ;
struct TYPE_7__ {void* plen; TYPE_2__ u; void* stag_inv; void* sendop_pkd; } ;
union t4_wr {TYPE_3__ send; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct t4_sq {size_t size; int /*<<< orphan*/ * queue; } ;
struct TYPE_5__ {int invalidate_rkey; } ;
struct ib_send_wr {int num_sge; int opcode; int send_flags; int /*<<< orphan*/  sg_list; TYPE_1__ ex; } ;
struct fw_ri_sge {int dummy; } ;
struct fw_ri_isgl {int dummy; } ;
struct fw_ri_immd {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_8__ {scalar_t__ immdlen; scalar_t__ r2; scalar_t__ r1; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FW_RI_DATA_IMMD ; 
 int /*<<< orphan*/  FW_RI_SEND ; 
 int /*<<< orphan*/  FW_RI_SEND_WITH_INV ; 
 int /*<<< orphan*/  FW_RI_SEND_WITH_SE ; 
 int /*<<< orphan*/  FW_RI_SEND_WITH_SE_INV ; 
 int IB_SEND_INLINE ; 
 int IB_SEND_SOLICITED ; 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_INV 128 
 int /*<<< orphan*/  T4_MAX_SEND_INLINE ; 
 int T4_MAX_SEND_SGE ; 
 int V_FW_RI_SEND_WR_SENDOP (int /*<<< orphan*/ ) ; 
 int build_immd (struct t4_sq*,TYPE_4__*,struct ib_send_wr*,int /*<<< orphan*/ ,int*) ; 
 int build_isgl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static int build_rdma_send(struct t4_sq *sq, union t4_wr *wqe,
			   struct ib_send_wr *wr, u8 *len16)
{
	u32 plen;
	int size;
	int ret;

	if (wr->num_sge > T4_MAX_SEND_SGE)
		return -EINVAL;
	switch (wr->opcode) {
	case IB_WR_SEND:
		if (wr->send_flags & IB_SEND_SOLICITED)
			wqe->send.sendop_pkd = cpu_to_be32(
				V_FW_RI_SEND_WR_SENDOP(FW_RI_SEND_WITH_SE));
		else
			wqe->send.sendop_pkd = cpu_to_be32(
				V_FW_RI_SEND_WR_SENDOP(FW_RI_SEND));
		wqe->send.stag_inv = 0;
		break;
	case IB_WR_SEND_WITH_INV:
		if (wr->send_flags & IB_SEND_SOLICITED)
			wqe->send.sendop_pkd = cpu_to_be32(
				V_FW_RI_SEND_WR_SENDOP(FW_RI_SEND_WITH_SE_INV));
		else
			wqe->send.sendop_pkd = cpu_to_be32(
				V_FW_RI_SEND_WR_SENDOP(FW_RI_SEND_WITH_INV));
		wqe->send.stag_inv = cpu_to_be32(wr->ex.invalidate_rkey);
		break;

	default:
		return -EINVAL;
	}

	plen = 0;
	if (wr->num_sge) {
		if (wr->send_flags & IB_SEND_INLINE) {
			ret = build_immd(sq, wqe->send.u.immd_src, wr,
					 T4_MAX_SEND_INLINE, &plen);
			if (ret)
				return ret;
			size = sizeof wqe->send + sizeof(struct fw_ri_immd) +
			       plen;
		} else {
			ret = build_isgl((__be64 *)sq->queue,
					 (__be64 *)&sq->queue[sq->size],
					 wqe->send.u.isgl_src,
					 wr->sg_list, wr->num_sge, &plen);
			if (ret)
				return ret;
			size = sizeof wqe->send + sizeof(struct fw_ri_isgl) +
			       wr->num_sge * sizeof(struct fw_ri_sge);
		}
	} else {
		wqe->send.u.immd_src[0].op = FW_RI_DATA_IMMD;
		wqe->send.u.immd_src[0].r1 = 0;
		wqe->send.u.immd_src[0].r2 = 0;
		wqe->send.u.immd_src[0].immdlen = 0;
		size = sizeof wqe->send + sizeof(struct fw_ri_immd);
		plen = 0;
	}
	*len16 = DIV_ROUND_UP(size, 16);
	wqe->send.plen = cpu_to_be32(plen);
	return 0;
}