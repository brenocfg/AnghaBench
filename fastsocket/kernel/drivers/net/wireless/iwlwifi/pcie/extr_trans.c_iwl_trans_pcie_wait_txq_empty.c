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
typedef  int u8 ;
typedef  int u32 ;
struct iwl_queue {scalar_t__ read_ptr; scalar_t__ write_ptr; int n_bd; int /*<<< orphan*/  id; } ;
struct iwl_txq {struct iwl_queue q; } ;
struct iwl_trans_pcie {int cmd_queue; int scd_base_addr; struct iwl_txq* txq; } ;
struct iwl_trans {TYPE_2__* cfg; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {int num_of_queues; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int FH_TCSR_CHNL_NUM ; 
 int /*<<< orphan*/  FH_TX_TRB_REG (int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int,...) ; 
 int /*<<< orphan*/  IWL_FLUSH_WAIT_MS ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  SCD_QUEUE_RDPTR (int) ; 
 int /*<<< orphan*/  SCD_QUEUE_STATUS_BITS (int) ; 
 int /*<<< orphan*/  SCD_QUEUE_STTS_REG_POS_ACTIVE ; 
 int SCD_QUEUE_STTS_REG_POS_TXF ; 
 int /*<<< orphan*/  SCD_QUEUE_WRPTR (int) ; 
 int SCD_TRANS_TBL_OFFSET_QUEUE (int) ; 
 int SCD_TX_STTS_QUEUE_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_print_hex_error (struct iwl_trans*,int*,int) ; 
 int /*<<< orphan*/  iwl_read_direct32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_read_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_trans_read_mem32 (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_trans_read_mem_bytes (struct iwl_trans*,int,int*,int) ; 
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static int iwl_trans_pcie_wait_txq_empty(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_txq *txq;
	struct iwl_queue *q;
	int cnt;
	unsigned long now = jiffies;
	u32 scd_sram_addr;
	u8 buf[16];
	int ret = 0;

	/* waiting for all the tx frames complete might take a while */
	for (cnt = 0; cnt < trans->cfg->base_params->num_of_queues; cnt++) {
		if (cnt == trans_pcie->cmd_queue)
			continue;
		txq = &trans_pcie->txq[cnt];
		q = &txq->q;
		while (q->read_ptr != q->write_ptr && !time_after(jiffies,
		       now + msecs_to_jiffies(IWL_FLUSH_WAIT_MS)))
			msleep(1);

		if (q->read_ptr != q->write_ptr) {
			IWL_ERR(trans,
				"fail to flush all tx fifo queues Q %d\n", cnt);
			ret = -ETIMEDOUT;
			break;
		}
	}

	if (!ret)
		return 0;

	IWL_ERR(trans, "Current SW read_ptr %d write_ptr %d\n",
		txq->q.read_ptr, txq->q.write_ptr);

	scd_sram_addr = trans_pcie->scd_base_addr +
			SCD_TX_STTS_QUEUE_OFFSET(txq->q.id);
	iwl_trans_read_mem_bytes(trans, scd_sram_addr, buf, sizeof(buf));

	iwl_print_hex_error(trans, buf, sizeof(buf));

	for (cnt = 0; cnt < FH_TCSR_CHNL_NUM; cnt++)
		IWL_ERR(trans, "FH TRBs(%d) = 0x%08x\n", cnt,
			iwl_read_direct32(trans, FH_TX_TRB_REG(cnt)));

	for (cnt = 0; cnt < trans->cfg->base_params->num_of_queues; cnt++) {
		u32 status = iwl_read_prph(trans, SCD_QUEUE_STATUS_BITS(cnt));
		u8 fifo = (status >> SCD_QUEUE_STTS_REG_POS_TXF) & 0x7;
		bool active = !!(status & BIT(SCD_QUEUE_STTS_REG_POS_ACTIVE));
		u32 tbl_dw =
			iwl_trans_read_mem32(trans, trans_pcie->scd_base_addr +
					     SCD_TRANS_TBL_OFFSET_QUEUE(cnt));

		if (cnt & 0x1)
			tbl_dw = (tbl_dw & 0xFFFF0000) >> 16;
		else
			tbl_dw = tbl_dw & 0x0000FFFF;

		IWL_ERR(trans,
			"Q %d is %sactive and mapped to fifo %d ra_tid 0x%04x [%d,%d]\n",
			cnt, active ? "" : "in", fifo, tbl_dw,
			iwl_read_prph(trans,
				      SCD_QUEUE_RDPTR(cnt)) & (txq->q.n_bd - 1),
			iwl_read_prph(trans, SCD_QUEUE_WRPTR(cnt)));
	}

	return ret;
}