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
struct sge_rspq {int iqe_len; int /*<<< orphan*/  intr_params; int /*<<< orphan*/  cntxt_id; scalar_t__ cur_desc; } ;
struct rsp_ctrl {int /*<<< orphan*/  pldbuflen_qid; int /*<<< orphan*/  type_gen; } ;
struct TYPE_4__ {int /*<<< orphan*/  intrq_lock; TYPE_1__** ingr_map; scalar_t__ ingr_start; struct sge_rspq intrq; } ;
struct adapter {TYPE_2__ sge; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int CIDXINC (unsigned int) ; 
 int INGRESSQID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ RSPD_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ RSP_TYPE_INTR ; 
 int SEINTARM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGE_PF_GTS ; 
 int /*<<< orphan*/  is_new_response (struct rsp_ctrl const*,struct sge_rspq*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  rspq_next (struct sge_rspq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int process_intrq(struct adapter *adap)
{
	unsigned int credits;
	const struct rsp_ctrl *rc;
	struct sge_rspq *q = &adap->sge.intrq;

	spin_lock(&adap->sge.intrq_lock);
	for (credits = 0; ; credits++) {
		rc = (void *)q->cur_desc + (q->iqe_len - sizeof(*rc));
		if (!is_new_response(rc, q))
			break;

		rmb();
		if (RSPD_TYPE(rc->type_gen) == RSP_TYPE_INTR) {
			unsigned int qid = ntohl(rc->pldbuflen_qid);

			qid -= adap->sge.ingr_start;
			napi_schedule(&adap->sge.ingr_map[qid]->napi);
		}

		rspq_next(q);
	}

	t4_write_reg(adap, MYPF_REG(SGE_PF_GTS), CIDXINC(credits) |
		     INGRESSQID(q->cntxt_id) | SEINTARM(q->intr_params));
	spin_unlock(&adap->sge.intrq_lock);
	return credits;
}