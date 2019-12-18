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
struct b577xx_fcoe_rx_doorbell {int doorbell_cq_cons; } ;
struct bnx2fc_rport {int cq_cons_idx; int cq_curr_toggle_bit; int /*<<< orphan*/  ctx_base; struct b577xx_fcoe_rx_doorbell rx_db; } ;

/* Variables and functions */
 int FCOE_CQE_TOGGLE_BIT_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2fc_arm_cq(struct bnx2fc_rport *tgt)
{
	struct b577xx_fcoe_rx_doorbell *rx_db = &tgt->rx_db;
	u32 msg;

	wmb();
	rx_db->doorbell_cq_cons = tgt->cq_cons_idx | (tgt->cq_curr_toggle_bit <<
			FCOE_CQE_TOGGLE_BIT_SHIFT);
	msg = *((u32 *)rx_db);
	writel(cpu_to_le32(msg), tgt->ctx_base);
	mmiowb();

}