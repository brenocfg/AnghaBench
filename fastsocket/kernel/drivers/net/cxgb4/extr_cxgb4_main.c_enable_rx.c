#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sge_rspq {int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  intr_params; int /*<<< orphan*/  napi; scalar_t__ handler; } ;
struct TYPE_2__ {struct sge_rspq** ingr_map; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sge_rspq**) ; 
 int INGRESSQID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int SEINTARM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGE_PF_GTS ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_rx(struct adapter *adap)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(adap->sge.ingr_map); i++) {
		struct sge_rspq *q = adap->sge.ingr_map[i];

		if (!q)
			continue;
		if (q->handler)
			napi_enable(&q->napi);
		/* 0-increment GTS to start the timer and enable interrupts */
		t4_write_reg(adap, MYPF_REG(SGE_PF_GTS),
			     SEINTARM(q->intr_params) |
			     INGRESSQID(q->cntxt_id));
	}
}