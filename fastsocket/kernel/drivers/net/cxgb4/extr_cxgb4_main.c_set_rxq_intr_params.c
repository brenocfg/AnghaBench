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
typedef  scalar_t__ u32 ;
struct sge_rspq {scalar_t__ pktcnt_idx; int intr_params; int /*<<< orphan*/  cntxt_id; scalar_t__ desc; } ;
struct adapter {int /*<<< orphan*/  sge; int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 scalar_t__ FW_PARAMS_MNEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DMAQ ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DMAQ_IQ_INTCNTTHRESH ; 
 scalar_t__ FW_PARAMS_PARAM_X (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_PARAMS_PARAM_YZ (int /*<<< orphan*/ ) ; 
 int QINTR_CNT_EN ; 
 int QINTR_TIMER_IDX (unsigned int) ; 
 scalar_t__ closest_thres (int /*<<< orphan*/ *,unsigned int) ; 
 int closest_timer (int /*<<< orphan*/ *,unsigned int) ; 
 int t4_set_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int set_rxq_intr_params(struct adapter *adap, struct sge_rspq *q,
			       unsigned int us, unsigned int cnt)
{
	if ((us | cnt) == 0)
		cnt = 1;

	if (cnt) {
		int err;
		u32 v, new_idx;

		new_idx = closest_thres(&adap->sge, cnt);
		if (q->desc && q->pktcnt_idx != new_idx) {
			/* the queue has already been created, update it */
			v = FW_PARAMS_MNEM(FW_PARAMS_MNEM_DMAQ) |
			    FW_PARAMS_PARAM_X(FW_PARAMS_PARAM_DMAQ_IQ_INTCNTTHRESH) |
			    FW_PARAMS_PARAM_YZ(q->cntxt_id);
			err = t4_set_params(adap, adap->fn, adap->fn, 0, 1, &v,
					    &new_idx);
			if (err)
				return err;
		}
		q->pktcnt_idx = new_idx;
	}

	us = us == 0 ? 6 : closest_timer(&adap->sge, us);
	q->intr_params = QINTR_TIMER_IDX(us) | (cnt > 0 ? QINTR_CNT_EN : 0);
	return 0;
}