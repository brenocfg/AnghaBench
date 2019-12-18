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
typedef  int u32 ;
struct TYPE_3__ {int max_send_wr; int max_recv_wr; int max_send_sge; int max_recv_sge; } ;
struct ib_qp_init_attr {size_t qp_type; int port_num; int /*<<< orphan*/ * srq; int /*<<< orphan*/ * event_handler; int /*<<< orphan*/ * qp_context; TYPE_1__ cap; int /*<<< orphan*/  sq_sig_type; struct ib_qp* recv_cq; struct ib_qp* send_cq; } ;
struct ib_qp {int dummy; } ;
typedef  struct ib_qp ib_cq ;
struct ehca_sport {struct ib_qp* ibcq_aqp1; struct ib_qp** ibqp_sqp; } ;
struct ehca_shca {int /*<<< orphan*/  ib_device; TYPE_2__* pd; struct ehca_sport* sport; } ;
struct TYPE_4__ {int /*<<< orphan*/  ib_pd; } ;

/* Variables and functions */
 int EPERM ; 
 size_t IB_QPT_GSI ; 
 int /*<<< orphan*/  IB_SIGNAL_ALL_WR ; 
 scalar_t__ IS_ERR (struct ib_qp*) ; 
 int PTR_ERR (struct ib_qp*) ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*) ; 
 struct ib_qp* ib_create_cq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 struct ib_qp* ib_create_qp (int /*<<< orphan*/ *,struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  ib_destroy_cq (struct ib_qp*) ; 
 int /*<<< orphan*/  memset (struct ib_qp_init_attr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ehca_create_aqp1(struct ehca_shca *shca, u32 port)
{
	struct ehca_sport *sport = &shca->sport[port - 1];
	struct ib_cq *ibcq;
	struct ib_qp *ibqp;
	struct ib_qp_init_attr qp_init_attr;
	int ret;

	if (sport->ibcq_aqp1) {
		ehca_err(&shca->ib_device, "AQP1 CQ is already created.");
		return -EPERM;
	}

	ibcq = ib_create_cq(&shca->ib_device, NULL, NULL, (void *)(-1), 10, 0);
	if (IS_ERR(ibcq)) {
		ehca_err(&shca->ib_device, "Cannot create AQP1 CQ.");
		return PTR_ERR(ibcq);
	}
	sport->ibcq_aqp1 = ibcq;

	if (sport->ibqp_sqp[IB_QPT_GSI]) {
		ehca_err(&shca->ib_device, "AQP1 QP is already created.");
		ret = -EPERM;
		goto create_aqp1;
	}

	memset(&qp_init_attr, 0, sizeof(struct ib_qp_init_attr));
	qp_init_attr.send_cq          = ibcq;
	qp_init_attr.recv_cq          = ibcq;
	qp_init_attr.sq_sig_type      = IB_SIGNAL_ALL_WR;
	qp_init_attr.cap.max_send_wr  = 100;
	qp_init_attr.cap.max_recv_wr  = 100;
	qp_init_attr.cap.max_send_sge = 2;
	qp_init_attr.cap.max_recv_sge = 1;
	qp_init_attr.qp_type          = IB_QPT_GSI;
	qp_init_attr.port_num         = port;
	qp_init_attr.qp_context       = NULL;
	qp_init_attr.event_handler    = NULL;
	qp_init_attr.srq              = NULL;

	ibqp = ib_create_qp(&shca->pd->ib_pd, &qp_init_attr);
	if (IS_ERR(ibqp)) {
		ehca_err(&shca->ib_device, "Cannot create AQP1 QP.");
		ret = PTR_ERR(ibqp);
		goto create_aqp1;
	}
	sport->ibqp_sqp[IB_QPT_GSI] = ibqp;

	return 0;

create_aqp1:
	ib_destroy_cq(sport->ibcq_aqp1);
	return ret;
}