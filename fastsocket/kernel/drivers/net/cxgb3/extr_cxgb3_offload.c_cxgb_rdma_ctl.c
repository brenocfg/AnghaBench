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
struct tp_mib_stats {int dummy; } ;
struct rdma_info {struct pci_dev* pdev; scalar_t__ kdb_addr; void* rqt_top; void* rqt_base; void* pbl_top; void* pbl_base; void* tpt_top; void* tpt_base; int /*<<< orphan*/  udbell_len; int /*<<< orphan*/  udbell_physbase; } ;
struct rdma_ctrlqp_setup {int /*<<< orphan*/  size; int /*<<< orphan*/  base_addr; } ;
struct rdma_cq_setup {int /*<<< orphan*/  credit_thres; int /*<<< orphan*/  credits; int /*<<< orphan*/  ovfl_mode; int /*<<< orphan*/  size; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  id; } ;
struct rdma_cq_op {int /*<<< orphan*/  credits; int /*<<< orphan*/  op; int /*<<< orphan*/  id; } ;
struct pci_dev {int dummy; } ;
struct mc7 {int dummy; } ;
struct ch_mem_range {int addr; int len; scalar_t__ buf; int /*<<< orphan*/  mem_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;
struct adapter {int /*<<< orphan*/  stats_lock; TYPE_1__ sge; struct mc7 pmtx; struct mc7 pmrx; struct mc7 cm; scalar_t__ regs; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_NOTIF_RSPQ ; 
 scalar_t__ A_SG_KDOORBELL ; 
 int /*<<< orphan*/  A_ULPRX_RQ_LLIMIT ; 
 int /*<<< orphan*/  A_ULPRX_RQ_ULIMIT ; 
 int /*<<< orphan*/  A_ULPTX_PBL_LLIMIT ; 
 int /*<<< orphan*/  A_ULPTX_PBL_ULIMIT ; 
 int /*<<< orphan*/  A_ULPTX_TPT_LLIMIT ; 
 int /*<<< orphan*/  A_ULPTX_TPT_ULIMIT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FW_RI_SGEEC_START ; 
 int /*<<< orphan*/  FW_RI_TID_START ; 
 int /*<<< orphan*/  MEM_CM ; 
 int /*<<< orphan*/  MEM_PMRX ; 
 int /*<<< orphan*/  MEM_PMTX ; 
#define  RDMA_CQ_DISABLE 134 
#define  RDMA_CQ_OP 133 
#define  RDMA_CQ_SETUP 132 
#define  RDMA_CTRL_QP_SETUP 131 
#define  RDMA_GET_MEM 130 
#define  RDMA_GET_MIB 129 
#define  RDMA_GET_PARAMS 128 
 int /*<<< orphan*/  SGE_CNTXT_RDMA ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int t3_mc7_bd_read (struct mc7*,int,int,int /*<<< orphan*/ *) ; 
 void* t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int t3_sge_cqcntxt_op (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t3_sge_disable_cqcntxt (struct adapter*,unsigned int) ; 
 int t3_sge_init_cqcntxt (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t3_sge_init_ecntxt (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_tp_get_mib_stats (struct adapter*,struct tp_mib_stats*) ; 

__attribute__((used)) static int cxgb_rdma_ctl(struct adapter *adapter, unsigned int req, void *data)
{
	int ret = 0;

	switch (req) {
	case RDMA_GET_PARAMS: {
		struct rdma_info *rdma = data;
		struct pci_dev *pdev = adapter->pdev;

		rdma->udbell_physbase = pci_resource_start(pdev, 2);
		rdma->udbell_len = pci_resource_len(pdev, 2);
		rdma->tpt_base =
			t3_read_reg(adapter, A_ULPTX_TPT_LLIMIT);
		rdma->tpt_top = t3_read_reg(adapter, A_ULPTX_TPT_ULIMIT);
		rdma->pbl_base =
			t3_read_reg(adapter, A_ULPTX_PBL_LLIMIT);
		rdma->pbl_top = t3_read_reg(adapter, A_ULPTX_PBL_ULIMIT);
		rdma->rqt_base = t3_read_reg(adapter, A_ULPRX_RQ_LLIMIT);
		rdma->rqt_top = t3_read_reg(adapter, A_ULPRX_RQ_ULIMIT);
		rdma->kdb_addr = adapter->regs + A_SG_KDOORBELL;
		rdma->pdev = pdev;
		break;
	}
	case RDMA_CQ_OP:{
		unsigned long flags;
		struct rdma_cq_op *rdma = data;

		/* may be called in any context */
		spin_lock_irqsave(&adapter->sge.reg_lock, flags);
		ret = t3_sge_cqcntxt_op(adapter, rdma->id, rdma->op,
					rdma->credits);
		spin_unlock_irqrestore(&adapter->sge.reg_lock, flags);
		break;
	}
	case RDMA_GET_MEM:{
		struct ch_mem_range *t = data;
		struct mc7 *mem;

		if ((t->addr & 7) || (t->len & 7))
			return -EINVAL;
		if (t->mem_id == MEM_CM)
			mem = &adapter->cm;
		else if (t->mem_id == MEM_PMRX)
			mem = &adapter->pmrx;
		else if (t->mem_id == MEM_PMTX)
			mem = &adapter->pmtx;
		else
			return -EINVAL;

		ret =
			t3_mc7_bd_read(mem, t->addr / 8, t->len / 8,
					(u64 *) t->buf);
		if (ret)
			return ret;
		break;
	}
	case RDMA_CQ_SETUP:{
		struct rdma_cq_setup *rdma = data;

		spin_lock_irq(&adapter->sge.reg_lock);
		ret =
			t3_sge_init_cqcntxt(adapter, rdma->id,
					rdma->base_addr, rdma->size,
					ASYNC_NOTIF_RSPQ,
					rdma->ovfl_mode, rdma->credits,
					rdma->credit_thres);
		spin_unlock_irq(&adapter->sge.reg_lock);
		break;
	}
	case RDMA_CQ_DISABLE:
		spin_lock_irq(&adapter->sge.reg_lock);
		ret = t3_sge_disable_cqcntxt(adapter, *(unsigned int *)data);
		spin_unlock_irq(&adapter->sge.reg_lock);
		break;
	case RDMA_CTRL_QP_SETUP:{
		struct rdma_ctrlqp_setup *rdma = data;

		spin_lock_irq(&adapter->sge.reg_lock);
		ret = t3_sge_init_ecntxt(adapter, FW_RI_SGEEC_START, 0,
						SGE_CNTXT_RDMA,
						ASYNC_NOTIF_RSPQ,
						rdma->base_addr, rdma->size,
						FW_RI_TID_START, 1, 0);
		spin_unlock_irq(&adapter->sge.reg_lock);
		break;
	}
	case RDMA_GET_MIB: {
		spin_lock(&adapter->stats_lock);
		t3_tp_get_mib_stats(adapter, (struct tp_mib_stats *)data);
		spin_unlock(&adapter->stats_lock);
		break;
	}
	default:
		ret = -EOPNOTSUPP;
	}
	return ret;
}