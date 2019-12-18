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
struct sge_txq {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  pidx; int /*<<< orphan*/  db_pidx; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  db_disabled; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SGE_PF_KDOORBELL ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int V_PIDX (int) ; 
 int V_QID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void ring_tx_db(struct adapter *adap, struct sge_txq *q, int n)
{
	wmb();            /* write descriptors before telling HW */
	spin_lock(&q->db_lock);
	if (!q->db_disabled) {
		t4_write_reg(adap, MYPF_REG(A_SGE_PF_KDOORBELL),
			     V_QID(q->cntxt_id) | V_PIDX(n));
	}
	q->db_pidx = q->pidx;
	spin_unlock(&q->db_lock);
}