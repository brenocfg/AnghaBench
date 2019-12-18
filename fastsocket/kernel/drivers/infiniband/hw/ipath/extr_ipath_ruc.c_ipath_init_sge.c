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
typedef  int /*<<< orphan*/  wc ;
typedef  scalar_t__ u32 ;
struct ipath_sge_state {int num_sge; int /*<<< orphan*/  sge; int /*<<< orphan*/ * sg_list; } ;
struct ipath_rwqe {int num_sge; int /*<<< orphan*/  wr_id; TYPE_2__* sg_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  recv_cq; } ;
struct ipath_qp {TYPE_1__ ibqp; } ;
struct ib_wc {TYPE_1__* qp; int /*<<< orphan*/  opcode; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; } ;
struct TYPE_4__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 int /*<<< orphan*/  IB_WC_LOC_PROT_ERR ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int /*<<< orphan*/  ipath_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int) ; 
 int /*<<< orphan*/  ipath_lkey_ok (struct ipath_qp*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_icq (int /*<<< orphan*/ ) ; 

int ipath_init_sge(struct ipath_qp *qp, struct ipath_rwqe *wqe,
		   u32 *lengthp, struct ipath_sge_state *ss)
{
	int i, j, ret;
	struct ib_wc wc;

	*lengthp = 0;
	for (i = j = 0; i < wqe->num_sge; i++) {
		if (wqe->sg_list[i].length == 0)
			continue;
		/* Check LKEY */
		if (!ipath_lkey_ok(qp, j ? &ss->sg_list[j - 1] : &ss->sge,
				   &wqe->sg_list[i], IB_ACCESS_LOCAL_WRITE))
			goto bad_lkey;
		*lengthp += wqe->sg_list[i].length;
		j++;
	}
	ss->num_sge = j;
	ret = 1;
	goto bail;

bad_lkey:
	memset(&wc, 0, sizeof(wc));
	wc.wr_id = wqe->wr_id;
	wc.status = IB_WC_LOC_PROT_ERR;
	wc.opcode = IB_WC_RECV;
	wc.qp = &qp->ibqp;
	/* Signal solicited completion event. */
	ipath_cq_enter(to_icq(qp->ibqp.recv_cq), &wc, 1);
	ret = 0;
bail:
	return ret;
}