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
struct qfq_class {int /*<<< orphan*/  cl_q; int /*<<< orphan*/ * cl_sfb; TYPE_1__* cl_qif; } ;
typedef  int /*<<< orphan*/  pktsched_pkt_t ;
struct TYPE_2__ {int /*<<< orphan*/  qif_ifq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _getq (int /*<<< orphan*/ *) ; 
 void pktsched_pkt_encap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ q_is_sfb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qptype (int /*<<< orphan*/ *) ; 
 void sfb_getq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
qfq_getq(struct qfq_class *cl, pktsched_pkt_t *pkt)
{
	IFCQ_LOCK_ASSERT_HELD(cl->cl_qif->qif_ifq);

	if (q_is_sfb(&cl->cl_q) && cl->cl_sfb != NULL)
		return (sfb_getq(cl->cl_sfb, &cl->cl_q, pkt));

	return (pktsched_pkt_encap(pkt, qptype(&cl->cl_q), _getq(&cl->cl_q)));
}