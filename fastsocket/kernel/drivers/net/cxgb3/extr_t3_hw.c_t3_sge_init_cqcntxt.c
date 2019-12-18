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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_CONTEXT_CMD ; 
 int /*<<< orphan*/  A_SG_CONTEXT_DATA0 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_DATA1 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_DATA2 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_DATA3 ; 
 int EBUSY ; 
 int EINVAL ; 
 int F_CONTEXT_CMD_BUSY ; 
 int /*<<< orphan*/  F_CQ ; 
 int V_CQ_BASE_HI (int /*<<< orphan*/ ) ; 
 int V_CQ_CREDITS (unsigned int) ; 
 int V_CQ_CREDIT_THRES (unsigned int) ; 
 int V_CQ_ERR (int) ; 
 int V_CQ_GEN (int) ; 
 int V_CQ_OVERFLOW_MODE (int) ; 
 int V_CQ_RSPQ (int) ; 
 int V_CQ_SIZE (unsigned int) ; 
 int t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int t3_sge_write_context (struct adapter*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

int t3_sge_init_cqcntxt(struct adapter *adapter, unsigned int id, u64 base_addr,
			unsigned int size, int rspq, int ovfl_mode,
			unsigned int credits, unsigned int credit_thres)
{
	if (base_addr & 0xfff)	/* must be 4K aligned */
		return -EINVAL;
	if (t3_read_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		return -EBUSY;

	base_addr >>= 12;
	t3_write_reg(adapter, A_SG_CONTEXT_DATA0, V_CQ_SIZE(size));
	t3_write_reg(adapter, A_SG_CONTEXT_DATA1, base_addr);
	base_addr >>= 32;
	t3_write_reg(adapter, A_SG_CONTEXT_DATA2,
		     V_CQ_BASE_HI((u32) base_addr) | V_CQ_RSPQ(rspq) |
		     V_CQ_GEN(1) | V_CQ_OVERFLOW_MODE(ovfl_mode) |
		     V_CQ_ERR(ovfl_mode));
	t3_write_reg(adapter, A_SG_CONTEXT_DATA3, V_CQ_CREDITS(credits) |
		     V_CQ_CREDIT_THRES(credit_thres));
	return t3_sge_write_context(adapter, id, F_CQ);
}