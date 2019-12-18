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
struct sge_rspq {size_t cidx; int /*<<< orphan*/  holdoff_tmr; int /*<<< orphan*/  cntxt_id; struct rsp_desc* desc; } ;
struct sge_qset {int /*<<< orphan*/  napi; } ;
struct rsp_desc {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_GTS ; 
 int V_NEWINDEX (size_t) ; 
 int V_NEWTIMER (int /*<<< orphan*/ ) ; 
 int V_RSPQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_new_response (struct rsp_desc*,struct sge_rspq*) ; 
 scalar_t__ is_pure_response (struct rsp_desc*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ process_pure_responses (struct adapter*,struct sge_qset*,struct rsp_desc*) ; 
 int /*<<< orphan*/  rmb () ; 
 struct sge_qset* rspq_to_qset (struct sge_rspq*) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int handle_responses(struct adapter *adap, struct sge_rspq *q)
{
	struct sge_qset *qs = rspq_to_qset(q);
	struct rsp_desc *r = &q->desc[q->cidx];

	if (!is_new_response(r, q))
		return -1;
	rmb();
	if (is_pure_response(r) && process_pure_responses(adap, qs, r) == 0) {
		t3_write_reg(adap, A_SG_GTS, V_RSPQ(q->cntxt_id) |
			     V_NEWTIMER(q->holdoff_tmr) | V_NEWINDEX(q->cidx));
		return 0;
	}
	napi_schedule(&qs->napi);
	return 1;
}