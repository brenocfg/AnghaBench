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
struct sge_rspq {int /*<<< orphan*/  cntxt_id; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_RSPQ_CREDIT_RETURN ; 
 int V_CREDITS (unsigned int) ; 
 int V_RSPQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void refill_rspq(struct adapter *adapter,
			       const struct sge_rspq *q, unsigned int credits)
{
	rmb();
	t3_write_reg(adapter, A_SG_RSPQ_CREDIT_RETURN,
		     V_RSPQ(q->cntxt_id) | V_CREDITS(credits));
}