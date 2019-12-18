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
typedef  int u32 ;
struct ocrdma_reg_nsmr_rsp {int /*<<< orphan*/  lrkey; } ;
struct ocrdma_reg_nsmr {int num_pbl_pdid; int flags_hpage_pbe_sz; int totlen_low; int fbo_low; int fbo_high; int va_loaddr; int va_hiaddr; TYPE_1__* pbl; void* totlen_high; } ;
struct ocrdma_mqe {int dummy; } ;
struct ocrdma_hw_mr {int num_pbls; int remote_wr; int remote_rd; int local_wr; int remote_atomic; int mw_bind; int pbe_size; int pbl_size; int len; int fbo; int va; int /*<<< orphan*/  lkey; TYPE_2__* pbl_table; } ;
struct ocrdma_dev {int dummy; } ;
struct TYPE_4__ {int pa; } ;
struct TYPE_3__ {int lo; void* hi; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  OCRDMA_CMD_REGISTER_NSMR ; 
 int OCRDMA_MIN_HPAGE_SIZE ; 
 int OCRDMA_REG_NSMR_BIND_MEMWIN_SHIFT ; 
 int OCRDMA_REG_NSMR_HPAGE_SIZE_SHIFT ; 
 int OCRDMA_REG_NSMR_LAST_SHIFT ; 
 int OCRDMA_REG_NSMR_LOCAL_WR_SHIFT ; 
 int OCRDMA_REG_NSMR_NUM_PBL_SHIFT ; 
 int OCRDMA_REG_NSMR_REMOTE_ATOMIC_SHIFT ; 
 int OCRDMA_REG_NSMR_REMOTE_RD_SHIFT ; 
 int OCRDMA_REG_NSMR_REMOTE_WR_SHIFT ; 
 int /*<<< orphan*/  kfree (struct ocrdma_reg_nsmr*) ; 
 struct ocrdma_reg_nsmr* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 
 void* upper_32_bits (int) ; 

__attribute__((used)) static int ocrdma_mbx_reg_mr(struct ocrdma_dev *dev, struct ocrdma_hw_mr *hwmr,
			     u32 pdid, u32 pbl_cnt, u32 pbe_size, u32 last)
{
	int status = -ENOMEM;
	int i;
	struct ocrdma_reg_nsmr *cmd;
	struct ocrdma_reg_nsmr_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_REGISTER_NSMR, sizeof(*cmd));
	if (!cmd)
		return -ENOMEM;
	cmd->num_pbl_pdid =
	    pdid | (hwmr->num_pbls << OCRDMA_REG_NSMR_NUM_PBL_SHIFT);

	cmd->flags_hpage_pbe_sz |= (hwmr->remote_wr <<
				    OCRDMA_REG_NSMR_REMOTE_WR_SHIFT);
	cmd->flags_hpage_pbe_sz |= (hwmr->remote_rd <<
				    OCRDMA_REG_NSMR_REMOTE_RD_SHIFT);
	cmd->flags_hpage_pbe_sz |= (hwmr->local_wr <<
				    OCRDMA_REG_NSMR_LOCAL_WR_SHIFT);
	cmd->flags_hpage_pbe_sz |= (hwmr->remote_atomic <<
				    OCRDMA_REG_NSMR_REMOTE_ATOMIC_SHIFT);
	cmd->flags_hpage_pbe_sz |= (hwmr->mw_bind <<
				    OCRDMA_REG_NSMR_BIND_MEMWIN_SHIFT);
	cmd->flags_hpage_pbe_sz |= (last << OCRDMA_REG_NSMR_LAST_SHIFT);

	cmd->flags_hpage_pbe_sz |= (hwmr->pbe_size / OCRDMA_MIN_HPAGE_SIZE);
	cmd->flags_hpage_pbe_sz |= (hwmr->pbl_size / OCRDMA_MIN_HPAGE_SIZE) <<
					OCRDMA_REG_NSMR_HPAGE_SIZE_SHIFT;
	cmd->totlen_low = hwmr->len;
	cmd->totlen_high = upper_32_bits(hwmr->len);
	cmd->fbo_low = (u32) (hwmr->fbo & 0xffffffff);
	cmd->fbo_high = (u32) upper_32_bits(hwmr->fbo);
	cmd->va_loaddr = (u32) hwmr->va;
	cmd->va_hiaddr = (u32) upper_32_bits(hwmr->va);

	for (i = 0; i < pbl_cnt; i++) {
		cmd->pbl[i].lo = (u32) (hwmr->pbl_table[i].pa & 0xffffffff);
		cmd->pbl[i].hi = upper_32_bits(hwmr->pbl_table[i].pa);
	}
	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status)
		goto mbx_err;
	rsp = (struct ocrdma_reg_nsmr_rsp *)cmd;
	hwmr->lkey = rsp->lrkey;
mbx_err:
	kfree(cmd);
	return status;
}