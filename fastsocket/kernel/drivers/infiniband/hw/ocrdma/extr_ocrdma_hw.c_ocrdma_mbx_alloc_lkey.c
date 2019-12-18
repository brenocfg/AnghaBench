#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ocrdma_mqe {int dummy; } ;
struct ocrdma_hw_mr {int fr_mr; int remote_wr; int remote_rd; int local_wr; int remote_atomic; int num_pbls; int /*<<< orphan*/  lkey; } ;
struct ocrdma_dev {int dummy; } ;
struct ocrdma_alloc_lkey_rsp {int /*<<< orphan*/  lrkey; } ;
struct ocrdma_alloc_lkey {int pbl_sz_flags; int /*<<< orphan*/  pdid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int OCRDMA_ALLOC_LKEY_FMR_SHIFT ; 
 int OCRDMA_ALLOC_LKEY_LOCAL_WR_SHIFT ; 
 int OCRDMA_ALLOC_LKEY_PBL_SIZE_SHIFT ; 
 int OCRDMA_ALLOC_LKEY_REMOTE_ATOMIC_SHIFT ; 
 int OCRDMA_ALLOC_LKEY_REMOTE_RD_SHIFT ; 
 int OCRDMA_ALLOC_LKEY_REMOTE_WR_SHIFT ; 
 int /*<<< orphan*/  OCRDMA_CMD_ALLOC_LKEY ; 
 int /*<<< orphan*/  kfree (struct ocrdma_alloc_lkey*) ; 
 struct ocrdma_alloc_lkey* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 

int ocrdma_mbx_alloc_lkey(struct ocrdma_dev *dev, struct ocrdma_hw_mr *hwmr,
			  u32 pdid, int addr_check)
{
	int status = -ENOMEM;
	struct ocrdma_alloc_lkey *cmd;
	struct ocrdma_alloc_lkey_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_ALLOC_LKEY, sizeof(*cmd));
	if (!cmd)
		return status;
	cmd->pdid = pdid;
	cmd->pbl_sz_flags |= addr_check;
	cmd->pbl_sz_flags |= (hwmr->fr_mr << OCRDMA_ALLOC_LKEY_FMR_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->remote_wr << OCRDMA_ALLOC_LKEY_REMOTE_WR_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->remote_rd << OCRDMA_ALLOC_LKEY_REMOTE_RD_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->local_wr << OCRDMA_ALLOC_LKEY_LOCAL_WR_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->remote_atomic << OCRDMA_ALLOC_LKEY_REMOTE_ATOMIC_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->num_pbls << OCRDMA_ALLOC_LKEY_PBL_SIZE_SHIFT);

	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status)
		goto mbx_err;
	rsp = (struct ocrdma_alloc_lkey_rsp *)cmd;
	hwmr->lkey = rsp->lrkey;
mbx_err:
	kfree(cmd);
	return status;
}